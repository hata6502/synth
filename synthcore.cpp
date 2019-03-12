#include <request.hpp>
#include <response.hpp>
#include <core/core.hpp>
#include <com/com.hpp>

#include <exception>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

using namespace std;

extern "C"
{
    int main(int argc, char **argv);
}
void execute(Request &request);
template <typename T>
void respond(T &response);
void addcom(vector<string> &args);
void lscom(vector<string> &args);
void lsport(vector<string> &args);

int main(int argc, char **argv)
{
    initCom();

    /*Component *speaker1 = newCom("Speaker");

    {
        Component *input1 = newCom("Input");
        Component *sine1 = newCom("Sine");

        static_cast<Input *>(input1)->setValue(440.0);
        sine1->ins[sine1->getIn()["freq"]]->connect(input1->outs[input1->getOut()["value"]]);
        speaker1->ins[speaker1->getIn()["sound"]]->connect(sine1->outs[sine1->getOut()["sine"]]);
        g_sketch.appendCom(input1);
        g_sketch.appendCom(sine1);
        g_sketch.appendCom(speaker1);
    }
*/

    while (!cin.eof())
    {
        char ch;
        string requestJson;
        while (cin >> ch && ch != '\0')
        {
            requestJson += ch;
        }

        try
        {
            Request request;
            stringstream stream(requestJson);
            {
                cereal::JSONInputArchive archive(stream);
                archive(CEREAL_NVP(request));
            }
            execute(request);
        }
        catch (exception &e)
        {
            ErrorResponse response;

            response.error = e.what();
            respond(response);
        }
    }

    return 0;
}

void execute(Request &request)
{
    try
    {
        if (!request.args.size())
        {
            throw runtime_error("");
        }

        // ここの部分を関数ポインタ配列で書き直す。
        if (request.args[0] == "addcom")
        {
            addcom(request.args);
            return;
        }
        else if (request.args[0] == "lscom")
        {
            lscom(request.args);
            return;
        }
        else if (request.args[0] == "lsport")
        {
            lsport(request.args);
            return;
        }

        throw runtime_error("不明なコマンドです。\n");
    }
    catch (exception &e)
    {
        ErrorResponse response;

        response.error = e.what();
        respond(response);
    }
}

template <typename T>
void respond(T &response)
{
    stringstream stream;
    {
        cereal::JSONOutputArchive archive(stream);
        archive(CEREAL_NVP(response));
    }
    cout << stream.str() << '\0';
}

void addcom(vector<string> &args)
{
    if (args.size() != 2)
    {
        throw runtime_error("構文: addcom (部品名)\n");
    }

    Component *com = newCom(args[1]);
    if (!com)
    {
        throw runtime_error("不明な部品名です。\n");
    }

    g_sketch.appendCom(com);

    AddcomResponse response;
    response.uuid = uuidStr(com->id);
    respond(response);
}

void lscom(vector<string> &args)
{
    LscomResponse response;

    for (Component_up &com : g_sketch.coms)
    {
        LscomResponse::Component comResponse;

        comResponse.uuid = uuidStr(com->id);
        comResponse.type = com->com_name;
        response.components.push_back(comResponse);
    }

    respond(response);
}

void lsport(vector<string> &args)
{
    if (args.size() != 2)
    {
        throw runtime_error("構文: lsport (部品の UUID)\n");
    }

    uuid_t uuid;
    if (parseUuid(args[1], &uuid))
    {
        throw runtime_error("不正な UUID です。\n");
    }

    Component *com = searchCom(uuid);
    if (!com)
    {
        throw runtime_error("存在しない部品です。\n");
    }

    int i;
    LsportResponse response;
    vector<string> port_types;

    i = 0;
    port_types = com->getIn();
    for (PortIn_p in : com->ins)
    {
        LsportResponse::PortIn inResponse;

        inResponse.uuid = uuidStr(in->id);
        inResponse.type = port_types[i++];
        response.inputs.push_back(inResponse);
    }

    i = 0;
    port_types = com->getOut();
    for (PortOut_p out : com->outs)
    {
        LsportResponse::PortOut outResponse;

        outResponse.uuid = uuidStr(out->id);
        outResponse.type = port_types[i++];
        response.outputs.push_back(outResponse);
    }

    respond(response);
}

/*EMSCRIPTEN_KEEPALIVE void onSimStart()
{
    g_sketch.onSimStart();
}

EMSCRIPTEN_KEEPALIVE float *onAudioProcess(double dt)
{
    // スキップフレームは未実装。
    try
    {
        float *buffer = g_buffer;

        for (int i = 0; i < G_BUFFER_SIZE; i++)
        {
            g_spout = 0.0;
            g_spcount = 0;
            g_sketch.onChangeTime(dt);
            *(buffer++) = g_spcount ? g_spout / g_spcount : 0.0;
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        return NULL;
    }

    return g_buffer;
}

EMSCRIPTEN_KEEPALIVE void onSimEnd()
{
    g_sketch.onSimEnd();
}

EMSCRIPTEN_KEEPALIVE const char *export_()
{
    g_sketch.exportExtends();

    stringstream stream;
    {
        cereal::JSONOutputArchive archive(stream);
        archive(cereal::make_nvp("sketch", g_sketch));
    }

    return stream.str().c_str();
}*/

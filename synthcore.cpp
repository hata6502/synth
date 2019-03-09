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

    for (int i = 1; i < 50; i++)
    {
        Component *speaker2 = newCom("Speaker");
        g_sketch.appendCom(speaker2);

        speaker2->ins[speaker2->getIn()["sound"]]->connect(speaker1->outs[speaker1->getOut()["thru"]]);

        speaker1 = speaker2;
    }*/

    string requestJson;
    while (!cin.eof())
    {
        char ch;

        cin >> ch;
        if (ch == '\0')
        {
            Request request;

            stringstream stream(requestJson);
            try
            {
                cereal::JSONInputArchive archive(stream);
                archive(CEREAL_NVP(request));
            }
            catch (exception &e)
            {
                ErrorResponse response;

                response.error = e.what();
                respond(response);
            }
            requestJson = "";

            execute(request);
        }
        else
            requestJson += ch;
    }

    return 0;
}

void execute(Request &request)
{
    try
    {
        if (!request.args.size())
        {
            throw runtime_error("構文: (コマンド) (引数1) (引数2) ...");
        }

        // ここの部分を関数ポインタ配列で書き直す。
        if (request.args[0] == "addcom")
        {
            addcom(request.args);
            return;
        }

        throw runtime_error("不明なコマンドです。");
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
        throw runtime_error("構文: addcom (部品名)");

    Component *com = newCom(args[1]);
    if (!com)
        throw runtime_error("不明な部品名です。");

    g_sketch.appendCom(com);

    AddcomResponse response;
    response.uuid = uuidStr(com->id);
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

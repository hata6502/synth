#include <core/core.hpp>
#include <component/component.hpp>
#include <command/command.hpp>
#include <io.hpp>

#include <exception>
#include <stdexcept>

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

int main(int argc, char **argv)
{
    initCom();

    while (!eof())
    {
        try
        {
            Request request = receive();
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
    if (!request.args.size())
    {
        throw runtime_error("");
    }

    for (Command &command : g_commands)
    {
        if (request.args[0] == command.name)
        {
            command.handler(request.args);
            return;
        }
    }

    throw runtime_error("不明なコマンドです。\n");
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

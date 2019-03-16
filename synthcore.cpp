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

/*
EMSCRIPTEN_KEEPALIVE float *onAudioProcess(double dt)
{

    return g_buffer;
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

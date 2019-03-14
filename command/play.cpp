#include "command.hpp"

#include <io/io.hpp>
#include <core/core.hpp>

void playHandler(vector<string> &args)
{
    if (!g_sketch.onSim)
    {
        g_sketch.onSimStart();
    }

    // この処理がデバイス依存になる
    /*float *buffer = g_buffer;

    for (int i = 0; i < G_BUFFER_SIZE; i++)
    {
        g_spout = 0.0;
        g_spcount = 0;
        g_sketch.onChangeTime(dt);
        *(buffer++) = g_spcount ? g_spout / g_spcount : 0.0;
    }*/

    EmptyResponse response;
    respond(response);
}

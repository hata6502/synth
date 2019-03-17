#include "command.hpp"

#include <io.hpp>
#include <core/core.hpp>

void stopHandler(vector<string> &args)
{
    g_sketch.onSimEnd();

    EmptyResponse response;
    respond(response);
}
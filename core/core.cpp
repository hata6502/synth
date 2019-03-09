#include "core.hpp"

double g_spout;
int g_spcount;
Sketch g_sketch;
float g_buffer[G_BUFFER_SIZE];

string uuidStr(uuid_t uuid)
{
    char uuid_str[37];

    uuid_unparse_lower(uuid, uuid_str);
    return string(uuid_str);
}

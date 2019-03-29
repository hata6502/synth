#include "core.hpp"

double g_spout;
int g_spcount;

Sketch g_sketch;

string uuidStr(uuid_t uuid)
{
    char uuid_str[37];

    uuid_unparse_lower(uuid, uuid_str);
    return string(uuid_str);
}

int parseUuid(string &uuid_str, uuid_t *uuid)
{
    return uuid_parse(uuid_str.c_str(), *uuid);
}

Component *searchCom(uuid_t uuid)
{
    for (Component_up &com : g_sketch.coms)
    {
        if (!uuid_compare(uuid, com->id))
        {
            return com.get();
        }
    }

    return nullptr;
}

PortIn_p searchPortIn(uuid_t uuid)
{
    for (Component_up &com : g_sketch.coms)
    {
        for (PortIn_p in : com->ins)
        {
            if (!uuid_compare(uuid, in->id))
            {
                return in;
            }
        }
    }

    return PortIn_p(nullptr);
}

PortOut_p searchPortOut(uuid_t uuid)
{
    for (Component_up &com : g_sketch.coms)
    {
        for (PortOut_p out : com->outs)
        {
            if (!uuid_compare(uuid, out->id))
            {
                return out;
            }
        }
    }

    return PortOut_p(nullptr);
}

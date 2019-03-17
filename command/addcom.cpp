#include "command.hpp"

#include <io.hpp>
#include <core/core.hpp>
#include <component/component.hpp>

void addcomHandler(vector<string> &args)
{
    if (args.size() != 2)
    {
        throw runtime_error("構文: addcom (部品名)");
    }

    Component *com = newCom(args[1]);
    if (!com)
    {
        throw runtime_error("不明な部品名です。");
    }

    g_sketch.appendCom(com);

    AddcomResponse response;
    response.uuid = uuidStr(com->id);
    respond(response);
}

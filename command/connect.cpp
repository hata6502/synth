#include "command.hpp"

#include <io.hpp>
#include <core/core.hpp>

void connectHandler(vector<string> &args)
{
    if (args.size() != 3)
    {
        throw runtime_error("構文: connect (出力ポート UUID) (入力ポート UUID)");
    }

    uuid_t out_uuid, in_uuid;
    if (parseUuid(args[1], &out_uuid))
    {
        throw runtime_error("不正な出力ポート UUID です。");
    }
    if (parseUuid(args[2], &in_uuid))
    {
        throw runtime_error("不正な入力ポート UUID です。");
    }

    PortOut_p out = searchPortOut(out_uuid);
    if (!out)
    {
        throw runtime_error("存在しない出力ポートです。");
    }
    PortIn_p in = searchPortIn(in_uuid);
    if (!in)
    {
        throw runtime_error("存在しない入力ポートです。");
    }

    in->connect(out);

    EmptyResponse response;
    respond(response);
}
#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

void disconnHandler(vector<string> &args) {
  if (args.size() != 2) {
    throw runtime_error("構文: connect (InPort UUID)");
  }

  uuid_t uuid;
  if (parseUuid(args[1], &uuid)) {
    throw runtime_error("不正な InPort UUID です。");
  }

  PortIn_p in = searchPortIn(uuid);
  if (!in) {
    throw runtime_error("存在しない InPort です。");
  }

  in->disconnect();

  EmptyResponse response;
  respond(response);
}

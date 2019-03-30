#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

void callHandler(vector<string> &args) {
  if (args.size() < 3) {
    throw runtime_error("構文: call (Component UUID) (Call Command) ...");
  }

  uuid_t uuid;
  if (parseUuid(args[1], &uuid)) {
    throw runtime_error("不正な Component UUID です。");
  }

  Component *com = searchCom(uuid);
  if (!com) {
    throw runtime_error("存在しない Component です。");
  }

  for (CallCommand &call_command : com->getCallCommands()) {
    if (args[2] == call_command.name) {
      // 少し重そう
      vector<string> call_args = args;
      call_args.erase(call_args.begin(), call_args.begin() + 2);

      call_command.handler(com, call_args);
      return;
    }
  }

  throw runtime_error("不明な Call Command です。");
}

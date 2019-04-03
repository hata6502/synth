// Copyright 2019 BlueHood

#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

using std::vector, std::string, std::runtime_error;

void rmcomHandler(const vector<string> &args) {
  if (args.size() != 2) {
    throw runtime_error("Syntax: rmcom (Component UUID)");
  }

  uuid_t uuid;
  if (parseUuid(args[1], &uuid)) {
    throw runtime_error("不正な Component UUID です。");
  }

  Component *com = searchCom(uuid);
  if (!com) {
    throw runtime_error("存在しない Component です。");
  }

  g_sketch.removeCom(com);

  EmptyResponse response;
  respond(response);
}

// Copyright 2019 BlueHood

#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

void disconnHandler(const vector<string> &args) {
  if (args.size() != 2) {
    throw runtime_error("Syntax: connect (InPort UUID)");
  }

  uuid_t uuid;
  if (parseUuid(args[1], &uuid)) {
    throw runtime_error("不正な InPort UUID です。");
  }

  InPort_p in = searchInPort(uuid);
  if (!in) {
    throw runtime_error("存在しない InPort です。");
  }

  in->disconnect();

  EmptyResponse response;
  respond(response);
}

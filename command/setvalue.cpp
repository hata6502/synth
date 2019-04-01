// Copyright 2019 BlueHood

#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

void setvalueHandler(const vector<string> &args) {
  if (args.size() != 3) {
    throw runtime_error("Syntax: setvalue (InPort UUID) (value)");
  }

  uuid_t uuid;
  if (parseUuid(args[1], &uuid)) {
    throw runtime_error("不正な InPort UUID です。");
  }

  InPort_p in = searchInPort(uuid);
  if (!in) {
    throw runtime_error("存在しない InPort です。");
  }

  in->val = stod(args[2]);

  EmptyResponse response;
  respond(response);
}

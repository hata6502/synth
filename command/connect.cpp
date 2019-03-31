// Copyright 2019 BlueHood

#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

void connectHandler(const vector<string> &args) {
  if (args.size() != 3) {
    throw runtime_error("構文: connect (OutPort UUID) (InPort UUID)");
  }

  uuid_t out_uuid, in_uuid;
  if (parseUuid(args[1], &out_uuid)) {
    throw runtime_error("不正な OutPort UUID です。");
  }
  if (parseUuid(args[2], &in_uuid)) {
    throw runtime_error("不正な InPort UUID です。");
  }

  OutPort_p out = searchOutPort(out_uuid);
  if (!out) {
    throw runtime_error("存在しない OutPort です。");
  }
  InPort_p in = searchInPort(in_uuid);
  if (!in) {
    throw runtime_error("存在しない InPort です。");
  }

  in->connect(out);

  EmptyResponse response;
  respond(response);
}

// Copyright 2019 BlueHood

#include "command.hpp"

#include <component/component.hpp>
#include <core/core.hpp>
#include <io.hpp>

using std::vector, std::string, std::runtime_error;

void addcomHandler(const vector<string> &args) {
  if (args.size() != 2) {
    throw runtime_error("Syntax: addcom (Component Type)");
  }

  Component *com = newCom(args[1]);
  if (!com) {
    throw runtime_error("不明な Component Type です。");
  }

  g_sketch.appendCom(com);

  AddcomResponse response;
  response.uuid = uuidStr(com->id);
  respond(response);
}

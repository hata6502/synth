// Copyright 2019 BlueHood

#include <string>

#include "core.hpp"

using std::string;

double g_spout;
int g_spcount;
Sketch g_sketch;

string uuidStr(uuid_t uuid) {
  char uuid_str[37];

  uuid_unparse_lower(uuid, uuid_str);
  return string(uuid_str);
}

int parseUuid(const string &uuid_str, uuid_t *uuid) {
  return uuid_parse(uuid_str.c_str(), *uuid);
}

Component *searchCom(uuid_t uuid) {
  for (Component_up &com : g_sketch.coms) {
    if (!uuid_compare(uuid, com->id)) {
      return com.get();
    }
  }

  return nullptr;
}

InPort *searchInPort(uuid_t uuid) {
  for (Component_up &com : g_sketch.coms) {
    for (InPort_up &in : com->ins) {
      if (!uuid_compare(uuid, in->id)) {
        return in.get();
      }
    }
  }

  return nullptr;
}

OutPort *searchOutPort(uuid_t uuid) {
  for (Component_up &com : g_sketch.coms) {
    for (OutPort_up &out : com->outs) {
      if (!uuid_compare(uuid, out->id)) {
        return out.get();
      }
    }
  }

  return nullptr;
}

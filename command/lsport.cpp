// Copyright 2019 BlueHood

#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

using std::vector, std::string, std::runtime_error;

void lsportHandler(const vector<string> &args) {
  if (args.size() != 2) {
    throw runtime_error("Syntax: lsport (Component UUID)");
  }

  uuid_t uuid;
  if (parseUuid(args[1], &uuid)) {
    throw runtime_error("不正な Component UUID です。");
  }

  Component *com = searchCom(uuid);
  if (!com) {
    throw runtime_error("存在しない Component です。");
  }

  int i;
  LsportResponse response;
  vector<string> port_types;

  i = 0;
  port_types = com->getIn();
  for (InPort_up &in : com->ins) {
    LsportResponse::InPort inResponse;

    inResponse.uuid = uuidStr(in->id);
    inResponse.type = port_types[i++];
    inResponse.value = in->val;
    if (in->src) {
      inResponse.source = uuidStr(in->src->id);
    } else {
      inResponse.source = "";
    }
    response.inputs.push_back(inResponse);
  }

  i = 0;
  port_types = com->getOut();
  for (OutPort_up &out : com->outs) {
    LsportResponse::OutPort outResponse;

    outResponse.uuid = uuidStr(out->id);
    outResponse.type = port_types[i++];
    outResponse.value = out->getVal();
    for (InPort *to : out->tos) {
      outResponse.tos.push_back(uuidStr(to->id));
    }
    response.outputs.push_back(outResponse);
  }

  respond(response);
}

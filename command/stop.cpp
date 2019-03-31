// Copyright 2019 BlueHood

#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

void stopHandler(const vector<string> &args) {
  g_sketch.onSimEnd();

  EmptyResponse response;
  respond(response);
}

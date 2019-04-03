// Copyright 2019 BlueHood

#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

using std::vector, std::string;

void stopHandler(const vector<string> &args) {
  g_sketch.onSimEnd();

  EmptyResponse response;
  respond(response);
}

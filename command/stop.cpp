#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

void stopHandler(vector<string> &args) {
  g_sketch.onSimEnd();

  EmptyResponse response;
  respond(response);
}

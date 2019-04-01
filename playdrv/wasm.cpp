// Copyright 2019 BlueHood

#include <cstdint>

#include "io.hpp"
#include <cereal/cereal.hpp>

using std::vector, std::string;

#define G_BUFFER_SIZE 2048
static float g_buffer[G_BUFFER_SIZE];
static int g_buffer_index;

struct PlayResponse {
  uintptr_t address;

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    archive(CEREAL_NVP(address));
  }
};

namespace WasmPlayDriver {
void init(const vector<string> &args) { g_buffer_index = 0; }

bool isContinue() { return g_buffer_index < G_BUFFER_SIZE; }

void store(double sample) {
  g_buffer[g_buffer_index++] = static_cast<float>(sample);
}

void respond() {
  PlayResponse response;
  response.address = reinterpret_cast<uintptr_t>(g_buffer);
  respond(response);
}

} // namespace WasmPlayDriver

// Copyright 2019 BlueHood

#include <vector>

#include "io.hpp"
#include <cereal/cereal.hpp>

using std::vector, std::string, std::runtime_error;

#define MAX_BUFFER_SIZE (256 * 256 * 16)

struct PlayResponse {
  vector<double> samples;

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    archive(CEREAL_NVP(samples));
  }
};

static PlayResponse g_response;
static int g_buffer_size;

namespace JsonPlayDriver {
void init(const vector<string> &args) {
  if (args.size() < 4) {
    throw runtime_error(
        "Syntax: play (sampling rate) Json (number of samples)");
  }

  int request_buffer_size = stoi(args[3]);
  if (request_buffer_size < 0 || request_buffer_size > MAX_BUFFER_SIZE) {
    throw runtime_error("サンプル数の範囲オーバーです。");
  }
  g_buffer_size = request_buffer_size;

  g_response.samples.clear();
}

bool isContinue() { return g_response.samples.size() < g_buffer_size; }

void store(double sample) { g_response.samples.push_back(sample); }

void respond() { respond(g_response); }

} // namespace JsonPlayDriver

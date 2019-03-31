// Copyright 2019 BlueHood

#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>

void playHandler(const vector<string> &args) {
  if (args.size() < 2) {
    throw runtime_error("構文: play (sampling rate) ...");
  }
  double dt = 1.0 / stoi(args[1]);

  if (!g_sketch.onSim) {
    g_sketch.onSimStart();
  }

  initPlay(args);

  while (isContinuePlay()) {
    g_spout = 0.0;
    g_spcount = 0;
    g_sketch.onChangeTime(dt);
    storePlay(g_spcount ? g_spout / g_spcount : 0.0);
  }

  respondPlay();
}

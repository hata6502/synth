// Copyright 2019 BlueHood

#include "command.hpp"

#include <core/core.hpp>
#include <io.hpp>
#include <playdrv/playdrv.hpp>

using std::vector, std::string, std::runtime_error;

void playHandler(const vector<string> &args) {
  if (args.size() < 3) {
    throw runtime_error("Syntax: play (sampling rate) (Play Driver) ...");
  }

  double dt = 1.0 / stoi(args[1]);

  PlayDriver *driver = nullptr;
  for (PlayDriver &search : g_playDrivers) {
    if (search.name == args[2]) {
      driver = &search;
      break;
    }
  }
  if (!driver) {
    throw runtime_error("不明な Play Driver です。");
  }

  driver->init(args);

  if (!g_sketch.onSim) {
    g_sketch.onSimStart();
  }

  while (driver->isContinue()) {
    g_spout = 0.0;
    g_spcount = 0;
    g_sketch.onChangeTime(dt);
    driver->store(g_spcount ? g_spout / g_spcount : 0.0);
  }

  driver->respond();
}

// Copyright 2019 BlueHood

#pragma once

#include <string>
#include <vector>

struct PlayDriver {
  std::string name;
  void (*init)(const std::vector<std::string> &args);
  bool (*isContinue)();
  void (*store)(double sample);
  void (*respond)();
};

extern std::vector<PlayDriver> g_playDrivers;

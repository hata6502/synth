// Copyright 2019 BlueHood

#pragma once

#include <string>
#include <vector>

struct Command {
  std::string name;
  void (*handler)(const std::vector<std::string> &args);
};

extern std::vector<Command> g_commands;

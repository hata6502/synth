#pragma once

#include <string>
#include <vector>

using namespace std;

struct Command {
  string name;
  void (*handler)(vector<string> &args);
};

extern vector<Command> g_commands;
#pragma once

#include <vector>
#include <string>

using namespace std;

struct Command
{
    string name;
    void (*handler)(vector<string> &args);
};

extern vector<Command> g_commands;
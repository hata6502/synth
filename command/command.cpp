// Copyright 2019 BlueHood

#include "command.hpp"

#include <string>
#include <vector>

using std::vector, std::string;

void addcomHandler(const vector<string> &args);
void lscomHandler(const vector<string> &args);
void lsportHandler(const vector<string> &args);
void connectHandler(const vector<string> &args);
void playHandler(const vector<string> &args);
void stopHandler(const vector<string> &args);
void callHandler(const vector<string> &args);
void rmcomHandler(const vector<string> &args);
void disconnHandler(const vector<string> &args);
void setvalueHandler(const vector<string> &args);

#define registerCommand(name)                                                  \
  { #name, name##Handler }

vector<Command> g_commands = {
    registerCommand(addcom),   registerCommand(lscom), registerCommand(lsport),
    registerCommand(connect),  registerCommand(play),  registerCommand(stop),
    registerCommand(call),     registerCommand(rmcom), registerCommand(disconn),
    registerCommand(setvalue),
};

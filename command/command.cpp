#include "command.hpp"

void addcomHandler(vector<string> &args);
void lscomHandler(vector<string> &args);
void lsportHandler(vector<string> &args);
void connectHandler(vector<string> &args);

#define registerCommand(name) \
    {                         \
#name, name##Handler  \
    }

vector<Command> g_commands = {
    registerCommand(addcom),
    registerCommand(lscom),
    registerCommand(lsport),
    registerCommand(connect),
};

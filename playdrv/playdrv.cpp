// Copyright 2019 BlueHood

#include "playdrv.hpp"

#include <string>
#include <vector>

using std::string, std::vector;

#define includePlayDriver(name)                                                \
  namespace name##PlayDriver {                                                 \
    void init(const vector<string> &args);                                     \
    bool isContinue();                                                         \
    void store(double sample);                                                 \
    void respond();                                                            \
  }

includePlayDriver(Json);
includePlayDriver(Wasm);

#define registerPlayDriver(name)                                               \
  {                                                                            \
#name, name##PlayDriver::init, name##PlayDriver::isContinue,               \
        name##PlayDriver::store, name##PlayDriver::respond,                    \
  }

vector<PlayDriver> g_playDrivers = {
    registerPlayDriver(Json),
    registerPlayDriver(Wasm),
};

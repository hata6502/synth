#pragma once

#include "component.hpp"
#include "in_port.hpp"
#include "out_port.hpp"
#include "sketch.hpp"

#include <string>
#include <uuid/uuid.h>

extern double g_spout;
extern int g_spcount;
extern Sketch g_sketch;

string uuidStr(uuid_t uuid);
int parseUuid(string &uuid_str, uuid_t *uuid);
Component *searchCom(uuid_t uuid);
InPort_p searchInPort(uuid_t uuid);
OutPort_p searchOutPort(uuid_t uuid);

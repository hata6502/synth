#pragma once

#include "component.hpp"
#include "port_in.hpp"
#include "port_out.hpp"
#include "sketch.hpp"

#include <string>
#include <uuid/uuid.h>

extern double g_spout;
extern int g_spcount;
extern Sketch g_sketch;

string uuidStr(uuid_t uuid);
int parseUuid(string &uuid_str, uuid_t *uuid);
Component *searchCom(uuid_t uuid);
PortIn_p searchPortIn(uuid_t uuid);
PortOut_p searchPortOut(uuid_t uuid);

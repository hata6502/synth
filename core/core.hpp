#pragma once

#define G_BUFFER_SIZE 2048

#include "sketch.hpp"
#include "component.hpp"
#include "port_in.hpp"
#include "port_out.hpp"

#include <string>
#include <uuid/uuid.h>

extern double g_spout;
extern int g_spcount;
extern Sketch g_sketch;
extern float g_buffer[G_BUFFER_SIZE];

string uuidStr(uuid_t uuid);
int parseUuid(string &uuid_str, uuid_t *uuid);
Component *searchCom(uuid_t uuid);

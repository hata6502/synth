#pragma once

#include "sketch.hpp"
#include "component.hpp"
#include "port_in.hpp"
#include "port_out.hpp"

#define G_BUFFER_SIZE 2048

extern double g_spout;
extern int g_spcount;

extern Sketch g_sketch;
extern float g_buffer[G_BUFFER_SIZE];

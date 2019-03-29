#pragma once

#include "amplifier.hpp"
#include "input.hpp"
#include "sine.hpp"
#include "speaker.hpp"

void initCom();
Component *newCom(string com_name);

#pragma once

#include "speaker.hpp"
#include "input.hpp"
#include "sine.hpp"
#include "amplifier.hpp"

void initCom();
Component *newCom(string com_name);

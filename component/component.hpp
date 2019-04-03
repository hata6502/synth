// Copyright 2019 BlueHood

#pragma once

#include <string>

#include "amplifier.hpp"
#include "sine.hpp"
#include "speaker.hpp"

void initCom();
Component *newCom(std::string com_name);

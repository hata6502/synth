// Copyright 2019 BlueHood

#pragma once
class Sine;

#include <deque>
#include <string>
#include <vector>

#include <core/core.hpp>

class Amplifier : public Component {
public:
  Amplifier();
  virtual std::vector<std::string> getIn();
  virtual std::vector<std::string> getOut();
  virtual void onChangeIn(std::deque<Component *> *chcoms);
};

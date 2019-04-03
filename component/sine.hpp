// Copyright 2019 BlueHood

#pragma once
class Sine;

#include <deque>
#include <string>
#include <vector>

#include <core/core.hpp>

class Sine : public Component {
  double phase;

public:
  Sine();
  virtual std::vector<std::string> getIn();
  virtual std::vector<std::string> getOut();
  virtual void onSimStart();
  virtual void onChangeTime(double dt, std::deque<Component *> *chcoms);
};

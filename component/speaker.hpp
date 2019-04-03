// Copyright 2019 BlueHood

#pragma once
class Speaker;

#include <deque>
#include <string>
#include <vector>

#include <core/core.hpp>

class Speaker : public Component {
public:
  Speaker();
  virtual std::vector<std::string> getIn();
  virtual std::vector<std::string> getOut();
  virtual void onChangeTime(double dt, std::deque<Component *> *chcoms);
};

#pragma once
class Sine;

#include <core/core.hpp>

class Sine : public Component
{
  double phase;

public:
  Sine();
  virtual vector<string> getIn();
  virtual vector<string> getOut();
  virtual void onSimStart();
  virtual void onChangeTime(double dt, deque<Component *> &chcoms);
};

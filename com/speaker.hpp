#pragma once
class Speaker;

#include <core/core.hpp>

class Speaker : public Component
{
public:
  Speaker();
  virtual map<string, int> getIn();
  virtual map<string, int> getOut();
  virtual void onChangeTime(double dt, deque<Component *> &chcoms);
};

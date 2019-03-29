#pragma once
class Speaker;

#include <core/core.hpp>

class Speaker : public Component {
public:
  Speaker();
  virtual vector<string> getIn();
  virtual vector<string> getOut();
  virtual void onChangeTime(double dt, deque<Component *> &chcoms);
};

#pragma once
class Sine;

#include <core/core.hpp>

class Amplifier : public Component {
public:
  Amplifier();
  virtual vector<string> getIn();
  virtual vector<string> getOut();
  virtual void onChangeIn(deque<Component *> &chcoms);
};

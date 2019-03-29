#pragma once
class Input;

#include <core/core.hpp>

class Input : public Component {
  double val;

public:
  Input();
  virtual vector<string> getIn();
  virtual vector<string> getOut();
  virtual vector<CallCommand> &getCallCommands();
  double setValue(double value);
  virtual void onChangeTime(double dt, deque<Component *> &chcoms);
  virtual void exportExtends();
};

#pragma once
class Sine;

#include <core/core.hpp>

class Amplifier : public Component
{
  public:
    Amplifier();
    virtual map<string, int> getIn();
    virtual map<string, int> getOut();
    virtual void onChangeIn(deque<Component *> &chcoms);
};

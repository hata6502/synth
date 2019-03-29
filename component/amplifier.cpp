#include "amplifier.hpp"

#define IN_IN_1 0
#define IN_IN_2 1
vector<string> Amplifier::getIn() { return vector<string>{"in_1", "in_2"}; }

#define OUT_AMP 0
vector<string> Amplifier::getOut() { return vector<string>{"amp"}; }

Amplifier::Amplifier() : Component() {
  this->initPort(this->getIn().size(), this->getOut().size());
  this->com_name = string(__FUNCTION__);
}

void Amplifier::onChangeIn(deque<Component *> &chcoms) {
  Component::onChangeIn(chcoms);
  this->outs[OUT_AMP]->setLatch(this->ins[IN_IN_1]->val *
                                this->ins[IN_IN_2]->val);
  this->update(chcoms);
}

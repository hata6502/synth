#include "amplifier.hpp"

#define IN_IN_1 0
#define IN_IN_2 1
map<string, int> Amplifier::getIn()
{
    return map<string, int>{{"in_1", IN_IN_1}, {"in_2", IN_IN_2}};
}

#define OUT_AMP 0
map<string, int> Amplifier::getOut()
{
    return map<string, int>{{"amp", OUT_AMP}};
}

Amplifier::Amplifier() : Component()
{
    this->initPort(this->getIn().size(), this->getOut().size());
    this->com_name = string(__FUNCTION__);
}

void Amplifier::onChangeIn(deque<Component *> &chcoms)
{
    Component::onChangeIn(chcoms);
    this->outs[OUT_AMP]->setLatch(this->ins[IN_IN_1]->val * this->ins[IN_IN_2]->val);
    this->update(chcoms);
}

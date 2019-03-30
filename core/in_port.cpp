#include "in_port.hpp"

typedef shared_ptr<InPort> InPort_p;

InPort::InPort() : com(nullptr), src(OutPort_p(nullptr)), int_(false) {
  uuid_generate(this->id);
  this->initVal();
}

void InPort::initVal() { this->val = 0.0; }

void InPort::connect(OutPort_p &src) {
  this->disconnect();
  this->src = src;
  src->tos.push_back(this);
}

void InPort::disconnect() {
  if (this->src) {
    InPort *dis = this;
    this->src->tos.erase(
        remove_if(this->src->tos.begin(), this->src->tos.end(),
                  [&](InPort *to) -> bool { return to == dis; }),
        this->src->tos.end());
    this->src = OutPort_p(nullptr);
  }
}

/*
var InPort = class{
        import(im){
                this.id = im.id;
                this.int = im.int;
                return { id: this.id, inst: this };
        }
};
*/
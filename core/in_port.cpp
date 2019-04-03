// Copyright 2019 BlueHood

#include "in_port.hpp"

InPort::InPort() : com(nullptr), src(nullptr), int_(false) {
  uuid_generate(this->id);
  // this->initVal();
}

// void InPort::initVal() { this->val = 0.0; }

void InPort::connect(OutPort *src) {
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
    this->src = nullptr;
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

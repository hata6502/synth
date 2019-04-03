// Copyright 2019 BlueHood

#include <deque>
#include <string>
#include <vector>

#include "out_port.hpp"

using std::deque, std::string, std::vector;

OutPort::OutPort() : int_(false) {
  uuid_generate(this->id);
  // this->initVal();
}

double OutPort::getVal() { return this->val; }

double OutPort::setLatch(double value) { return this->latch = value; }

/*void OutPort::initVal() {
  this->latch = 0.0;
  this->val = 0.0;
}*/

void OutPort::update(deque<Component *> *chcoms) {
  if (this->val != this->latch) {
    this->val = this->latch;

    for (InPort *to : this->tos) {
      to->val = this->val;
      chcoms->push_back(to->com); // ここで重複を確認する
    }
  }
}

void OutPort::disconnectAll() {
  while (!this->tos.empty()) {
    this->tos[0]->disconnect();
  }
}

vector<string> OutPort::exportTos() {
  vector<string> tos;
  char uuid_str[37];

  for (InPort *to : this->tos) {
    uuid_unparse_lower(to->id, uuid_str);
    tos.push_back(string(uuid_str));
  }

  return tos;
}

/*
var OutPort = class{


        import(im){
                this.to_ids = im.tos;
                this.int = im.int;
        }

        connectById(lut){
                this.disconnectAll();
                this.to_ids.forEach((to_id) => {
                        for(var i = 0; i<lut.length; i++){
                                if (to_id==lut[i].id){
                                        lut[i].inst.connect(this);
                                        break;
                                }
                        }
                });
        }
};
*/

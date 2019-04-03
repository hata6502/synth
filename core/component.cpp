// Copyright 2019 BlueHood

#include "component.hpp"

#include <deque>
#include <map>
#include <stdexcept>
#include <string>

using std::vector, std::deque, std::string, std::map, std::runtime_error;

Component::Component() : loopcnt(0) {
  /*
          this.ui_class = UiComponent;
*/
  uuid_generate(this->id);
  this->com_name = string(__FUNCTION__);
}

vector<InPort *> Component::getIntIns() {
  vector<InPort *> int_ins;

  for (InPort_up &in_ : this->ins) {
    if (in_->int_) {
      int_ins.push_back(in_.get());
    }
  }
  return int_ins;
}

vector<OutPort *> Component::getIntOuts() {
  vector<OutPort *> int_outs;

  for (OutPort_up &out : this->outs) {
    if (out->int_) {
      int_outs.push_back(out.get());
    }
  }
  return int_outs;
}

vector<string> Component::getIn() { return vector<string>(); }

vector<string> Component::getOut() { return vector<string>(); }

vector<CallCommand> &Component::getCallCommands() {
  static vector<CallCommand> call_commands;
  return call_commands;
}

void Component::appendIn(InPort *in_) {
  this->ins.push_back(InPort_up(in_));
  in_->com = this;
}

void Component::removeIn(InPort *rm) {
  this->ins.erase(
      remove_if(this->ins.begin(), this->ins.end(),
                [&](InPort_up &in_) -> bool { return in_.get() == rm; }),
      this->ins.end());
  rm->com = nullptr;
}

void Component::clearIn() { this->ins.clear(); }

void Component::appendOut(OutPort *out) {
  this->outs.push_back(OutPort_up(out));
}

void Component::removeOut(OutPort *rm) {
  this->outs.erase(
      remove_if(this->outs.begin(), this->outs.end(),
                [&](OutPort_up &out) -> bool { return out.get() == rm; }),
      this->outs.end());
}

void Component::clearOut() { this->outs.clear(); }

void Component::initPort(int in_n, int out_n) {
  this->clearIn();
  for (int i = 0; i < in_n; i++) {
    this->appendIn(new InPort());
  }

  this->clearOut();
  for (int i = 0; i < out_n; i++) {
    this->appendOut(new OutPort());
  }
}

void Component::update(deque<Component *> *chcoms) {
  for (OutPort_up &out : this->outs) {
    out->update(chcoms);
  }
}

void Component::onSimStart() {
  /*for (InPort_p &in_ : this->ins) {
    in_->initVal();
  }
  for (OutPort_p &out : this->outs) {
    out->initVal();
  }*/
}

void Component::onChangeIn(deque<Component *> *chcoms) {
  if (++this->loopcnt >= 256) {
    throw runtime_error("無限ループが発生しました。問題を解決するために Buffer "
                        "を入れてください。");
  }
}

void Component::onChangeTime(double dt, deque<Component *> *chcoms) {
  this->loopcnt = 0;
}

void Component::exportExtends() { this->extends = map<string, string>(); }

/*
var Component = class{


        import(im){
                var lut = [];

                this.id = im.id;
                this.clearIn();
                im.ins.forEach((im) => {
                        var in_ = new InPort();
                        lut.push(in_.import(im));
                        this.appendIn(in_);
                });

                this.clearOut();
                im.outs.forEach((im) => {
                        var out = new OutPort();
                        out.import(im);
                        this.appendOut(out);
                });

                return lut;
        }

        connectById(lut){
                this.outs.forEach((out) => {
                        out.connectById(lut);
                });
        }


};

*/

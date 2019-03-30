#include "component.hpp"

#include <stdexcept>

Component::Component() : loopcnt(0) {
  /*
          this.ui_class = UiComponent;
*/
  uuid_generate(this->id);
  this->com_name = string(__FUNCTION__);
}

vector<InPort_p> Component::getIntIns() {
  vector<InPort_p> int_ins;

  for (InPort_p &in_ : this->ins) {
    if (in_->int_) {
      int_ins.push_back(in_);
    }
  }
  return int_ins;
}

vector<OutPort_p> Component::getIntOuts() {
  vector<OutPort_p> int_outs;

  for (OutPort_p &out : this->outs) {
    if (out->int_) {
      int_outs.push_back(out);
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

void Component::appendIn(InPort_p in_) {
  this->ins.push_back(in_);
  in_->com = this;
}

void Component::removeIn(InPort_p &rm) {
  this->ins.erase(remove_if(this->ins.begin(), this->ins.end(),
                            [&](InPort_p &in_) -> bool { return in_ == rm; }),
                  this->ins.end());
  rm->com = nullptr;
}

void Component::clearIn() { this->ins.clear(); }

void Component::appendOut(OutPort_p out) { this->outs.push_back(out); }

void Component::removeOut(OutPort_p &rm) {
  this->outs.erase(remove_if(this->outs.begin(), this->outs.end(),
                             [&](OutPort_p &out) -> bool { return out == rm; }),
                   this->outs.end());
}

void Component::clearOut() { this->outs.clear(); }

void Component::initPort(int in_n, int out_n) {
  this->clearIn();
  for (int i = 0; i < in_n; i++) {
    this->appendIn(InPort_p(new InPort()));
  }

  this->clearOut();
  for (int i = 0; i < out_n; i++) {
    this->appendOut(OutPort_p(new OutPort()));
  }
}

void Component::update(deque<Component *> &chcoms) {
  for (OutPort_p &out : this->outs) {
    out->update(chcoms);
  }
}

void Component::onSimStart() {
  for (InPort_p &in_ : this->ins) {
    in_->initVal();
  }
  for (OutPort_p &out : this->outs) {
    out->initVal();
  }
}

void Component::onChangeIn(deque<Component *> &chcoms) {
  if (++this->loopcnt >= 256) {
    throw runtime_error("無限ループが発生しました。問題を解決するために Buffer "
                        "を入れてください。");
  }
}

void Component::onChangeTime(double dt, deque<Component *> &chcoms) {
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
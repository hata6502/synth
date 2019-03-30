#include "sketch.hpp"

#include <algorithm>
#include <deque>

Sketch::Sketch() : onSim(false) {}

void Sketch::appendCom(Component *com) {
  this->coms.push_back(Component_up(com));
}

void Sketch::removeCom(Component *rm) {
  this->coms.erase(
      remove_if(this->coms.begin(), this->coms.end(),
                [&](Component_up &com) -> bool { return com.get() == rm; }),
      this->coms.end());
}

void Sketch::upInterface() {
  this->int_ins.clear();
  this->int_outs.clear();
  for (Component_up &com : this->coms) {
    vector<InPort_p> int_ins = com->getIntIns();
    this->int_ins.insert(this->int_ins.end(), int_ins.begin(), int_ins.end());

    vector<OutPort_p> int_outs = com->getIntOuts();
    this->int_outs.insert(this->int_outs.end(), int_outs.begin(),
                          int_outs.end());
  }
}

void Sketch::onSimStart() {
  for (Component_up &com : this->coms) {
    com->onSimStart();
  }

  this->onSim = true;
}

void Sketch::onChangeTime(double dt) {
  deque<Component *> chcoms;

  for (Component_up &com : this->coms) {
    com->onChangeTime(dt, chcoms);
  }

  while (!chcoms.empty()) {
    chcoms.front()->onChangeIn(chcoms);
    chcoms.pop_front();
  }
}

void Sketch::onSimEnd() { this->onSim = false; }

void Sketch::exportExtends() {
  for (Component_up &com : this->coms) {
    com->exportExtends();
  }
}

/*
        export(){
                var ex = {};
                ex.coms = [];
                this.coms.forEach((com) => {
                        ex.coms.push(com.export());
                });
                return ex;
        }

        import(im){
                this.clearCom();
                var lut = [];
                im.coms.forEach((im) => {
                        var com = eval("new "+im.type+"()");
                        lut = lut.concat(com.import(im));
                        this.appendCom(com);
                });

                var comlut = [];
                this.coms.forEach((com) => {
                        com.connectById(lut);
                        comlut.push({ id: com.id, inst: com });
                });
                return comlut;
        }
};
*/
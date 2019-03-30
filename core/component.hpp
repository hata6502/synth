#pragma once
class Component;

#include "in_port.hpp"
#include "out_port.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <deque>
#include <memory>
#include <string>
#include <uuid/uuid.h>
#include <vector>

using namespace std;

typedef shared_ptr<InPort> InPort_p;
typedef shared_ptr<OutPort> OutPort_p;

struct CallCommand {
  string name;
  void (*handler)(Component *com, vector<string> &args);
};

#define registerCallCommand(name)                                              \
  { #name, name##Handler }

class Component {
  int loopcnt;

protected:
  map<string, string> extends;

  void update(deque<Component *> &chcoms);
  void appendIn(InPort_p in_);
  void removeIn(InPort_p &rm);
  void clearIn();
  void appendOut(OutPort_p out);
  void removeOut(OutPort_p &rm);
  void clearOut();

public:
  uuid_t id;
  string com_name;
  vector<InPort_p> ins;
  vector<OutPort_p> outs;

  Component();
  vector<InPort_p> getIntIns();
  vector<OutPort_p> getIntOuts();
  virtual vector<string> getIn();
  virtual vector<string> getOut();
  virtual vector<CallCommand> &getCallCommands();
  void initPort(int in_n, int out_n);
  virtual void onSimStart();
  virtual void onChangeIn(deque<Component *> &chcoms);
  virtual void onChangeTime(double dt, deque<Component *> &chcoms);
  virtual void exportExtends();

  template <class Archive> void serialize(Archive &archive) {
    char uuid_str[37];
    vector<InPort> ins;
    vector<OutPort> outs;

    uuid_unparse_lower(this->id, uuid_str);
    for (InPort_p in_ : this->ins) {
      ins.push_back(*in_);
    }
    for (OutPort_p out : this->outs) {
      outs.push_back(*out);
    }

    archive(cereal::make_nvp("type", com_name),
            cereal::make_nvp("id", string(uuid_str)), CEREAL_NVP(ins),
            CEREAL_NVP(outs), CEREAL_NVP(extends));

    this->extends = map<string, string>();
  }
};

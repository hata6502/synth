#pragma once
class Component;

#include "port_in.hpp"
#include "port_out.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <deque>
#include <memory>
#include <string>
#include <uuid/uuid.h>
#include <vector>

using namespace std;

typedef shared_ptr<PortIn> PortIn_p;
typedef shared_ptr<PortOut> PortOut_p;

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
  void appendIn(PortIn_p in_);
  void removeIn(PortIn_p &rm);
  void clearIn();
  void appendOut(PortOut_p out);
  void removeOut(PortOut_p &rm);
  void clearOut();

public:
  uuid_t id;
  string com_name;
  vector<PortIn_p> ins;
  vector<PortOut_p> outs;

  Component();
  vector<PortIn_p> getIntIns();
  vector<PortOut_p> getIntOuts();
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
    vector<PortIn> ins;
    vector<PortOut> outs;

    uuid_unparse_lower(this->id, uuid_str);
    for (PortIn_p in_ : this->ins) {
      ins.push_back(*in_);
    }
    for (PortOut_p out : this->outs) {
      outs.push_back(*out);
    }

    archive(cereal::make_nvp("type", com_name),
            cereal::make_nvp("id", string(uuid_str)), CEREAL_NVP(ins),
            CEREAL_NVP(outs), CEREAL_NVP(extends));

    this->extends = map<string, string>();
  }
};

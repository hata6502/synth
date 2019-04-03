// Copyright 2019 BlueHood

#pragma once
class Component;

#include <uuid/uuid.h>

#include <deque>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "in_port.hpp"
#include "out_port.hpp"
#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

typedef std::unique_ptr<InPort> InPort_up;
typedef std::unique_ptr<OutPort> OutPort_up;

struct CallCommand {
  std::string name;
  void (*handler)(Component *com, const std::vector<std::string> &args);
};

#define registerCallCommand(name)                                              \
  { #name, name##Handler }

class Component {
  int loopcnt;

protected:
  std::map<std::string, std::string> extends;

  void update(std::deque<Component *> *chcoms);
  void appendIn(InPort *in_);
  void removeIn(InPort *rm);
  void clearIn();
  void appendOut(OutPort *out);
  void removeOut(OutPort *rm);
  void clearOut();

public:
  uuid_t id;
  std::string com_name;
  std::vector<InPort_up> ins;
  std::vector<OutPort_up> outs;

  Component();
  std::vector<InPort *> getIntIns();
  std::vector<OutPort *> getIntOuts();
  virtual std::vector<std::string> getIn();
  virtual std::vector<std::string> getOut();
  virtual std::vector<CallCommand> &getCallCommands();
  void initPort(int in_n, int out_n);
  virtual void onSimStart();
  virtual void onChangeIn(std::deque<Component *> *chcoms);
  virtual void onChangeTime(double dt, std::deque<Component *> *chcoms);
  virtual void exportExtends();

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    char uuid_str[37];
    std::vector<InPort> ins;
    std::vector<OutPort> outs;

    uuid_unparse_lower(this->id, uuid_str);
    for (InPort_up &in_ : this->ins) {
      ins.push_back(*in_);
    }
    for (OutPort_up &out : this->outs) {
      outs.push_back(*out);
    }

    archive(cereal::make_nvp("type", com_name),
            cereal::make_nvp("id", std::string(uuid_str)), CEREAL_NVP(ins),
            CEREAL_NVP(outs), CEREAL_NVP(extends));

    this->extends = std::map<std::string, std::string>();
  }
};

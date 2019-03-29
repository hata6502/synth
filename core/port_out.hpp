#pragma once
class PortOut;

#include "component.hpp"
#include "port_in.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <deque>
#include <memory>
#include <string>
#include <uuid/uuid.h>
#include <vector>

using namespace std;

typedef shared_ptr<PortIn> PortIn_p;

class PortOut {
  double val;
  double latch;

  vector<string> exportTos();

public:
  uuid_t id;
  bool int_;
  vector<PortIn *> tos;
  vector<string> to_ids;

  PortOut();
  double getVal();
  double setLatch(double value);
  void initVal();
  void update(deque<Component *> &chcoms);
  void disconnectAll();

  template <class Archive> void serialize(Archive &archive) {
    vector<string> tos = this->exportTos();
    archive(CEREAL_NVP(tos), cereal::make_nvp("int", int_));
  }
};

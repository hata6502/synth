#pragma once
class PortOut;

#include "component.hpp"
#include "port_in.hpp"

#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <uuid/uuid.h>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

using namespace std;

typedef shared_ptr<PortIn> PortIn_p;

class PortOut
{
  double val;
  double latch;

  vector<string> exportTos();

public:
  string int_;
  vector<PortIn *> tos;
  vector<string> to_ids;

  PortOut();
  double getVal();
  double setLatch(double value);
  void initVal();
  void update(deque<Component *> &chcoms);
  void disconnectAll();

  template <class Archive>
  void serialize(Archive &archive)
  {
    vector<string> tos = this->exportTos();
    archive(CEREAL_NVP(tos), cereal::make_nvp("int", int_));
  }
};

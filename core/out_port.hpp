// Copyright 2019 BlueHood

#pragma once
class OutPort;

#include <uuid/uuid.h>

#include <deque>
#include <memory>
#include <string>
#include <vector>

#include "component.hpp"
#include "in_port.hpp"
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

class OutPort {
  double val;
  double latch;

  std::vector<std::string> exportTos();

public:
  uuid_t id;
  bool int_;
  std::vector<InPort *> tos;
  std::vector<std::string> to_ids;

  OutPort();
  double getVal();
  double setLatch(double value);
  // void initVal();
  void update(std::deque<Component *> *chcoms);
  void disconnectAll();

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    std::vector<std::string> tos = this->exportTos();
    archive(CEREAL_NVP(tos), cereal::make_nvp("int", int_));
  }
};

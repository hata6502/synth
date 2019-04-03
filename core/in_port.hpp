// Copyright 2019 BlueHood

#pragma once
class InPort;

#include <uuid/uuid.h>

#include <memory>
#include <string>

#include "component.hpp"
#include "out_port.hpp"
#include <cereal/cereal.hpp>

class InPort {
public:
  uuid_t id;
  double val;
  Component *com;
  OutPort *src;
  bool int_;

  InPort();
  // void initVal();
  void connect(OutPort *src);
  void disconnect();

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    char uuid_str[37];

    uuid_unparse_lower(this->id, uuid_str);
    archive(cereal::make_nvp("id", std::string(uuid_str)),
            cereal::make_nvp("int", int_));
  }
};

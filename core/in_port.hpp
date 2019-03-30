#pragma once
class InPort;

#include "component.hpp"
#include "out_port.hpp"

#include <cereal/cereal.hpp>
#include <memory>
#include <string>
#include <uuid/uuid.h>

using namespace std;

typedef shared_ptr<OutPort> OutPort_p;

class InPort {
public:
  uuid_t id;
  double val;
  Component *com;
  OutPort_p src;
  bool int_;

  InPort();
  void initVal();
  void connect(OutPort_p &src);
  void disconnect();

  template <class Archive> void serialize(Archive &archive) {
    char uuid_str[37];

    uuid_unparse_lower(this->id, uuid_str);
    archive(cereal::make_nvp("id", string(uuid_str)),
            cereal::make_nvp("int", int_));
  }
};

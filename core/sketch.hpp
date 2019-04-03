// Copyright 2019 BlueHood

#pragma once
class Sketch;

#include <memory>
#include <vector>

#include "component.hpp"
#include "in_port.hpp"
#include "out_port.hpp"
#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

typedef std::unique_ptr<Component> Component_up;
typedef std::unique_ptr<InPort> InPort_up;
typedef std::unique_ptr<OutPort> OutPort_up;

class Sketch {
public:
  std::vector<Component_up> coms;
  std::vector<InPort *> int_ins;
  std::vector<OutPort *> int_outs;
  bool onSim;

  Sketch();
  void appendCom(Component *com);
  void removeCom(Component *rm);
  void clearCom();
  void upInterface();
  void onSimStart();
  void onChangeTime(double dt);
  void onSimEnd();
  void exportExtends();

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    std::vector<Component> coms;

    for (Component_up &com : this->coms) {
      coms.push_back(*com);
    }
    archive(CEREAL_NVP(coms));
  }
};

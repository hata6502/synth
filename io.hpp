// Copyright 2019 BlueHood

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

struct Request;

bool eof();
Request receive();

template <typename T> void respond(const T &response) {
  std::stringstream stream;
  {
    cereal::JSONOutputArchive archive(stream);
    archive(CEREAL_NVP(response));
  }

  std::cout << stream.str() << '\0';
}

struct Request {
  std::vector<std::string> args;

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    archive(CEREAL_NVP(args));
  }
};

struct ErrorResponse {
  std::string error;

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    archive(CEREAL_NVP(error));
  }
};

struct EmptyResponse {
  template <class Archive> void serialize(Archive &archive) {} // NOLINT
};

struct AddcomResponse {
  std::string uuid;

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    archive(CEREAL_NVP(uuid));
  }
};

struct LscomResponse {
  struct Component {
    std::string uuid;
    std::string type;

    template <class Archive> void serialize(Archive &archive) { // NOLINT
      archive(CEREAL_NVP(uuid), CEREAL_NVP(type));
    }
  };

  std::vector<Component> components;

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    archive(CEREAL_NVP(components));
  }
};

struct LsportResponse {
  struct InPort {
    std::string uuid;
    std::string type;
    std::string source;
    double value;

    template <class Archive> void serialize(Archive &archive) { // NOLINT
      archive(CEREAL_NVP(uuid), CEREAL_NVP(type), CEREAL_NVP(value),
              CEREAL_NVP(source));
    }
  };

  struct OutPort {
    std::string uuid;
    std::string type;
    std::vector<std::string> tos;
    double value;

    template <class Archive> void serialize(Archive &archive) { // NOLINT
      archive(CEREAL_NVP(uuid), CEREAL_NVP(type), CEREAL_NVP(value),
              CEREAL_NVP(tos));
    }
  };

  std::vector<InPort> inputs;
  std::vector<OutPort> outputs;

  template <class Archive> void serialize(Archive &archive) { // NOLINT
    archive(CEREAL_NVP(inputs), CEREAL_NVP(outputs));
  }
};

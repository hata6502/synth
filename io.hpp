#pragma once

#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Request;

bool eof();
Request receive();
void initPlay(vector<string> &args);
bool isContinuePlay();
void storePlay(double sample);
void respondPlay();

template <typename T> void respond(T &response) {
  stringstream stream;
  {
    cereal::JSONOutputArchive archive(stream);
    archive(CEREAL_NVP(response));
  }

  cout << stream.str() << '\0';
}

struct Request {
  vector<string> args;

  template <class Archive> void serialize(Archive &archive) {
    archive(CEREAL_NVP(args));
  }
};

struct ErrorResponse {
  string error;

  template <class Archive> void serialize(Archive &archive) {
    archive(CEREAL_NVP(error));
  }
};

struct EmptyResponse {
  template <class Archive> void serialize(Archive &archive) {}
};

struct AddcomResponse {
  string uuid;

  template <class Archive> void serialize(Archive &archive) {
    archive(CEREAL_NVP(uuid));
  }
};

struct LscomResponse {
  struct Component {
    string uuid;
    string type;

    template <class Archive> void serialize(Archive &archive) {
      archive(CEREAL_NVP(uuid), CEREAL_NVP(type));
    }
  };

  vector<Component> components;

  template <class Archive> void serialize(Archive &archive) {
    archive(CEREAL_NVP(components));
  }
};

struct LsportResponse {
  struct InPort {
    string uuid;
    string type;

    template <class Archive> void serialize(Archive &archive) {
      archive(CEREAL_NVP(uuid), CEREAL_NVP(type));
    }
  };

  struct OutPort {
    string uuid;
    string type;

    template <class Archive> void serialize(Archive &archive) {
      archive(CEREAL_NVP(uuid), CEREAL_NVP(type));
    }
  };

  vector<InPort> inputs;
  vector<OutPort> outputs;

  template <class Archive> void serialize(Archive &archive) {
    archive(CEREAL_NVP(inputs), CEREAL_NVP(outputs));
  }
};

// Copyright 2019 BlueHood

#include "io.hpp"

#include <iostream>
#include <sstream>
#include <string>

using std::cin, std::string, std::stringstream;

bool eof() { return cin.eof(); }

Request receive() {
  char ch;
  string requestJson;
  while (cin >> ch && ch != '\0') {
    requestJson += ch;
  }

  Request request;
  stringstream stream(requestJson);
  {
    cereal::JSONInputArchive archive(stream);
    archive(CEREAL_NVP(request));
  }

  return request;
}

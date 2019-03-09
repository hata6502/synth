#pragma once

#include <string>
#include <vector>
#include <cereal/cereal.hpp>

using namespace std;

struct Request
{
    vector<string> args;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(args));
    }
};

#pragma once

#include <string>
#include <cereal/cereal.hpp>

using namespace std;

struct ErrorResponse
{
    string error;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(error));
    }
};

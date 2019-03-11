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

struct AddcomResponse
{
    string uuid;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(uuid));
    }
};

struct LscomResponse
{
    struct Component
    {
        string uuid;
        string type;

        template <class Archive>
        void serialize(Archive &archive)
        {
            archive(CEREAL_NVP(uuid), CEREAL_NVP(type));
        }
    };

    vector<Component> coms;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(coms));
    }
};

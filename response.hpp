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

    vector<Component> components;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(components));
    }
};

struct LsportResponse
{
    struct PortIn
    {
        string uuid;
        string type;

        template <class Archive>
        void serialize(Archive &archive)
        {
            archive(CEREAL_NVP(uuid), CEREAL_NVP(type));
        }
    };

    struct PortOut
    {
        string uuid;
        string type;

        template <class Archive>
        void serialize(Archive &archive)
        {
            archive(CEREAL_NVP(uuid), CEREAL_NVP(type));
        }
    };

    vector<PortIn> inputs;
    vector<PortOut> outputs;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(CEREAL_NVP(inputs), CEREAL_NVP(outputs));
    }
};

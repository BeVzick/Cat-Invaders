#pragma once

#include <nlohmann/json.hpp>

class ISerializable
{
public:
    virtual nlohmann::json Serialize() = 0;
    virtual void Deserialize(const nlohmann::json& data) = 0;
};

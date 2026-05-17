#pragma once

#include "ISerializable.h"
#include <string>

class SaveSlot : public ISerializable
{
public:
    SaveSlot(unsigned long id);
    SaveSlot(unsigned long id, std::string_view name, std::string_view filename, std::string_view datetime, std::time_t time_played = 0);

    unsigned long GetID();
    std::string GetName();
    std::string GetFilename();
    std::string GetDatetime();
    std::time_t GetTimePlayed();
    void SetName(std::string_view name);
    void SetFilename(std::string_view filename);
    void SetDatetime(std::string_view datetime);
    void SetTimePlayed(std::time_t time_played);

    nlohmann::json Serialize() override;
    void Deserialize(const nlohmann::json& data) override;

private:
    unsigned long ID;
    std::string name;
    std::string filename;
    std::string datetime;
    std::time_t timePlayed;
};
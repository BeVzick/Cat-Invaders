#pragma once

#include <string>
#include <nlohmann/json.hpp>

class SaveSlot
{
public:
    SaveSlot();
    SaveSlot(std::string_view name, std::string_view filename, std::string_view datetime, std::time_t time_played = 0);

    std::string GetName();
    std::string GetFilename();
    std::string GetDatetime();
    std::time_t GetTimePlayed();
    void SetName(std::string_view name);
    void SetFilename(std::string_view filename);
    void SetDatetime(std::string_view datetime);
    void SetTimePlayed(std::time_t time_played);

    nlohmann::json Serialize();
    void Deserialize(const nlohmann::json& data);

private:
    std::string name;
    std::string filename;
    std::string datetime;
    std::time_t timePlayed;
};
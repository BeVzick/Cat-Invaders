#include "SaveSlot.h"

SaveSlot::SaveSlot(unsigned long id)
    : SaveSlot(id, "", "", "00-00-00 00:00:00")
{
}

SaveSlot::SaveSlot(unsigned long id, std::string_view name, std::string_view filename, std::string_view datetime, std::time_t time_played)
    : name(name), filename(filename), datetime(datetime), timePlayed(time_played)
{
}

unsigned long SaveSlot::GetID()
{
    return ID;
}

std::string SaveSlot::GetName()
{
    return name;
}

std::string SaveSlot::GetFilename()
{
    return filename;
}

std::string SaveSlot::GetDatetime()
{
    return datetime;
}

std::time_t SaveSlot::GetTimePlayed()
{
    return timePlayed;
}

void SaveSlot::SetName(std::string_view name)
{
    this->name = name;
}

void SaveSlot::SetFilename(std::string_view filename)
{
    this->filename = filename;
}

void SaveSlot::SetDatetime(std::string_view datetime)
{
    this->datetime = datetime;
}

void SaveSlot::SetTimePlayed(std::time_t time_played)
{
    this->timePlayed = time_played;
}

nlohmann::json SaveSlot::Serialize()
{
    nlohmann::json slot = nlohmann::json::object();
    
    slot["id"] = ID;
    slot["name"] = name;
    slot["filename"] = filename;
    slot["datetime"] = datetime;
    slot["time_played"] = timePlayed;

    return slot;
}

void SaveSlot::Deserialize(const nlohmann::json& data)
{
    ID = data.value("id", 0);
    name = data.value("name", "");
    filename = data.value("filename", "");
    datetime = data.value("datetime", "00-00-00 00:00:00");
    timePlayed = data.value("time_played", 0);
}

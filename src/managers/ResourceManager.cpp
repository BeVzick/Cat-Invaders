#include "ResourceManager.h"

#include "../utills/ClampWindows.h"
#include <string>
#include <imgui.h>

ResourceManager::ResourceManager(unsigned scrap_metals, unsigned plasma_shards)
    : scrapMetals(scrap_metals), plasmaShards(plasma_shards)
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::UpdateUI()
{
    ImGui::Begin("Resources", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ClampImGuiWindow();

    std::string scrapMetalsStr = std::to_string(scrapMetals);
    std::string plasmaShardsStr = std::to_string(plasmaShards);
    ImGui::Text("Scrap Metals:");
    ImGui::SameLine();
    ImGui::Text(scrapMetalsStr.c_str());

    ImGui::Text("Plasma Shards:");
    ImGui::SameLine();
    ImGui::Text(plasmaShardsStr.c_str());

    ImGui::End();
}

unsigned ResourceManager::GetScrapMetals()
{
    return scrapMetals;
}

unsigned ResourceManager::GetPlasmaShards()
{
    return plasmaShards;
}

bool ResourceManager::Enough(ResourceType resource_type, unsigned number)
{
    switch (resource_type)
    {
    case ScrapMetal:
        if (number > scrapMetals)
            return false;
        break;
    case PlasmaShard:
        if (number > plasmaShards)
            return false;
        break;
    }
    return true;
}

bool ResourceManager::Spend(ResourceType resource_type, unsigned number)
{
    if (!Enough(resource_type, number))
        return false;

    switch (resource_type)
    {
    case ScrapMetal:
        scrapMetals -= number;
        break;
    case PlasmaShard:
        plasmaShards -= number;
        break;
    }
    return true;
}

void ResourceManager::Add(ResourceType resource_type, unsigned number)
{
    switch (resource_type)
    {
    case ScrapMetal:
        scrapMetals += number;
        break;
    case PlasmaShard:
        plasmaShards += number;
        break;
    }
}

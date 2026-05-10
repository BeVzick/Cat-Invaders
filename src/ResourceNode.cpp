#include "ResourceNode.h"

#include <imgui.h>

ResourceNode::ResourceNode(sf::Texture &texture, ResourceType resource_type, unsigned amount, sf::Vector2f pos)
    : GameObject(texture), resourceType(resource_type), amount(amount)
{
    SetPos(pos);
    maxHealth = 1;
    health = maxHealth;
}

ResourceNode::~ResourceNode()
{
}

void ResourceNode::ShowData()
{
    std::string typeName = (resourceType == ScrapMetal) ? "Scrap Metal" : "Plasma Shard";
    ImGui::LabelText("Type", "%s", typeName);
    ImGui::LabelText("Amount", "%u", amount);
}

ResourceType ResourceNode::GetResourceType() const
{
    return resourceType;
}

unsigned ResourceNode::GetAmount() const
{
    return amount;
}

bool ResourceNode::IsEmpty() const
{
    return amount == 0;
}

unsigned ResourceNode::Harvest(unsigned requested)
{
    unsigned harvested = std::min(requested, amount);
    amount -= harvested;
    return harvested;
}

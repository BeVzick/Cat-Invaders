#pragma once

#include "GameObject.h"
#include "managers/ResourceManager.h"

class ResourceNode : public GameObject
{
public:
    ResourceNode(sf::Texture& texture, ResourceType resource_type, unsigned amount, sf::Vector2f pos);
    ~ResourceNode();

    void UpdateAnimations(float dt) override {}
    void ShowData() override;
    ResourceType GetResourceType() const;
    unsigned GetAmount() const;
    bool IsEmpty() const;

    unsigned Harvest(unsigned requested);

private:
    ResourceType resourceType;
    unsigned amount;
};

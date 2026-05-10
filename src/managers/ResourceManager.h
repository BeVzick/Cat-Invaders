#pragma once

enum ResourceType
{
    ScrapMetal,
    PlasmaShard
};

class ResourceManager
{
public:
    ResourceManager(unsigned scrap_metals = 0, unsigned plasma_shards = 0);
    ~ResourceManager();

    void UpdateUI();

    unsigned GetScrapMetals();
    unsigned GetPlasmaShards();

    bool Enough(ResourceType resource_type, unsigned number);
    bool Spend(ResourceType resource_type, unsigned number);
    void Add(ResourceType resource_type, unsigned number);

private:
    unsigned scrapMetals;
    unsigned plasmaShards;
};

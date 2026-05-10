#pragma once

#include <string>
#include <vector>
#include <functional>

class GameObject;

struct ResearchEffect
{
    std::string name;
    std::string description;
    std::function<void(std::vector<GameObject*>&)> Apply;
    bool applied;
};

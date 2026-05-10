#pragma once

#include "../researches/Research.h"
#include <queue>
#include <vector>

class ResearchManager
{
public:
    ResearchManager();
    ~ResearchManager();

    void UpdateUI();

    bool IsPaused();
    void StartResearch();
    void StopResearch();
    void AddResearch(Research* research);
    void RemoveResearch();

private:
    std::queue<Research*> researches;
    std::vector<Research*> availableResearches;
    bool paused;
};

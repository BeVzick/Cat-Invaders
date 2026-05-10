#pragma once

#include "../researches/Research.h"
#include <queue>
#include <vector>

class ResearchManager
{
public:
    ResearchManager();
    ~ResearchManager();

    void Update(float dt, std::vector<GameObject*>& objects);
    void UpdateUI();

    bool IsPaused() const;
    void Pause();
    void Unpause();

    void Enqueue(Research* research);
    void CancelCurrent();
    void ClearQueue();

    void AddAvailable(Research* research);

    const Research* GetCurrent() const;
    bool HasPending() const;

    const std::vector<std::string>& GetCompleted() const;

private:
    std::queue<Research*> queue;
    std::vector<Research*> available;
    std::vector<std::string> completed;
    bool paused;
};

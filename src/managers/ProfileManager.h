#pragma once

#include "../GameObject.h"

class ProfileManager
{
public:
    ProfileManager(GameObject* object = nullptr);
    ~ProfileManager();

    void Show();

    void SetObject(GameObject* object = nullptr);

private:
    GameObject* object;
    bool isOpen;
};

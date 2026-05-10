#pragma once

#include <string>

class Entity;

class ISkill
{
public:
    virtual void Activate(Entity& owner) = 0;
    virtual void Update(float dt);
    virtual bool IsReady() const;
    virtual float GetCooldownProgress() const;
    virtual std::string GetName() const = 0;
    virtual std::string GetDescription() const;
    virtual float GetMaxCooldown() const = 0;

protected:
    float cooldownTimer = 0.f;
    bool onCooldown = false;
};

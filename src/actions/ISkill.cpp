#include "ISkill.h"

void ISkill::Update(float dt)
{
    if (onCooldown)
    {
        cooldownTimer -= dt;
        if (cooldownTimer <= 0.f)
        {
            cooldownTimer = 0.f;
            onCooldown = false;
        }
    }
}

bool ISkill::IsReady() const
{
    return !onCooldown;
}

float ISkill::GetCooldownProgress() const
{
    if (!onCooldown || GetMaxCooldown() <= 0.f)
        return 1.f;
    return 1.f - (cooldownTimer / GetMaxCooldown());
}

std::string ISkill::GetDescription() const
{
    return "";
}

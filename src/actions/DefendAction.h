#pragma once

#include "MoveToAction.h"
#include "../GameObject.h"
#include <SFML/System/Vector2.hpp>

class DefendAction : public IAction
{
public:
    DefendAction(sf::Vector2f pos_iso, float defend_radius = 80.f, float attack_range = 28.f);
    ~DefendAction();

    void Start(Entity& owner) override;
    void Update(Entity& owner, float dt) override;
    bool IsDone() const override;
    void Cancel() override;

    void SetWorldObjects(const std::vector<GameObject*>* objects);

private:
    sf::Vector2f defendPos;
    float defendRadius;
    float attackRange;
    float attackTimer;
    bool done;
    bool arrivedOnce;

    MoveToAction* moveAction;
    GameObject* currentThreat;
    const std::vector<GameObject*>* worldObjects;

    enum class Phase { MovingToPos, Holding, Attacking, Returning } phase = Phase::MovingToPos;

    GameObject* FindThreat(const Entity& owner) const;
    float DistanceTo(const Entity& owner, sf::Vector2f pos) const;
};

#pragma once

class Entity;

class IAction
{
public:
    virtual void Start(Entity& owner) {}
    virtual void Update(Entity& owner, float dt) = 0;
    virtual bool IsDone() const  = 0;
    virtual void Cancel() {}
};

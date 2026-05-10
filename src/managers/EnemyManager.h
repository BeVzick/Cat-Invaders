#pragma once

#include "../entities/enemies/Enemy.h"

class Enemy;

class EnemyManager
{
public:
    EnemyManager();
    ~EnemyManager();

    void CreateEnemy(EnemyType enemy_type, sf::Texture& texture);
    void RemoveEnemy(Enemy* enemy);
    void RemoveEnemy(unsigned index);

private:
    std::vector<Enemy*> enemies;
};

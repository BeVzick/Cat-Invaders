#include "EnemyManager.h"

#include "../entities/enemies/RegularRat.h"
#include "../entities/enemies/Bat.h"

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
    for (auto& e : enemies)
        delete e;
}

void EnemyManager::CreateEnemy(EnemyType enemy_type, sf::Texture& texture)
{
    switch (enemy_type)
    {
    case EnemyType::RegularRat:
        // enemies.push_back(new RegularRat(texture));
        break;
    case EnemyType::Bat:
        // enemies.push_back(new Bat(texture));
        break;
    }
}

void EnemyManager::RemoveEnemy(Enemy *enemy)
{
    for (int i = 0; i < enemies.size(); ++i)
    {
        if (enemies[i] == enemy)
        {
            delete enemy;
            enemies[i] = nullptr;
            break;
        }
    }
}

void EnemyManager::RemoveEnemy(unsigned index)
{
    delete enemies[index];
    enemies[index] = nullptr;
}

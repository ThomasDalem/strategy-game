#ifndef ENEMY_HPP
#define ENEMY_HPP

enum EnemyType
{
    INFANTRY,
    TANK
};

struct Enemy
{
    EnemyType type;
    int health;
};

#endif // ENEMY_HPP
#ifndef CREATURE_H
#define CREATURE_H

#include <string>

class Creature
{
public:
    std::string name;
    int health;
    int damage;

    Creature(std::string n, int h, int d)
    {
        name = n;
        health = h;
        damage = d;
    }

    void attack(Creature &other)
    {

        other.health -= damage;
        if (other.health < 0)
        {
            other.health = 0;
        }
    }

    bool isAlive()
    {
        return health > 0;
    }
};

#endif
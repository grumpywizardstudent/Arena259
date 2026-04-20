#include <iostream>
#include "arena.h"

void Arena::battle(Creature &a, Creature &b)
{
    std::cout << a.name << " vs " << b.name << std::endl;

    int turn = 1;

    while (a.isAlive() && b.isAlive())
    {
        std::cout << "\nTurn " << turn << std::endl;

        std::cout << a.name << " attacks!" << std::endl;
        a.attack(b);
        std::cout << b.name << " health: " << b.health << std::endl;

        if (!b.isAlive())
            break;

        std::cout << b.name << " attacks!" << std::endl;
        b.attack(a);
        std::cout << a.name << " health: " << a.health << std::endl;

        turn++;
    }

    if (a.isAlive())
    {
        std::cout << a.name << " wins!" << std::endl;
    }
    else
    {
        std::cout << b.name << " wins!" << std::endl;
    }
}
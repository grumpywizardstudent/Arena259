#ifndef ARENA_H
#define ARENA_H

#include "creature.h"

class Arena
{
public:
    static void battle(Creature &a, Creature &b);
    static bool takeTurn(Creature &acting, Creature &target);
};

#endif
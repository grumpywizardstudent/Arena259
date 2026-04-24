#ifndef ARENA_H
#define ARENA_H

#include "creature.h"
#include <vector>

class Arena
{
public:
    static void battle(Creature &temp1, Creature &temp2);
    static void printWinner(Creature &winner, Creature &loser);
};

#endif
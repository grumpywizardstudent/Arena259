#ifndef ARENA_H
#define ARENA_H

#include "creature.h"
#include <vector>

class Arena
{
public:
    Arena(std::vector<Creature*> creatures) : creatures(creatures) {};
    void printBegin();
    void printTurn(int turn);
    void printWinner(Creature& winner);
    bool takeTurn(Creature& acting, Creature& target); // return target->isAlive()

private:
    bool hasWinner = false;
    std::vector<Creature*> still_alive;
    std::vector<Creature*> creatures;
};

#endif
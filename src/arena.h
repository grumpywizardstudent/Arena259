#ifndef ARENA_H
#define ARENA_H

#include "creature.h"
#include <vector>

class Arena
{
public:
    Arena(std::vector<Creature*> creatures) : creatures(creatures) {};
    void battle();
    void printBegin();
    void printTurn(int turn);
    void printWinner(Creature& winner);
    void takeTurn(Creature& acting, Creature& target);

private:
    bool hasWinner = false;
    bool checkPulse(Creature* c);
    std::vector<Creature*> creatures;
};

#endif
#ifndef BLACKHOLE_H
#define BLACKHOLE_H

#include "../creature.h"

class BlackHole : public Creature
{
public:
    BlackHole();

    void attack(Creature& target) override;
    void specialMove(Creature& other) override;

private:
    int hitsTaken = 0;
    int lastObservedHealth = 0;
    bool specialUsed = false;
    bool specialActivated = false;
    
};

#endif

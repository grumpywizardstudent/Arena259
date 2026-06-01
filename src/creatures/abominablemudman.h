#ifndef ABOMINABLEMUDMAN_H
#define ABOMINABLEMUDMAN_H
#include "../creature.h"
#include "../rng.h"

class AbominableMudman : public Creature{
    private:
        int atk_count = 0;

        bool dealPercentDmg(); //used to calculate whether an attack deals an additional % of opponents remaining health (scales with consecutive attacks)

    public:
        AbominableMudman();

        ~AbominableMudman() = default;

        void attack(Creature& other) override; // overloaded base function, deals 8 damage and calls dealPercentDmg to determine if extra damage is dealt

        void specialMove(Creature& other) override; //heals the mudman creature for 3x the number of consecutive attacks done ex: 3 x 5 attacks = 15 hp regained (max of 24)
};

#endif
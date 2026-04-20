#include "arena.h"
#include "creature.h"
#include "./creatures/viper.h"
#include "./creatures/giantleech.h"

#include <random>


int main()
{
    Creature c1(makeViper());
    Creature c2(makeGiantleech());

    //
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> var1(-c1.damage / 4, c1.damage / 4);
    std::uniform_int_distribution<int> var2(-c2.damage / 4, c2.damage / 4);

    c1.damage += var1(rng);
    c2.damage += var2(rng);

    if (c1.damage < 1) c1.damage = 1;
    if (c2.damage < 1) c2.damage = 1;

    Arena::battle(c1, c2);

    return 0;
}
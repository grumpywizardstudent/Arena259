#include "arena.h"
#include "creatures/_all_creatures.h"

int main()
{
    // Creature c1(makeViper());
    // Creature c2(makeGiantleech());
    Creature c1 = randomCreature();
    Creature c2 = randomCreature();

    Arena::battle(c1, c2);

    return 0;
}
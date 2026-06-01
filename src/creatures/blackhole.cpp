#include <iostream>
#include <string>

#include "blackhole.h"

BlackHole::BlackHole(): Creature("Black Hole", 120, 1)
{
    lastObservedHealth = getStartHealth();
}

void BlackHole::attack(Creature& other) {
    // Track damage taken
    int current = getHealth();
    if (current < lastObservedHealth) {
        hitsTaken++;
    }
    lastObservedHealth = current;

    // Only trigger vortex if it has been armed
    if (specialActivated && !specialUsed && hitsTaken >= 5) {
        specialMove(other);
        return;
    }

    other.takeDamage(getDamage());
    incDamageDealt(getDamage());
    if (specialActivated && !specialUsed)
        std::cout << other.getName() << " has " << (5 - hitsTaken) << " hits left before it is consumed." << std::endl;
}

void BlackHole::specialMove(Creature& other) {
    if (!specialActivated) {
        std::cout << "Black Hole begins to swirl ominously... Vortex is armed!" << std::endl;
        specialActivated = true;
        return;
    }
    if (!specialUsed && hitsTaken >= 5) {
        int remaining = other.getHealth();
        other.setHealth(0);
        incDamageDealt(remaining);
        std::cout << other.getName() << " is consumed by the vortex!" << std::endl;
        specialUsed = true;
        return;
    }
    std::cout << "Vortex has already been used." << std::endl;
}
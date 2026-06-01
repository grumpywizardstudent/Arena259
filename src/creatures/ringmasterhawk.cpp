#include "ringmasterhawk.h"
#include "../rng.h"

RingmasterHawk::RingmasterHawk() : Creature("Ringmaster Hawk", 95, 15, 10){}

void RingmasterHawk::specialMove(Creature& other) {
    int randomDamage = RNG::randomValue(7, 45); // Random damage between 7 and 45

    std::cout << getName() << " calls for a daring act against " << other.getName() << "!" << std::endl;

    if (randomDamage <= 10) {
        std::cout << "Zzzz.... the Ringmaster hawk's head hangs low for such an abysmal act, dealing: " << randomDamage << " damage." << std::endl;
    } else if (randomDamage <= 20) {
        std::cout << "Well... a Ringmaster can't make every actit doesn't leave much of an impression though " << other.getName() << ", as it dealt: " << randomDamage << " damage." << std::endl;
    } else if (randomDamage <= 30) {
        std::cout << "A great display of the Ringmaster hawk's skills! landing against " << other.getName() << " hard, dealing: " << randomDamage << " damage." << std::endl;
    } else {
        std::cout << "The act is a masterstoke of skill in a act that leaves " << other.getName() << " jaw metaphorically and literally on the floor dealing an astounding: " << randomDamage << " damage!" << std::endl;
    }

    other.takeDamage(randomDamage);
    incDamageDealt(randomDamage);
}

RingmasterHawk makeRingmasterHawk() {
    return RingmasterHawk();
}
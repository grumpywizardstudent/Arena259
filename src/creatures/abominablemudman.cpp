#include "abominablemudman.h"

AbominableMudman::AbominableMudman()
    : Creature("Abominable Mudman", 120, 9){}

void AbominableMudman::attack(Creature& target, int modifier) {
    atk_count++;
    int dmg = this->getDamage() + modifier;
    target.takeDamage(dmg); //normal attack phase
	incDamageDealt(dmg);

    if (dealPercentDmg()){
        int health_portion = (target.getHealth()/10)+1; //calculate portion of health to remove +1 to avoid trunkation after division
        std::cout << "A large portion of " << target.getName() << "'s blood has turned to MUD, dealing " << health_portion << " damage!\n";
        target.takeDamage(health_portion); //removes percentage of oponents remaining health
	incDamageDealt(health_portion);
    }
}

void AbominableMudman::specialMove(Creature& other){ //does nothing with other creature
    int heal_amount;

    if (atk_count >= 8)
        heal_amount = 8 * 3;
    else
        heal_amount = atk_count * 3;

    this->setHealth(this->getHealth() + heal_amount);
    std::cout << "The Mudman has healed "<< heal_amount <<" hp, based on the mud in the opponents blood\n"
              <<  "The opponents blood is no longer tainted with mud\n";
    std::cout << this->getName() << " health after special move: "
                << this->getHealth() << std::endl;
    atk_count = 0; //resets atk_count
}

bool AbominableMudman::dealPercentDmg(){
    static const int percent_per_atk = 5;
    if (atk_count >= 8){return RNG::randomValue(0, 99) < 8 * percent_per_atk;} //returns 1 if random value between 0-100 is less than (8 * 5) max chance
    else return RNG::randomValue(0, 99) < atk_count * percent_per_atk; // //returns 1 if random value between 0-100 is less than (atk_count * 5)
}
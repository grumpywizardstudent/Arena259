#include "creature.h"
#include "rng.h"
#include <algorithm>

// new default constructor creates a creature called 
// "Grunt" which has very middle-ground stats for testing
Creature::Creature()
    : name_("Grunt")
    , hp_base_(10)
    , max_hp_((BASE_STAT + hp_base_) * 4)
    , current_hp(max_hp_)
    , attack_base_(10)
    , attack_(attack_base_ + BASE_STAT)
    , defense_base_(6)
    , defense_(defense_base_ + BASE_STAT)
    , spirit_base_(4)
    , spirit_(spirit_base_+1)
    {creatureCount++;}

// public parameterized constructor for creating creatures with custom stats
// HP, Attack, and Defense all start with a base of 5 in each attribute to 
// prevent 0 values. Spirit has base 1. Assigned values are added during 
// instantiation.
Creature::Creature(const std::string name, const int hp, const int attack, const int defense, const int spirit)
    : name_(name)
    , hp_base_(hp)
    , max_hp_((BASE_STAT + hp_base_) * 4)
    , current_hp(max_hp_)
    , attack_base_(attack)
    , attack_((attack_base_ + BASE_STAT))
    , defense_base_(defense)
    , defense_((defense_base_ + BASE_STAT))
    , spirit_base_(spirit)
    , spirit_(spirit_base_+1)
    {creatureCount++;}

// Class deconstructor
Creature::~Creature() {}

// Updated attack method adds or subtracts damage from base attack
// based on a symmetrical window centered on zero based on a chaos roll
// derived from spirit stat. 
//
// Now also takes a target and handles printing attack info to cout
// by calling takeDamage() on the included target.
void Creature::mainAttack(Creature &target) {
    int spirit_chance = rollSpirit();
    const int raw = attack_ + RNG::randomValue((-spirit_chance), (spirit_chance));
    const int damage = std::max(1, raw);
    std::cout << name_ << " attacks " << target.getName() << " for " << damage << "!" << std::endl;
    std::cout << target.getName() << " only takes " << target.takeDamage(damage) << " damage!" << std:: endl;
    std::cout << target.getName() << " health is: " << target.getCurrentHP() << " HP" << std::endl;
}

// takeDamage performs a bit-shift on the defense stat
// and calculates damage mitigation using a diminishing-returns
// formula that uses spirit as a random noise factor
int Creature::takeDamage(int raw_damage) {
    int chaos = rollSpirit();  
    int rate = (defense_ * 256) / (defense_ + chaos * SPIRIT_SCALE);    // diminishing returns with noise
    int net = std::max(1, raw_damage - (raw_damage * rate / 256));      // floored at 1 (min 1 damage)
    current_hp = std::max(0, current_hp - net);                         // floored at zero to prevent negative health
    return net; 
}


// validate creatures by attribute assignment. Total points assigned 
// must equal point pool to prevent over-and-under-powered creatures
// print out creature stat total if they fail.
bool Creature::validate() {
    if (hp_base_ + attack_base_  + defense_base_  + spirit_base_ != POINT_POOL) {
        std::cout << name_ << " doesn't qualify for battle." << std::endl;
        std::cout << "Stat Total: " << hp_base_ + attack_base_  + defense_base_  + spirit_base_ << std::endl;
        return false;
    }
    return true;
}

// the chaos generator
int Creature::rollSpirit() {
    return RNG::randomValue(1, spirit_);
}


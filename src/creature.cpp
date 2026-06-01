// c++ libraries
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

// header files
#include "creature.h"
#include "rng.h"
#include "utils.h"

// constant values
int Creature::creatureCount = 0;
const int Creature::MIN_HEALTH;
const int Creature::MAX_HEALTH;
const int Creature::MIN_DAMAGE;
const int Creature::MAX_DAMAGE; 


// Constructor
Creature::Creature(std::string name, int health, int damage) 
	: name(name)
	, health(health)
	, startHealth(health)
	, damage(damage)
	, startDamage(damage)
	, defense(0)
	{ creatureCount++;
	std::cout << "[constructor] Creature base constructed: " << name << std::endl;  }

Creature::Creature(std::string name, int health, int damage, int defense) 
	: name(name)
	, health(health)
	, startHealth(health)
	, damage(damage)
	, startDamage(damage)
	, defense(defense)
	{ creatureCount++; 
	std::cout << "[constructor] Creature base constructed: " << name << std::endl; }

// Destructor
Creature::~Creature() { std::cout << "[destructor] Creature destroyed: " << name << std::endl; }


// Getters
std::string Creature::getName() const {
	return name; // return name
}

int Creature::getHealth() const {
	return health; // return health
}

int Creature::getStartHealth() const {
	return startHealth;
}

int Creature::getDamage() const {
	return damage; // return damage
}

int Creature::getStartDamage() const {
	return startDamage;
}

int Creature::getDamageDealt() const {
	return damageDealt;
}

int Creature::getDefense() const {
	return defense;
}

bool Creature::isAlive() const {
	return health > 0; // return true if health > 0
}

int Creature::getCreatureCount() {
	return creatureCount;
}


// Setters
void Creature::setName(std::string newName) {
	name = newName; // update name, no checks needed
}

void Creature::setHealth(int newHealth) {
	health = newHealth; // update health
	if (getHealth() < 0) { // ensure that health stays non-negative
		health = 0;
	}
	else if (getHealth() > getStartHealth()) {
		setHealth(startHealth);
	}
}

void Creature::setDefense(int newDefense) {
	defense = newDefense;
}

void Creature::setDamage(int newDamage) {
	damage = newDamage; // update damage
	if (getDamage() < 0) { // don't allow damage to be negative
		damage = 0;
	}
}

// Incrementers
void Creature::heal(int increase) {
	setHealth(getHealth() + increase); // set the health + increase
}

void Creature::incDamage(int increase) {
	setDamage(getDamage() + increase); // just set the damage + increase
}

void Creature::incDamageDealt(int increase) {
	damageDealt += increase;
}

void Creature::takeDamage(int amount) {
	int reduced = amount - defense;
	if (reduced < 0) reduced = 0;

	health = std::max(0, health - reduced);
}

// Methods interacting with other creatures
void Creature::attack(Creature& target, int modifier) {
	int modified_damage = damage + modifier;
	target.takeDamage(modified_damage);
	incDamageDealt(modified_damage);
	std::cout << colorMe(name, Color::CYAN) << " attacks "
                  << colorMe(target.getName(), Color::RED) << " for "
                  << colorMe(std::to_string(modified_damage), Color::YELLOW) << " damage! "
                  << colorMe("(" + std::to_string(target.getHealth()) + " HP remaining)", Color::WHITE) << "\n";
}

void Creature::specialMove(Creature& target){
	std::cout << name << " has no special move." << std::endl;
}

Creature& Creature::chooseTarget(const Creatures& creatures, MODE m) {
    std::vector<Creature*> targets;
    for (const auto& c : creatures) {
        if (c.get() != this && c->isAlive()) targets.push_back(c.get());
    }
    if (targets.empty()) return *this;

    auto cmp = [](auto fn) {
        return [fn](Creature* a, Creature* b){ return fn(a) < fn(b); };
    };

    std::vector<Creature*>::iterator it;
    switch (m) {
        case MODE::LOW_CUR_HP:   it = std::min_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getHealth();      })); break;
        case MODE::HIGH_CUR_HP:  it = std::max_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getHealth();      })); break;
        case MODE::LOW_MAX_HP:   it = std::min_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getStartHealth(); })); break;
        case MODE::HIGH_MAX_HP:  it = std::max_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getStartHealth(); })); break;
        case MODE::LOW_ATTACK:   it = std::min_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getDamage();      })); break;
        case MODE::HIGH_ATTACK:  it = std::max_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getDamage();      })); break;
        case MODE::LOW_DEFENSE:  it = std::min_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getDefense();     })); break;
        case MODE::HIGH_DEFENSE: it = std::max_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getDefense();     })); break;
        default: return *targets[RNG::randomValue(0, targets.size() - 1)];
    }
    return **it;
}

// Validation
bool Creature::isValid(Creature& c) {
	// test health
	if (c.getHealth() < MIN_HEALTH || c.getHealth() > MAX_HEALTH) { 
		
	// health error
		std::cerr << "Error: " << c.getName() << " has invalid health (" << c.getHealth() 
		<< " HP). Health must be between " << MIN_HEALTH << " and " << MAX_HEALTH << std::endl;
		return false;
	}

	//test damage
	if (c.getDamage() < MIN_DAMAGE || c.getDamage() > MAX_DAMAGE) {
		
	// damage error
		std::cerr << "Error: " << c.getName() << " has invalid damage (" << c.getDamage() 
		<<  " DMG). Damage must be between " << MIN_DAMAGE << " and " << MAX_DAMAGE << std::endl;
		return false; 
	}
	// everything is good!
	return true;
}

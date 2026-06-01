#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>

class Creature;
using Creatures = std::vector<std::unique_ptr<Creature>>;

// enum class that allows a creature to
// choose who it attacks in multi-creature battles.
// Used in Creature::chooseTarget()
enum class MODE {
    RANDOM = 0,
    LOW_CUR_HP = 1,
    HIGH_CUR_HP = 2,
    LOW_MAX_HP = 3,
    HIGH_MAX_HP = 4,
    LOW_ATTACK = 5,
    HIGH_ATTACK = 6,
    LOW_DEFENSE = 7,
    HIGH_DEFENSE = 8,
    LOW_SPIRIT = 9,
    HIGH_SPIRIT = 10
};


class Creature
{
private:
	static int creatureCount; 				// will be increased in the constructor
	static const int MIN_HEALTH = 80; 		// ranges for valid health and damage
	static const int MAX_HEALTH = 120;
	static const int MIN_DAMAGE = 0;
	static const int MAX_DAMAGE = 20;

	std::string name;
	int startHealth; 						// maxmimum health stat
	int health;
	int startDamage; 						// maximum damage stat
	int damage;
	int damageDealt = 0;
	int defense;


public:
	// Constructor 
	Creature(std::string name, int health, int damage); 
	Creature(std::string name, int health, int damage, int defense);

	virtual ~Creature();

	// Getters
	std::string getName() const; 					// returns the name variable
	int getHealth() const; 							// returns the health variable
	int getStartHealth() const;
	int getDamage() const; 							// returns the damage variable
	int getStartDamage() const;
	int getDamageDealt() const;
	int getDefense() const;
	bool isAlive() const; 							// checks if the health is >= 0
	static int getCreatureCount(); 					// get the total amount of creature instances
	
	// Setters
	void setName(std::string); 						// set name
	void setHealth(int); 							// set health
	void setDamage(int); 		                    // set damage
	void setDefense(int);							// set defense
	void heal(int); 								// increase health
	void incDamage(int); 							// increase damage
	void incDamageDealt(int); 						// increase damage dealt stat

	// Damage other creatures
	virtual void attack(Creature& target, int modifier=0); 			// decreases health of target 
	virtual void specialMove(Creature& target);
	void takeDamage(int amount); 					// decrease this creature's health by amount - defense
	Creature& chooseTarget(const Creatures& creatures, MODE m = MODE::RANDOM);

	constexpr int specialChance() {
		float numerator = damage - MIN_DAMAGE;
		float denominator = MAX_DAMAGE - MIN_DAMAGE;
		int coeff = 25 - 10;
		return 10 + (int)(numerator / denominator * coeff);
	};

	// Validation checks
	static bool isValid(Creature& creature); 		// returns true if health and damage are in valid
											 		// ranges, false if otherwise (for balancing)
};

#endif

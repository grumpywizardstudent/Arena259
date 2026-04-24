#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <iostream>

// Added point pool-based attribute assignment system 
// to enforce balance and enable rock-paper-scissors-style
// creature design where putting points in one attribute 
// restricts the points available for other attributes.
const int POINT_POOL = 30;
const int BASE_STAT = 5;
const int SPIRIT_SCALE = 15;  // tunable: higher value = less mitigation overall

class Creature {
    public:
        inline static int getCreatureCount() { return creatureCount; };
// modified damage calc to include stat-based mitigation
        int takeDamage(int damage);  

// renamed attack and added target. Now calls takeDamage in the method
        void mainAttack(Creature &target); 

// getters for private var retrieval
        const std::string getName() { return name_; };
        const int getCurrentHP() { return current_hp; }; 
        const int getAttack() { return attack_; }; 
        const int getDefense() { return defense_; };

// state checks and validation
        bool isAlive() { return current_hp > 0; }
        bool validate();

// public constructors/deconstructor with const args and a new default constructor
        Creature();        
        Creature(const std::string name, const int hp, const int attack, const int defense, const int spirit_);
        ~Creature();
    private:
// moved vars to private, set to const if immutable
// and stored the constructor values for validation
// against the point pool
        const std::string name_;
        const int hp_base_;
        const int attack_base_;
        const int attack_;

// new defense stat for damage mitigation 
        const int defense_base_;
        const int defense_;
        const int max_hp_;
// new chaos stat that affects the randomness for attacks and defense
        const int spirit_base_;
        const int spirit_;
// separated HP into max and current for better visibility of 
// the stat floor/ceiling
        int current_hp;

// the chaos function based on the new spirit attribute.
// private because it is only ever called from within the class
        int rollSpirit();

// creature counter
        inline static int creatureCount = 0;

};


#endif
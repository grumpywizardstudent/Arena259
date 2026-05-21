#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <iostream>
#include <vector>

enum class MODE {
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
    virtual Creature& chooseTarget(std::vector<Creature*> creatures, MODE m);

// getters for private var retrieval
    std::string getName() const  { return name_; };
    int getCurrentHP() const  { return current_hp; }; 
    int getAttack() const  { return attack_; }; 
    int getDefense() const  { return defense_; };

// state checks and validation
    bool isAlive() { return current_hp > 0; }
    bool validate();

// public constructors
    Creature();        
    Creature(std::string name, int hp, int attack, int defense, int spirit_);
    virtual ~Creature();
private:
    const std::string name_;
    const int hp_base_;
    const int attack_base_;
    const int attack_;
    const int defense_base_;
    const int defense_;
    const int max_hp_;
    const int spirit_base_;
    const int spirit_;
    int current_hp;

// the chaos function based on the new spirit attribute.
// private because it is only ever called from within the class
    int rollSpirit();

// creature counter
    inline static int creatureCount = 0;

};


#endif
#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "damage.h"

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

const int POINT_POOL = 30;
const int BASE_STAT = 5;
const int SPIRIT_SCALE = 15;  // tunable: higher value = less mitigation overall

class Creature {
public:
    inline static int getCreatureCount() { return creatureCount; };
    int takeDamage(int raw_damage, Creature* source);
    void applyDamage(const Damage& d);
    void processDamage(int current_turn);
    virtual void mainAttack(Creature& target);
    virtual Creature& chooseTarget(std::vector<Creature*> creatures, MODE m);

    std::string getName() const  { return name_; };
    int getCurrentHP() const  { return current_hp; };
    int getMaxHP()     const  { return max_hp_; };
    int getAttack()    const  { return attack_; };
    int getDefense()   const  { return defense_; };
    int getSpirit()    const  { return spirit_; };
    MODE getMode()     const  { return mode_; };

    bool isAlive() { return current_hp > 0; }
    bool validate();

    Creature();
    Creature(std::string name, int hp, int attack, int defense, int spirit, MODE mode = MODE::LOW_CUR_HP);
    virtual ~Creature();
private:
    const std::string name_;
    const int hp_base_;
    const int attack_base_;
    const int attack_;
    const int defense_base_;
    const int defense_;
    const int spirit_base_;
    const int spirit_;
    const int max_hp_;    // depends on spirit_, must be declared after it
    int current_hp;
    MODE mode_;
    std::vector<Damage> active_damage_;
    std::map<DamageType, float> resistances_; // 1.0=normal, 0.5=resistant, 2.0=vulnerable

    int rollSpirit();
    inline static int creatureCount = 0;

};


#endif
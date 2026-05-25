#ifndef CREATURE_H
#define CREATURE_H

#include <memory>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "constants.h"
#include "attribute.h"
#include "damage.h"

enum class MODE {
    LOW_CUR_HP  = 1,
    HIGH_CUR_HP = 2,
    LOW_MAX_HP  = 3,
    HIGH_MAX_HP = 4,
    LOW_ATTACK  = 5,
    HIGH_ATTACK = 6,
    LOW_DEFENSE = 7,
    HIGH_DEFENSE = 8,
    LOW_SPIRIT  = 9,
    HIGH_SPIRIT = 10
};

class Creature {
public:
    inline static int getCreatureCount() { return creatureCount; }

    virtual std::unique_ptr<Damage> mainAttack();
    void takeDamage(std::unique_ptr<Damage> d);
    void processDamage(int current_turn);
    virtual Creature& chooseTarget(std::vector<Creature*> creatures, MODE m);

    std::string getName()      const { return name_; }
    int getCurrentHP()         const { return current_hp; }
    int getMaxHP()             const { return max_hp_; }
    int getAttack()            const { return attack_.getValue(); }
    int getDefense()           const { return defense_.getValue(); }
    int getSpirit()            const { return spirit_.getValue(); }
    MODE getMode()             const { return mode_; }

    bool isAlive() { return current_hp > 0; }
    bool validate();

    Creature();
    Creature(std::string name, int hp, int attack, int defense, int spirit, MODE mode = MODE::LOW_CUR_HP);
    virtual ~Creature();

private:
    const std::string name_;
    const Attribute hp_;       // AttributeType::HP,      raw=alloc, floor=BASE_STAT
    const Attribute attack_;   // AttributeType::ATTACK,  raw=alloc, floor=BASE_STAT
    const Attribute defense_;  // AttributeType::DEFENSE, raw=alloc, floor=BASE_STAT
    const Attribute spirit_;   // AttributeType::SPIRIT,  raw=alloc, floor=1
    const int max_hp_;         // depends on spirit_, must be declared after it
    int current_hp;
    MODE mode_;
    std::vector<std::unique_ptr<Damage>> active_damage_;
    std::map<DamageType, float> resistances_; // 1.0=normal, 0.5=resistant, 2.0=vulnerable

    inline static int creatureCount = 0;
};

#endif

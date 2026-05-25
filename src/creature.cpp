#include "creature.h"
#include "damage.h"
#include "rng.h"
#include "utils.h"
#include <algorithm>

Creature::Creature()
    : name_("Grunt")
    , hp_(AttributeType::HP,      10)
    , attack_(AttributeType::ATTACK,  10)
    , defense_(AttributeType::DEFENSE, 6)
    , spirit_(AttributeType::SPIRIT,   4)
    , max_hp_((BASE_STAT + 10) * (4 + 1))
    , current_hp(max_hp_)
    , mode_(MODE::LOW_CUR_HP)
    { creatureCount++; }

Creature::Creature(std::string name, int hp, int attack, int defense, int spirit, MODE mode)
    : name_(name)
    , hp_(AttributeType::HP,      hp)
    , attack_(AttributeType::ATTACK,  attack)
    , defense_(AttributeType::DEFENSE, defense)
    , spirit_(AttributeType::SPIRIT,  spirit)
    , max_hp_((BASE_STAT + hp) * (spirit + 1))
    , current_hp(max_hp_)
    , mode_(mode)
    { creatureCount++; }

Creature::~Creature() {}


Creature& Creature::chooseTarget(std::vector<Creature*> creatures, MODE m) {
    std::vector<Creature*> targets;
    for (Creature* c : creatures) {
        if (c != this && c->isAlive()) targets.push_back(c);
    }
    if (targets.empty()) return *this;

    auto cmp = [](auto fn) {
        return [fn](Creature* a, Creature* b){ return fn(a) < fn(b); };
    };

    std::vector<Creature*>::iterator it;
    switch (m) {
        case MODE::LOW_CUR_HP:   it = std::min_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getCurrentHP(); })); break;
        case MODE::HIGH_CUR_HP:  it = std::max_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getCurrentHP(); })); break;
        case MODE::LOW_MAX_HP:   it = std::min_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getMaxHP();     })); break;
        case MODE::HIGH_MAX_HP:  it = std::max_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getMaxHP();     })); break;
        case MODE::LOW_ATTACK:   it = std::min_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getAttack();    })); break;
        case MODE::HIGH_ATTACK:  it = std::max_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getAttack();    })); break;
        case MODE::LOW_DEFENSE:  it = std::min_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getDefense();   })); break;
        case MODE::HIGH_DEFENSE: it = std::max_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getDefense();   })); break;
        case MODE::LOW_SPIRIT:   it = std::min_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getSpirit();    })); break;
        case MODE::HIGH_SPIRIT:  it = std::max_element(targets.begin(), targets.end(), cmp([](Creature* c){ return c->getSpirit();    })); break;
        default: return *targets[RNG::randomValue(0, targets.size() - 1)];
    }
    return **it;
}

std::unique_ptr<Damage> Creature::mainAttack() {
    return std::make_unique<InstantDamage>(attack_.getValue(), DamageType::PHYSICAL, this);
}

void Creature::takeDamage(std::unique_ptr<Damage> d) {
    active_damage_.push_back(std::move(d));
}

void Creature::processDamage(int current_turn) {
    (void)current_turn;
    for (auto& d : active_damage_) {
        d->tick();
        int hp_loss = d->deliverable();
        if (hp_loss > 0) {
            current_hp = std::max(0, current_hp - hp_loss);
            std::cout << colorMe(name_, Color::CYAN) << " takes "
                      << colorMe(std::to_string(hp_loss), Color::RED) << " damage! ("
                      << colorMe(std::to_string(current_hp), Color::GREEN) << " HP remaining)\n";
        }
    }
    active_damage_.erase(
        std::remove_if(active_damage_.begin(), active_damage_.end(),
            [](const std::unique_ptr<Damage>& d){ return d->isExpired(); }),
        active_damage_.end()
    );
}

bool Creature::validate() {
    int total = hp_.getBase() + attack_.getBase() + defense_.getBase() + spirit_.getBase();
    if (total != POINT_POOL) {
        std::cout << name_ << " doesn't qualify for battle." << std::endl;
        std::cout << "Stat Total: " << total << std::endl;
        return false;
    }
    return true;
}

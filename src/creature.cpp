#include "creature.h"
#include "damage.h"
#include "rng.h"
#include "utils.h"
#include <algorithm>

Creature::Creature()
    : name_("Grunt")
    , hp_base_(10)
    , attack_base_(10)
    , attack_(attack_base_ + BASE_STAT)
    , defense_base_(6)
    , defense_(defense_base_ + BASE_STAT)
    , spirit_base_(4)
    , spirit_(spirit_base_ + 1)
    , max_hp_((BASE_STAT + hp_base_) * spirit_)
    , current_hp(max_hp_)
    , mode_(MODE::LOW_CUR_HP)
    {creatureCount++;}

Creature::Creature(std::string name, int hp, int attack, int defense, int spirit, MODE mode)
    : name_(name)
    , hp_base_(hp)
    , attack_base_(attack)
    , attack_((attack_base_ + BASE_STAT))
    , defense_base_(defense)
    , defense_((defense_base_ + BASE_STAT))
    , spirit_base_(spirit)
    , spirit_(spirit_base_ + 1)
    , max_hp_((BASE_STAT + hp_base_) * 4)
    , current_hp(max_hp_)
    , mode_(mode)
    {creatureCount++;}

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

void Creature::mainAttack(Creature& target) {
    int spirit_chance = rollSpirit();
    const int raw = attack_ + RNG::randomValue((-spirit_chance), (spirit_chance));
    const int damage = std::max(1, raw);
    int dealt = target.takeDamage(damage, this);
    std::cout << colorMe(name_, Color::CYAN) << " attacks " << colorMe(target.getName(), Color::CYAN)
              << " for " << colorMe(std::to_string(damage), Color::RED) << "!\n";
    std::cout << colorMe(target.getName(), Color::CYAN) << " only takes "
              << colorMe(std::to_string(dealt), Color::RED) << " damage!\n";
    std::cout << colorMe(target.getName(), Color::CYAN) << " health is: "
              << colorMe(std::to_string(target.getCurrentHP()), Color::GREEN) << " HP\n";
}

int Creature::takeDamage(int raw_damage, Creature* source) {
    // chaos scales with attacker spirit: high-spirit attackers deal variable damage, not high-spirit defenders
    int attacker_spirit = source ? source->getSpirit() : 1;
    int chaos = RNG::randomValue(1, attacker_spirit);
    int rate = (defense_ * 256) / (defense_ + chaos * SPIRIT_SCALE);    // diminishing returns with noise
    int net = std::max(1, raw_damage - (raw_damage * rate / 256));      // floored at 1 (min 1 damage)
    applyDamage(Damage(net, DamageType::PHYSICAL, DamageMode::INSTANT, 0, 0, source));
    return net;
}

void Creature::applyDamage(const Damage& d) {
    float mult = 1.0f;
    auto it = resistances_.find(d.getType());
    if (it != resistances_.end()) mult = it->second;

    int effective = static_cast<int>(d.getAmount() * mult);

    if (d.getMode() == DamageMode::INSTANT) {
        current_hp = std::max(0, current_hp - std::max(1, effective));
    } else {
        active_damage_.push_back(Damage(effective, d.getType(), d.getMode(), d.getDuration(), d.getTurnReceived(), d.getSource()));
    }
}

void Creature::processDamage(int current_turn) {
    (void)current_turn;
    for (auto& d : active_damage_) {
        d.tick();
        int hp_loss = d.deliverable();
        if (hp_loss > 0) current_hp = std::max(0, current_hp - hp_loss);
    }
    active_damage_.erase(
        std::remove_if(active_damage_.begin(), active_damage_.end(),
            [](const Damage& d){ return d.isExpired(); }),
        active_damage_.end()
    );
}


bool Creature::validate() {
    if (hp_base_ + attack_base_  + defense_base_  + spirit_base_ != POINT_POOL) {
        std::cout << name_ << " doesn't qualify for battle." << std::endl;
        std::cout << "Stat Total: " << hp_base_ + attack_base_  + defense_base_  + spirit_base_ << std::endl;
        return false;
    }
    return true;
}

int Creature::rollSpirit() {
    return RNG::randomValue(1, spirit_);
}


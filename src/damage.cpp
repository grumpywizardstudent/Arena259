#include "damage.h"

Damage::Damage(int amount, DamageType type, DamageMode mode, int duration, int turn_received, Creature* source)
    : amount_(amount)
    , type_(type)
    , mode_(mode)
    , duration_(duration)
    , turn_received_(turn_received)
    , source_(source)
    , accumulated_(0)
{}

bool Damage::isExpired() const {
    return duration_ <= 0;
}

void Damage::tick() {
    if (mode_ == DamageMode::STACK) accumulated_ += amount_;
    duration_--;
}

int Damage::deliverable() const {
    switch (mode_) {
        case DamageMode::INSTANT: return amount_;
        case DamageMode::DOT:     return amount_;
        case DamageMode::STACK:   return isExpired() ? accumulated_ : 0;
    }
    return 0;
}

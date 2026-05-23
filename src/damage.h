#ifndef DAMAGE_H
#define DAMAGE_H

class Creature;

enum class DamageType {
    PHYSICAL,
    MAGICAL,
    SPIRITUAL,
    ELEMENTAL
};

enum class DamageMode {
    INSTANT,
    DOT,    // deal amount_ per tick for duration_ ticks
    STACK   // accumulate amount_ each tick, deliver total when duration_ expires
};

class Damage {
public:
    // amount is int for now; will accept Attribute once that type is defined
    Damage(int amount, DamageType type, DamageMode mode, int duration, int turn_received, Creature* source);

    int        getAmount()       const { return amount_; }
    DamageType getType()         const { return type_; }
    DamageMode getMode()         const { return mode_; }
    int        getDuration()     const { return duration_; }
    int        getTurnReceived() const { return turn_received_; }
    Creature*  getSource()       const { return source_; }

    bool isExpired()   const;  // true when duration_ <= 0
    void tick();               // decrement duration_; STACK also accumulates amount_ into accumulated_
    int  deliverable() const;  // hp to subtract this tick: DOT=amount_, STACK=accumulated_ on expiry

private:
    int        amount_;
    DamageType type_;
    DamageMode mode_;
    int        duration_;
    int        turn_received_;
    Creature*  source_;      // raw pointer — source may die before DoT/STACK expires
    int        accumulated_; // STACK mode accumulator
};

#endif

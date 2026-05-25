#ifndef DAMAGE_H
#define DAMAGE_H

class Creature;

enum class DamageType {
    PHYSICAL,
    MAGICAL,
    SPIRITUAL,
    ELEMENTAL
};

class Damage {
public:
    Damage(int amount, DamageType type, Creature* source)
        : amount_(amount), type_(type), source_(source) {}
    virtual ~Damage() = default;

    int        getAmount() const { return amount_; }
    DamageType getType()   const { return type_; }
    Creature*  getSource() const { return source_; }  // may be null — always null-check before deref

    virtual bool isExpired()   const = 0;
    virtual void tick()              = 0;
    virtual int  deliverable() const = 0;

protected:
    int        amount_;
    DamageType type_;
    Creature*  source_;
};

// Delivers amount_ once on the first processDamage tick, then expires.
class InstantDamage : public Damage {
public:
    InstantDamage(int amount, DamageType type, Creature* source)
        : Damage(amount, type, source) {}

    bool isExpired()   const override { return ticked_; }
    void tick()              override { ticked_ = true; }
    int  deliverable() const override { return ticked_ ? amount_ : 0; }

private:
    bool ticked_ = false;
};

// Delivers amount_ each tick for duration_ ticks.
class DotDamage : public Damage {
public:
    DotDamage(int amount, DamageType type, int duration, Creature* source)
        : Damage(amount, type, source), duration_(duration) {}

    bool isExpired()   const override { return duration_ <= 0; }
    void tick()              override { duration_--; }
    int  deliverable() const override { return amount_; }

private:
    int duration_;
};

// Accumulates amount_ each tick; delivers the total only when duration_ expires.
class StackDamage : public Damage {
public:
    StackDamage(int amount, DamageType type, int duration, Creature* source)
        : Damage(amount, type, source), duration_(duration), accumulated_(0) {}

    bool isExpired()   const override { return duration_ <= 0; }
    void tick()              override { accumulated_ += amount_; duration_--; }
    int  deliverable() const override { return isExpired() ? accumulated_ : 0; }

private:
    int duration_;
    int accumulated_;
};

#endif

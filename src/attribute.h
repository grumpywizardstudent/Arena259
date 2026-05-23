#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

// Placeholder — will be fully defined in the Attribute refactor.
// Creature stats (HP, Attack, Defense, Spirit) will become Attribute instances.
class Attribute {
public:
    explicit Attribute(int value) : value_(value) {}
    int getValue() const { return value_; }
private:
    int value_;
};

#endif

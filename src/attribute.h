#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "constants.h"

enum class AttributeType { HP, ATTACK, DEFENSE, SPIRIT };

class Attribute {
public:
    Attribute(AttributeType type, int raw)
        : type_(type), base_(raw) {}

    AttributeType getType()  const { return type_; }
    int           getBase()  const { return base_; }
    int           getValue() const { return base_ + floorFor(type_); }

private:
    AttributeType type_;
    int           base_;

    static int floorFor(AttributeType t) {
        return (t == AttributeType::SPIRIT) ? 1 : BASE_STAT;
    }
};

#endif

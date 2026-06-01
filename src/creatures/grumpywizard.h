#pragma once

#include "../creature.h"

class GrumpyWizard : public Creature {
    public:
        GrumpyWizard() : Creature("The Grumpy Wizard", 120, 20, 20) {}

        void specialMove(Creature& target) override;
        void attack(Creature& target, int modifier=0) override;

};
#include "grumpywizard.h"

void GrumpyWizard::specialMove(Creature& target) {
      std::cout << "The Grumpy Wizard casts Polymorph on " << target.getName() << std::endl;
      target.setName("A Harmless Frog");
      target.setDamage(1);
      target.setHealth(3);
      std::cout << target.getName() << " has been transformed!" << std::endl;
}


void GrumpyWizard::attack(Creature& target, int modifier) {
            std::cout << "The Grumpy Wizard casts Disintegrate on " << target.getName() << std::endl;
            std::cout << target.getName() << " turns to dust!" << std::endl;
            target.takeDamage(5000);

}
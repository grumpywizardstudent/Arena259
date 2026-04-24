#include "arena.h"
#include "creature.h"
#include "./creatures/sumo_sally.h"
#include "./creatures/viper.h"
#include "./creatures/giantleech.h"
#include "./creatures/boogeyman.h"
#include "./creatures/clawdragon.h"
#include "./creatures/segoblin.h"
#include <vector>

int main()
{
    Creature Grunt;
    Creature Boogeyman(makeBoogeyman());
    Creature ClawDragon(makeClawdragon());
    Creature GiantLeech(makeGiantleech());
    Creature Segoblin(makeSEGoblin());
    Creature SumoSally(make_sumo_sally());
    Creature Viper(makeViper());
    

// we'll need this sooner or later!
    std::vector<Creature*> creatures;

        creatures.push_back(&Grunt);
        creatures.push_back(&Boogeyman);
        creatures.push_back(&ClawDragon);
        creatures.push_back(&GiantLeech);
        creatures.push_back(&Segoblin);
        creatures.push_back(&SumoSally);
        creatures.push_back(&Viper);

    std::cout << "Total Creatures created: " << Creature::getCreatureCount() << std::endl;

    Arena::battle(Grunt, Viper);
  

    return 0;
}

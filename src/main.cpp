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
    Creature grunt;
    Boogeyman boogeyman;
    Clawdragon clawdragon;
    GiantLeech giantleech;
    SEGoblin segoblin;
    SumoSally sumoSally;
    Viper viper;

    std::vector<Creature*> creatures;

        // creatures.push_back(&grunt);
        // creatures.push_back(&boogeyman);
        creatures.push_back(&clawdragon);
        creatures.push_back(&giantleech);
        creatures.push_back(&segoblin);
        creatures.push_back(&sumoSally);
        creatures.push_back(&viper);

    std::cout << "Total Creatures created: " << Creature::getCreatureCount() << std::endl;

    Arena battle(creatures);
    battle.battle();

    return 0;
}

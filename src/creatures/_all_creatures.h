#ifndef _ALL_CREATURES_H
#define _ALL_CREATURES_H

#include "boogeyman.h"
#include "clawdragon.h"
#include "giantleech.h"
#include "segoblin.h"
#include "sumo_sally.h"
#include "viper.h"
#include "../random.h"
#include <array>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdlib.h>

const std::array<std::string, 76> MONSTER_NAMES = {
    "Banshee", "Basilisk", "Behemoth", "Bogeyman", "Centaur",
    "Cerberus", "Changeling", "Chimera", "Cyclops", "Demon",
    "Devil", "Djinn", "Dragon", "Dryad", "Dullahan",
    "Elemental", "Fairy", "Gargoyle", "Genie", "Ghost",
    "Ghoul", "Giant", "Gnome", "Goblin", "Golem",
    "Gorgon", "Gremlin", "Griffin", "Hag", "Harpy",
    "Hydra", "Imp", "Kappa", "Kelpie", "Kobold",
    "Kraken", "Lamia", "Leprechaun", "Leviathan", "Lich",
    "Lizardfolk", "Manticore", "Medusa", "Mermaid", "Minotaur",
    "Mummy", "Naga", "Nymph", "Ogre", "Orc",
    "Pegasus", "Phoenix", "Poltergeist", "Rakshasa", "Satyr",
    "Scylla", "SeaSerpent", "Shapeshifter", "Siren", "Skeleton",
    "Specter", "Sphinx", "Sprite", "Tengu", "Titan",
    "Treant", "Troll", "Unicorn", "Vampire", "Werewolf",
    "Wendigo", "Wraith", "Wyvern", "Yeti", "Zombie"
};


Creature randomCreature() {
    int rand_index = Random::randomValue(0, MONSTER_NAMES.size() - 1);
    std::string name = "Basic" + MONSTER_NAMES[rand_index];
    int health = Random::randomValue(80, 120);
    int attack = Random::randomValue(8, 20);

    return Creature(name, health, attack);
}


#endif
#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include "arena.h"
#include "creature.h"
#include "creatures.h"
#include "utils.h"

static const std::vector<std::string> CREATURE_NAMES = {
    "AbominableMudman", "Banshee",       "BlackHole",   "Boogeyman",
    "Clawdragon",       "DarkJellyfish", "LordDevilious","GiantLeech",
    "GrumpyWizard",     "Jeff",          "JumpingSpider","Magician",
    "RingmasterHawk",   "SEGoblin",      "Sumo Sally",   "Viper"
};

static std::unique_ptr<Creature> makeCreature(int choice) {
    switch (choice) {
        case  1: return std::make_unique<AbominableMudman>();
        case  2: return std::make_unique<Banshee>();
        case  3: return std::make_unique<BlackHole>();
        case  4: return std::make_unique<Creature>(makeBoogeyman());
        case  5: return std::make_unique<Clawdragon>();
        case  6: return std::make_unique<DarkJellyfish>();
        case  7: return std::make_unique<LordDevilious>();
        case  8: return std::make_unique<Creature>(makeGiantleech());
        case  9: return std::make_unique<GrumpyWizard>();
        case 10: return std::make_unique<Jeff>();
        case 11: return std::make_unique<Jumpingspider>();
        case 12: return std::make_unique<Magician>();
        case 13: return std::make_unique<RingmasterHawk>();
        case 14: return std::make_unique<Creature>(makeSEGoblin());
        case 15: return std::make_unique<Creature>(make_sumo_sally());
        case 16: return std::make_unique<Creature>(makeViper());
        default: return nullptr;
    }
}

static void printRoster() {
    std::cout << "\nCreatures:\n";
    for (int i = 0; i < (int)CREATURE_NAMES.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << CREATURE_NAMES[i] << "\n";
    }
}

int main()
{
while(true) {

    std::cout << Color::YELLOW << "\n\n\n=============================\n";
    std::cout << "   WELCOME TO THE ARENA!        \n";
    std::cout << "=============================\n" << Color::RESET;

    // --- Game mode selection ---
    int mode = 0;
    while (mode < 1 || mode > 3) {
        std::cout << "\nSelect a game mode:\n"
                  << "  1. Battle        (2 creatures)\n"
                  << "  2. Battle Royale (2 or more creatures)\n"
                  << "  3. Tournament    (2 or more creatures)\n"
                  << "Choice: ";
        std::cin >> mode;
        if (std::cin.fail() || mode < 1 || mode > 3) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            mode = 0;
        }
    }

    // --- Creature selection ---
    Creatures creatures;
    std::set<int> picked;
    int needed = (mode == 1) ? 2 : 0;  // 0 = unlimited (until user says done)

    printRoster();

    if (mode == 1) {
        std::cout << "\nPick 2 creatures for battle.\n";
    } else {
        std::cout << "\nEnter creature numbers one at a time. Enter 0 when done (minimum 2).\n";
    }

    while (true) {
        if (mode == 1 && (int)creatures.size() == 2) break;

        if (mode != 1) {
            std::cout << "Add creature (0 to finish): ";
        } else {
            std::cout << "Pick creature " << (creatures.size() + 1) << ": ";
        }

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 0) {
            if (mode == 1) { std::cout << "Please pick 2 creatures.\n"; continue; }
            if ((int)creatures.size() < 2) { std::cout << "Select at least 2 creatures.\n"; continue; }
            break;
        }

        if (choice < 1 || choice > 16) {
            std::cout << "Please enter a number between 1 and 16.\n";
            continue;
        }

        if (picked.count(choice)) {
            std::cout << CREATURE_NAMES[choice - 1] << " is already in the arena.\n";
            continue;
        }

        picked.insert(choice);
        creatures.push_back(makeCreature(choice));
        std::cout << CREATURE_NAMES[choice - 1] << " added.\n";
    }

    // --- Launch ---
    std::cout << "\nTotal creatures: " << Creature::getCreatureCount() << "\n";

    Arena arena(std::move(creatures));
    if      (mode == 1) arena.battle();
    else if (mode == 2) arena.battleRoyale();
    else                arena.tournament();
}

    return 0;
}

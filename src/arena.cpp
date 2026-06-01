#include <iostream>
#include <iomanip>
#include <algorithm>
#include "utils.h"
#include "arena.h"
#include "rng.h"

// Removes conditional/duplicate print statements when a winner is decided
void Arena::printWinner(Creature& winner) {
    std::cout << Color::YELLOW << "\n=============================\n" << Color::RESET;
    std::cout << colorMe(winner.getName(), Color::GREEN) << " wins!\n";
    std::cout << colorMe(winner.getName(), Color::GREEN) << " has "
              << colorMe(std::to_string(winner.getHealth()), Color::GREEN) << " HP remaining.\n";
    std::cout << Color::YELLOW << "=============================\n" << Color::RESET;
}

void Arena::printBegin() {
    std::cout << Color::YELLOW << "=============================\n";
    std::cout << "        ARENA BATTLE        \n";
    std::cout << "=============================\n" << Color::RESET;
    for (auto& c : creatures) {
        std::cout << "  " << colorMe(c->getName(), Color::CYAN)
                  << " (" << colorMe(std::to_string(c->getHealth()), Color::GREEN) << " HP)\n";
    }
    std::cout << Color::YELLOW << "=============================\n" << Color::RESET;
}

void Arena::printTurn(int turn) {
    std::cout << Color::BLUE << "\n-----------------------------\n";
    std::cout << "Turn " << turn << " | " << getModString() << "\n";
    std::cout << "-----------------------------\n" << Color::RESET;
}

bool Arena::takeTurn(Creature& acting, Creature& target) {
    switch (mod) {
        case Modifier::NO_SPECIAL:
            std::cout << "Special Moves blocked by Arena!" << std::endl;
            if (RNG::randomValue(1, 100) <= acting.specialChance()) 
                { std::cout << acting.getName() + "can't use Special Move!" << std::endl; }
            else { acting.attack(target); }
            break;
        case Modifier::DOUBLE_SPECIAL:
            std::cout << "Chance for Special is DOUBLED!" << std::endl;
            if (RNG::randomValue(1, 100) <= acting.specialChance()) { acting.specialMove(target); }
            if (RNG::randomValue(1, 100) <= acting.specialChance()) { acting.specialMove(target); }
            else { acting.attack(target); }
            break;
        case Modifier::ATTACK_BUFF:
            if (RNG::randomValue(1, 100) <= acting.specialChance()) { acting.specialMove(target); }
            else { acting.attack(target, 10); }
            break;
        case Modifier::DEFENSE_BUFF: {
            int original_value = target.getDefense();
            target.setDefense(original_value + 5);
            if (RNG::randomValue(1, 100) <= acting.specialChance()) { acting.specialMove(target); }
            else { acting.attack(target); }
            target.setDefense(original_value);
            break;
        }
        default:
            if (RNG::randomValue(1, 100) <= acting.specialChance()) { acting.specialMove(target); }
            else { acting.attack(target); }
            break;
    }
    return target.isAlive();
}

void Arena::addCreature(std::unique_ptr<Creature> creature) { creatures.push_back(std::move(creature)); }


void Arena::fightPair(Creature& a, Creature& b) {
    Creature* first  = (RNG::flipCoin() == 1) ? &a : &b;
    Creature* second = (first == &a) ? &b : &a;

    std::cout << first->getName() << " vs " << second->getName() << "\n";

    hasWinner = false;
    int turn = 1;
    while (!hasWinner) {
        rotateMod();
        printTurn(turn);
        if (!takeTurn(*first, *second)) { hasWinner = true; break; }
        if (!takeTurn(*second, *first)) { hasWinner = true; break; }
        turn++;
    }
}

bool Arena::validateBattle(Creatures& creatures) {
    std::string error = "The stats of the creatures are invalid, so the battle cannot take place.";
        for (const auto& c : creatures) {
            if (!Creature::isValid(*c)) {
                std::cerr << error << std::endl;
                return false;
            }
        }
    return true;
}

void Arena::battleRoyale()
{
    int turn = 1;
// must use a non-owning structure because unique_ptr is not copyable.
    std::vector<Creature*> still_alive;

    printBegin();

    hasWinner = false;
    
    while (!hasWinner)
    {   
        rotateMod();
        printTurn(turn);
        for (auto& c : creatures)
        {
            if (!c->isAlive()) continue;
            std::cout << "\n>> " << colorMe(c->getName() + "'s", Color::CYAN) << " turn:\n";
            Creature& target = c->chooseTarget(creatures);
            bool survived = takeTurn(*c, target);
            if (!survived) {
                std::cout << colorMe("** " + target.getName() + " has been defeated! **", Color::RED) << "\n";
            }
        }
        turn++;

        still_alive.clear();
        for (auto& c: creatures)
        {
            if (c->isAlive()) { still_alive.push_back(&(*c)); }
        }
        if (still_alive.size() == 1) {
            printWinner(*still_alive[0]);
            hasWinner = true;
        }
    }
}

void Arena::battle()
{
    if (!Arena::validateBattle(creatures)) { return; }
    fightPair(*creatures[0], *creatures[1]);
    Creature& winner = creatures[0]->isAlive() ? *creatures[0] : *creatures[1];
    printWinner(winner);
}

void Arena::tournament() {

    std::shuffle(creatures.begin(), creatures.end(), RNG::gen);

    std::cout << "---------------------------------\n";
    std::cout << "--- The tournament has begun! ---\n";
    std::cout << "---------------------------------\n\n";

    int heat = 1;

    while (creatures.size() > 1) {
        std::cout << "========== HEAT "
                  << heat
                  << " ==========\n\n";

        Creatures winners;

        for (size_t i = 0; i < creatures.size(); i += 2) {
            // Odd number of creatures automatic advancement
            if (i + 1 >= creatures.size()) {

                std::cout << creatures[i]->getName()
                          << " advances automatically!\n\n";

                winners.push_back(std::move(creatures[i]));
                continue;
            }

            Creature& c1 = *creatures[i];
            Creature& c2 = *creatures[i + 1];

            int c1Health = c1.getHealth();
            int c2Health = c2.getHealth();

            fightPair(c1, c2);

            if (c1.isAlive()) {
                printWinner(c1);
                c1.setHealth(c1Health);
                winners.push_back(std::move(creatures[i]));
            }
            else {
                printWinner(c2);
                c2.setHealth(c2Health);
                winners.push_back(std::move(creatures[i + 1]));
            }

            std::cout << "---------------------------------\n\n";
        }

        creatures = std::move(winners);
        heat++;
    }

    std::cout << "---------------------------------\n";
    std::cout << "--- The tournament has ended! ---\n";
    std::cout << "---------------------------------\n\n";

    std::cout << "- The tournament champion is: "
              << creatures[0]->getName() << "! -\n";
    printWinner(*creatures[0]);
}

// void Arena::printStats(Creature& a, Creature& b, int turns) {

//     // print winner
//     std::cout << "Battle finished, the winner is ";
//     if (a->isAlive())
//     {
//         std::cout << a->getName() << "!" << std::endl;
//     }
//     else
//     {
//         std::cout << b->getName() << "!" << std::endl;
//     }

//     // arena stats
//     std::cout << "Total turns: " << turns << std::endl;
//     std::cout << "Total Damage Dealt: " << a->getDamageDealt() + b->getDamageDealt() << std::endl;
//     std::cout << std::endl;

//     // a creature stats
//     std::cout << a->getName() << " Health: " << a->getHealth() << "/" << a->getStartHealth() << std::endl;
//     std::cout << a->getName() << " Damage Dealt: " << a->getDamageDealt() << std::endl;
//     std::cout << std::endl;

//     // b creature stats
//     std::cout << b->getName() << " Health: " << b->getHealth() << "/" << b->getStartHealth() << std::endl;
//     std::cout << b->getName() << " Damage Dealt: " << b->getDamageDealt() << std::endl;

// }

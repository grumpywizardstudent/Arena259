#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "utils.h"
#include "arena.h"
#include "rng.h"  // renamed arenarand to rng for readability/ease of use

// Removes conditional/duplicate print statements when a winner is decided
void Arena::printWinner(Creature& winner) {
    std::cout << Color::YELLOW << "\n=============================\n" << Color::RESET;
    std::cout << colorMe(winner.getName(), Color::GREEN) << " wins!\n";
    std::cout << colorMe(winner.getName(), Color::GREEN) << " has "
              << colorMe(std::to_string(winner.getCurrentHP()), Color::GREEN) << " HP remaining.\n";
    std::cout << Color::YELLOW << "=============================\n" << Color::RESET;
}

void Arena::printBegin() {
    std::cout << Color::YELLOW << "=============================\n";
    std::cout << "        ARENA BATTLE        \n";
    std::cout << "=============================\n" << Color::RESET;
    for (Creature* c : creatures) {
        std::cout << "  " << colorMe(c->getName(), Color::CYAN)
                  << " (" << colorMe(std::to_string(c->getCurrentHP()), Color::GREEN) << " HP)\n";
    }
    std::cout << Color::YELLOW << "=============================\n" << Color::RESET;
}

void Arena::printTurn(int turn) {
    std::cout << Color::BLUE << "\n-----------------------------\n";
    std::cout << "Turn " << turn << "\n";
    std::cout << "-----------------------------\n" << Color::RESET;
}

bool Arena::takeTurn(Creature& acting, Creature& target) {
    acting.mainAttack(target);
    return target.isAlive();
}

bool Arena::checkPulse(Creature* c) {
    if (c == nullptr) { return false; };
    return c->isAlive();
}

void Arena::battle()
{
    int turn = 1;
    std::vector<Creature*> still_alive;

    printBegin();

    while (!hasWinner)
    {
        printTurn(turn);
        for (Creature* c : creatures)
        {
            if (!checkPulse(c)) continue;
            std::cout << "\n>> " << colorMe(c->getName() + "'s", Color::CYAN) << " turn:\n";
            Creature& target = c->chooseTarget(creatures, c->getMode());
            bool survived = takeTurn(*c, target);
            if (!survived) {
                std::cout << colorMe("** " + target.getName() + " has been defeated! **", Color::RED) << "\n";
            }
        }
        for (Creature* c : creatures)
            if (c->isAlive()) c->processDamage(turn);

        turn++;

        still_alive.clear();
        for (Creature* c : creatures)
        {
            if (checkPulse(c)) { still_alive.push_back(c); }
        }
        if (still_alive.size() == 1) {
            printWinner(*still_alive[0]);
            hasWinner = true;
        }
    }
}

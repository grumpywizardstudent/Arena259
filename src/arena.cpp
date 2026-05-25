#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "utils.h"
#include "arena.h"
#include "rng.h"

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

void Arena::takeTurn(Creature& acting, Creature& target) {
    auto d = acting.mainAttack();
    std::cout << colorMe(acting.getName(), Color::CYAN) << " attacks "
              << colorMe(target.getName(), Color::CYAN)
              << " for " << colorMe(std::to_string(d->getAmount()), Color::RED) << "!\n";
    target.takeDamage(std::move(d));
}

bool Arena::checkPulse(Creature* c) {
    if (c == nullptr) { return false; }
    return c->isAlive();
}

void Arena::battle()
{
    for (Creature* c : creatures)
        c->validate();

    int turn = 1;
    std::vector<Creature*> still_alive;

    printBegin();

    while (!hasWinner)
    {
        printTurn(turn);
        for (Creature* c : creatures)
        {
            if (!checkPulse(c)) continue;
            Creature& target = c->chooseTarget(creatures, c->getMode());
            if (&target == c) continue;  // no valid targets — last creature standing
            std::cout << "\n>> " << colorMe(c->getName() + "'s", Color::CYAN) << " turn:\n";
            takeTurn(*c, target);
        }

        for (Creature* c : creatures)
            if (c->isAlive()) c->processDamage(turn);

        for (Creature* c : creatures)
            if (!c->isAlive())
                std::cout << colorMe("** " + c->getName() + " has been defeated! **", Color::RED) << "\n";

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

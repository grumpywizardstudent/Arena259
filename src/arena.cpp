#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include "utils.h"
#include "arena.h"
#include "rng.h"  // renamed arenarand to rng for readability/ease of use

// Removes conditional/duplicate print statements when a winner is decided
void Arena::printWinner(Creature& winner) {
    std::cout << "\n=============================\n";
    std::cout << winner.getName() << " wins!" << std::endl;
    std::cout << winner.getName() << " has " << winner.getCurrentHP() << " HP remaining." << std::endl;
    std::cout << "=============================\n";
}

void Arena::printBegin() {
    std::cout << "=============================\n";
    std::cout << "        ARENA BATTLE        \n";
    std::cout << "=============================\n";
}

void Arena::printTurn(int turn) {
    std::cout << "\n-----------------------------\n";
	std::cout << "Turn " << turn << std::endl;
	std::cout << "-----------------------------\n";
}

void takeTurn(Creature& acting, Creature& target) {
    acting.mainAttack(target);
}

Arena::Arena(std::vector<Creature*> creatures)
{
    int turn = 1;
    while (!hasWinner)
    {
        for (Creature* c : creatures) 
        {
            takeTurn(*c, c->chooseTarget(creatures));
        }
        turn++;
    }

// more readable winner logic
    for (Creature* c : creatures) 
    {
        if (c->isAlive()) { still_alive.push_back(c); }
        if (still_alive.size() == 1) { printWinner(*still_alive[0]); }
        else (still_alive.clear());

    }
}

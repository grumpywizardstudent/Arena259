#include <iostream>
#include <algorithm>
#include <sstream>
#include "utils.h"
#include "arena.h"
#include "rng.h"  // renamed arenarand to rng for readability/ease of use

// Removes conditional/duplicate print statements when a winner is decided
void Arena::printWinner(Creature &winner, Creature &loser) {
    std::cout << "\n=============================\n";
    std::cout << winner.getName() << " defeats " << loser.getName() << "!" << std::endl;
    std::cout << winner.getName() << " has " << winner.getCurrentHP() << " HP remaining." << std::endl;
    std::cout << "=============================\n";
}


void Arena::battle(Creature &temp1, Creature &temp2)
{
    Creature* first;
    Creature* second;

    if (RNG::flipCoin() == 1) {
        first = &temp1;
        second = &temp2;
    } else {
        first = &temp2;
        second = &temp1;
    }

    Creature& a = *first;
    Creature& b = *second;

    if(!a.validate() || !b.validate()){
        return;
    }
	    
    std::cout << "=============================\n";
    std::cout << "        ARENA BATTLE        \n";
    std::cout << "=============================\n";

    std::cout << a.getName() << " vs " << b.getName() << std::endl;

    int turn = 1;

    while (a.isAlive() && b.isAlive())
    {
    std::cout << "\n-----------------------------\n";
	std::cout << "Turn " << turn << std::endl;
	std::cout << "-----------------------------\n";


	std::cout << std::left
                //   << std::setw(10) 
                //   << std::setw(10) 
                << a.getName() << " HP: " << a.getCurrentHP() << "\n"
                << b.getName() << " HP: " << b.getCurrentHP() << "\n";
        
    // use new mainAttack() method which handles printing info and takeDamage
        a.mainAttack(b); if (!b.isAlive()) {break;};
        b.mainAttack(a); if (!a.isAlive()) {break;};
        
        turn++;
    }

// more readable winner logic
    if (a.isAlive())    { printWinner(a, b); }
    else                { printWinner(b, a); }
}

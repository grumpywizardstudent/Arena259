#include <iostream>
#include "utils.h"
#include "arena.h"
#include "random.h"

bool Arena::takeTurn(Creature &acting, Creature &target) 
{
    std::cout << acting.name << " attacks for " << acting.damage  << std::endl;
    acting.attack(target);
    std::cout << target.name << " health: " << target.health << std::endl;

    return !target.isAlive();
}


void Arena::battle(Creature &a, Creature &b)
{

    std::cout << "\n================================\n";
    std::cout << a.name << " vs " << b.name << std::endl;
    std::cout << "================================";

    int turn = 1;

    /// set hasWinner to false before the while loop
    /// if takeTurn returns true, we break the loop and
    /// announce the winner.
    bool hasWinner = false;

    while (!hasWinner) /// Primary game loop
    {
        /// Announce turn number and then flip a coin to se
        /// which creature goes first.
        std::cout << "\nTurn " << turn << std::endl;
        if (Random::flipCoin()) {
            /// optional statement for debugging to show who won the coin toss
            // std::cout << "Heads! " << b.name << " goes first!" << std::endl; 

            hasWinner = takeTurn(b, a); if (hasWinner) {break;}
            hasWinner = takeTurn(a, b); if (hasWinner) {break;}
        }

        else {
            /// optional statement for debugging to show who won the coin toss
            // std::cout << "Tails! " << a.name << " goes first!" << std::endl;

            hasWinner = takeTurn(a, b); if (hasWinner) {break;}
            hasWinner = takeTurn(b, a); if (hasWinner) {break;}
        }

        turn++;
    }


    /// When the while loop breaks, we need to check to 
    /// see which creature is still alive and announce 
    /// them as the winner.
    if (a.isAlive())
    {
        std::cout << "\n================================\n";
        std::cout << a.name << " wins!" << std::endl;
        std::cout << "================================\n\n";
    }
    else
    {
        std::cout << "\n================================\n";
        std::cout << b.name << " wins!" << std::endl;
        std::cout << "================================\n\n";
    }
}
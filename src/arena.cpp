#include <iostream>
#include <iomanip>
#include "arena.h"

void Arena::battle(Creature &a, Creature &b)
{
    std::cout << a.name << " vs. " << b.name << std::endl;

    if(!Creature::validateBattle(a, b)){
        return;
    }

    std::cout << "=============================\n";
    std::cout << "        ARENA BATTLE        \n";
    std::cout << "=============================\n";

    std::cout << a.name << " vs " << b.name << std::endl;

    int turn = 1;

    while (a.isAlive() && b.isAlive())
    {
        std::cout << "-----------------------------\n";
	std::cout << "\nTurn " << turn << std::endl;
	std::cout << "-----------------------------\n";


	std::cout << std::left
                  << std::setw(10) << a.name << " HP: " << a.health << "\n"
                  << std::setw(10) << b.name << " HP: " << b.health << "\n";


        std::cout << a.name << " with attack power "<< a.damage << " attacks " << b.name << "!" << std::endl;
        a.attack(b);
        std::cout << b.name << " health is: " << b.health << " HP" << std::endl;


        std::cout << b.name << " with attack power " << b.damage << " attacks " << a.name << "!" << std::endl;
        b.attack(a);
        std::cout << a.name << " health is: " << a.health << " HP" << std::endl;

        turn++;
    }

    std::cout << "\n=============================\n";
    if (a.isAlive())
    {
        std::cout << a.name << " defeats " << b.name << "!" << std::endl;
        std::cout << a.name << " has " << a.health << " HP remaining." << std::endl;
    }
    else
    {
        std::cout << b.name << " defeats " << a.name << "!"<< std::endl;
        std::cout << b.name << " has " << b.health << " HP remaining." << std::endl;
    }
    std::cout << "\n=============================\n";
}

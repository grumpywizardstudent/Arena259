#ifndef ARENA_H
#define ARENA_H

#include "creature.h"
#include "rng.h"
#include<memory>
#include<vector>

// added a battle statistics function, good for debugging and generally fun

using Creatures = std::vector<std::unique_ptr<Creature>>;

enum class Modifier {
    NONE = 0,
    NO_SPECIAL,
    DOUBLE_SPECIAL,
    ATTACK_BUFF,
    DEFENSE_BUFF,
    COUNT
};

class Arena
{
public:
    Arena(Creatures creatures) : creatures(std::move(creatures)) {};
    ~Arena() { std::cout << "Arena destroyed" << std::endl; }
    void battle();
	void battleRoyale();
	void tournament();
    void printBegin();
    void printTurn(int turn);
    void printWinner(Creature& winner);
	bool validateBattle(Creatures& creature);
    bool takeTurn(Creature& acting, Creature& target); // return target->isAlive()

    void addCreature(std::unique_ptr<Creature> creature);

private:
    Modifier mod;
    bool hasWinner = false;
    void fightPair(Creature& a, Creature& b);
    void rotateMod() { mod = static_cast<Modifier>(RNG::randomValue(0, static_cast<int>(Modifier::COUNT))); };
    std::string getModString() const {
        switch (mod) {
            case Modifier::NO_SPECIAL:    return "No Special Moves";
            case Modifier::DOUBLE_SPECIAL: return "Double Special Chance";
            case Modifier::ATTACK_BUFF:   return "Attack Buff (+10)";
            case Modifier::DEFENSE_BUFF:  return "Defense Buff (+5)";
            default:                      return "No Modifier";
        }
    };
    Creatures defeated;
    Creatures creatures;
};

#endif

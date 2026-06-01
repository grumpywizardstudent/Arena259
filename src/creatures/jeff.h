#ifndef JEFF_H
#define JEFF_H

#include <string>
#include <iostream>
#include "../creature.h"

class Jeff : public Creature {
public:
	// Constructor 
	Jeff();

	void specialMove(Creature& other) override;
private:
	int timesUsed = 0;
};

#endif
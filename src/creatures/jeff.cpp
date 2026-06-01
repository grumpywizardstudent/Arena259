#include <chrono>
#include <thread>

// header files
#include "jeff.h"


// Constructor
Jeff::Jeff(): Creature("Jeff", 120, 5, 10){}
void Jeff::specialMove(Creature& other){
	if(timesUsed == 0){
		timesUsed++;
		std::cout << "Jeff is now angered." << std::endl;
		std::cout << "Jeff has pulled out his machine gun and fires at " << other.getName() << " dealing 20 damage." << std::endl;
		other.takeDamage(20);
	}

	else if(timesUsed == 1){
		timesUsed++;
		std::cout << "Jeff is even more angered now." << std::endl;
		std::cout << "Jeff has pulled out his rocket launcher and fires at " << other.getName() << " dealing 25 damage." << std::endl;
		other.takeDamage(25);
	}

	else if(timesUsed == 2){
		timesUsed++;
		std::cout << "Jeff is now infuriated." << std::endl;
		std::cout << "Jeff has pulled out his flamethrower and uses it on " << other.getName() << " dealing 30 damage." << std::endl;
		other.takeDamage(30);
	}

	else if(timesUsed == 3){
		std::cout << "Jeff now leaves quietly." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(10));
		std::cout << "20 minutes later Jeff returns with an M1 Abrams tank and fires at " << other.getName() << " dealing 40 damage." << std::endl;
		other.takeDamage(40);
	}
}
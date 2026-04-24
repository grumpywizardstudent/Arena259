#include <iostream>
#include "sumo_sally.h"

// This is the creation of a creature called Sumo Sally. 
// Sumo Sally is a creature that has the maximuum value for health and the minimum value for damage.
// Sumo Sally is a bullrider from wisconsin who moved to shanghai to persue a career in professional sumo wrestling.
// When in a battle, this creature does not use sumo wrestling at all but instead just insults people.
 
Creature make_sumo_sally(){
     return Creature("Sumo Sally", 10, 10, 8, 2);
}

//commenting out code, used for testing
//int main(){
//	Creature sumo_sally = make_sumo_sally();
//	
//	std::cout << sumo_sally.health << "\n" << sumo_sally.damage << "\n";	
//}

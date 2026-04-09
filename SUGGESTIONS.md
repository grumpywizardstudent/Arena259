> ## When contributing to this document, add your new suggestion directly below the `br` elements following this comment to prevent collision/overwriting of other contributors. Suggestions should use the following convention `# <suggestion title> - <next id>`. The inclusion of ID's is important so that a  particular suggestion can be directly referenced and searched for in DESIGN.md where specific  implementations of a suggestion can be proposed and iterated on without modifying the original suggestion/concept.
<br>
<br>

# Turn-based vs Tick-based combat (Raylib?)
> In a turn-based system, creatures can only act on their "turn" and intervals between abilities require an internal counter. 

> In a tick-based system, creatures have a "speed" attribute which is used to count the number of frames or ticks in the simulation. In this system a "fast" creature might attack twice before a "slow" creature has a chance to land a blow. Setting this system up is easy enough with Raylib and a conditional like `if (frame_count % speed == 0) {do something}.


# Tournament Organization - 06
The Arena should have a tournament style where 1v1 fights between each of programs until we have winner. However every program will get to battle each other so that we have a defentive winner on who won the most fights. This'll prevent juggernaut programs being picked off because they were unlucky with their first match.

# Random Events - 05    
We can add random events to make certain abilities more or less effective. It doesn't have to be specifically events either, it could be an entire environment, or events tied to an environment that can be activated in a special way. 

# Attribute Points - 04
Each class will have attributes, such as HP, Defense, Damage, etc...
If we say each class can have n attribute points, each classmate can distribute the points into their class accross all the stats.
With some tinkering, this could be a good step for ensuring balance.

# Buff Debuff Class - 03
add a buff/debuff class that stores any modifiers that will be added to a creature.

# Balanced attributes - 02
e.g. if a character is heavy, they will move slow but have more health, if they are light, they can move quick but has less health

# Creature Base Class - 01
All battling creatures should be a derived class of Creature to ensure that the contracts for creature to creature interaction remain consistent. To change a contract, we modify the base class first and then enforce all derived classes to comply at instantiation.
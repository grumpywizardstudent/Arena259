#include "viper.h"

Creature makeViper()
{
    std::string n = "Viper";
    return Creature(n, 8, 17, 3, 2);
}
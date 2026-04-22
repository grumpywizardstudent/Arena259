#include "viper.h"

Creature makeViper()
{
    std::string n = "Viper";
    int h = 80;
    int d = 19;
    return Creature(n, h, d);
}
#include "viper.h"

Creature makeViper()
{
    std::string n = "Viper";
    int h = 80;
    int d = 20;
    return Creature(n, h, d);
}
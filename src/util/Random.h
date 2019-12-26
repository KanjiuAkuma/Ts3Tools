/**
  * Created by Joscha Vack on 12/9/2019.
  *
  **/

#ifndef TS3TOOLS_RANDOM_H
#define TS3TOOLS_RANDOM_H

#include <random>


class Random {
private:
    std::random_device random_device; // create object for seeding
    std::mt19937 engine{random_device()}; // create engine and seed it
    std::uniform_real_distribution<> dist = std::uniform_real_distribution<>(0, 1);
public:

    double randDouble(double min, double max);
    int randInt(int min, int max);

};


#endif //TS3PLUGINTEMPLATE2_RANDOM_H

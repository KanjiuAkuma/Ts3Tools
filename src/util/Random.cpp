/**
  * Created by Joscha Vack on 12/9/2019.
  *
  **/

#include "Random.h"

double Random::randDouble(double min, double max) {
    return min + dist(engine) * (max - min);
}

int Random::randInt(int min, int max) {
    return (int) randDouble(min, max);
}

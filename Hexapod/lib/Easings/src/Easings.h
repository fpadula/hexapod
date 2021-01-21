#ifndef EASINGS_H
#define EASINGS_H

#include <Arduino.h>

class Easings{
    public:
        static float linear(float, float, float, float);
        static float expo(float, float, float, float);
        static float bounce_out(float, float, float, float);
};

#endif
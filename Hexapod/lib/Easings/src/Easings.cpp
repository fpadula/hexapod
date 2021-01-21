#include "Easings.h"

float Easings::linear(float time, float start, float change, float duration){
    return (change / duration)*time + start;
}

float Easings::expo(float time, float start, float change, float duration){
    time /= duration * 0.5;

    if (time < 1) 
    {
        return change * 0.5 * pow(2, 10 * (time - 1)) + start;
    }

    time -= 1;
    return change * 0.5 * (-pow(2, -10 * time) + 2) + start;    
}
float Easings::bounce_out(float time, float start, float change, float duration){
    time /= duration;

    if (time < (1 / 2.75))
    {
        return change * (7.5625 * time * time) + start;
    }
    else
    if (time < (2 / 2.75))
    {
        time -= (1.5 / 2.75);
        return change * (7.5625 * time * time + 0.75) + start;
    }
    else
    if (time < (2.5 / 2.75))
    {
        time -= (2.25 / 2.75);
        return change * (7.5625 * time * time + 0.9375) + start;
    }
    else
    {
        time -= ( 2.625 / 2.75 );
        return change * (7.5625 * time * time + 0.984375) + start;
    } 
}
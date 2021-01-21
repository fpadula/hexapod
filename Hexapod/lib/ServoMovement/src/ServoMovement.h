#ifndef SERVOMOVEMENT_H
#define SERVOMOVEMENT_H

#include <Arduino.h>
// #include <Servo.h>
#include "Easings.h"
#include <list>
#include <Servo.h>

enum easing_type{
    linear,    
};

class ServoMovement{
    private:
        enum easing_type easing_type;
        float t, start, change, duration, min, max;
        float (*f)(float, float, float, float);
        bool loop, mirrored, finished;
        std::list<Servo *> controlled_servos;

    public:
        // ServoMovement(const ServoMovement &);
        ServoMovement(float, float, float);
        ServoMovement(float, float, float, float(*)(float, float, float, float));
        ServoMovement(float, float, float, bool);
        ServoMovement(float, float, float, bool, float(*)(float, float, float, float));
        bool step(float);
        void add_servo(Servo *);
        void reset();
        void invert();
        bool is_finished();
};

#endif
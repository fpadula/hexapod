#include "ServoMovement.h"

// ServoMovement::ServoMovement(const ServoMovement &obj){
//     this->start = obj.start;
//     this->change = obj.change;
//     this->duration = obj.duration;
//     this->t = obj.t;    
//     this->loop = obj.loop;
//     this->f = obj.f;
//     this->mirrored = obj.mirrored;
//     this->min = obj.min;
//     this->max = obj.max;    
// }

ServoMovement::ServoMovement(float start, float change, float duration){    
    this->start = start;
    this->change = change;
    this->duration = duration;
    this->t = 0;    
    this->loop = false;
    this->f = &Easings::linear;
    this->mirrored = false;
    this->finished = false;
    this->min = 0;
    this->max = 180;
    this->controlled_servos = std::list<Servo *>();
}

ServoMovement::ServoMovement(float start, float change, float duration, float (*func)(float, float, float, float)){
    this->start = start;
    this->change = change;
    this->duration = duration;
    this->t = 0;    
    this->loop = false;
    this->f = func;
    this->mirrored = false;
    this->finished = false;
    this->min = 0;
    this->max = 180;
    this->controlled_servos = std::list<Servo *>();
}

ServoMovement::ServoMovement(float start, float change, float duration, bool mirrored) : ServoMovement(start, change, duration){
    this->mirrored = mirrored;         
}
ServoMovement::ServoMovement(float start, float change, float duration, bool mirrored, float (*func)(float, float, float, float)): ServoMovement(start, change, duration, func){
    this->mirrored = mirrored;    
}

bool ServoMovement::is_finished(){return this->finished;}

void ServoMovement::add_servo(Servo *s){
    this->controlled_servos.push_back(s);
}

void ServoMovement::reset(){this->t = 0;}
void ServoMovement::invert(){
    this->start += this->change;
    this->change *= -1;
}

bool ServoMovement::step(float dt){
    float value;  
    if(this->t == this->duration){
        if(loop){
            this->invert();
            this->reset();
        }
        else{
            this->finished = true;
            return false;
        }
    }
    else{
        this->t += dt;
    }
    if(this->t >= this->duration){
        this->t = this->duration;
    }    
    value = this->f(this->t, this->start, this->change ,this->duration); 
    if(this->mirrored)
        value = map(value, this->min, this->max, this->max, this->min);
    for (std::list<Servo *>::iterator it=this->controlled_servos.begin(); it != this->controlled_servos.end(); ++it)
        (*it)->write((int)value);
    return true;
}
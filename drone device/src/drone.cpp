#include "drone.h"

void Drone::init()
{
    pinMode(rotor1, OUTPUT);
    analogWrite(rotor1, 0);
}

void Drone::setRotorSpeed(int rotor, int speed)
{
    int pin = Drone::getPinOfRotor(rotor);
    if(pin != 0){
       // std::cout << "pin " << pin << "!" << std::endl;
     analogWrite(pin, speed);
    }
    
    //std::cout << "rotor speed set to " << speed << "!" << std::endl;
}

int Drone::getPinOfRotor(int index)
{
    if(index == 0)
        return rotor1;
    return 0;
}
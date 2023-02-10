
#include <Arduino.h>
#include "Constants.h"
#include <iostream>

class Drone 
{
    public: 
        static void init();
        static void setRotorSpeed(int rotor, int speed);
        static int getPinOfRotor(int index);
    
};
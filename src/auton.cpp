#include "include.hpp"
#include <ctime>

void teamwork(){
    resetMotorPos();
    turn1d(-25, 50);
    move1d(200, 50, -25);
    turn1d(0, 50);
    move1d(100, 50, 0);

    //turn1d(90);
}

void skills(){
    
    resetMotorPos();
    turn1d(-20);
    move1d(100, 80, -20);
    delay(500);
    setDriveSpdWTime(30, 0, 500);

    printDouble(1);
    setDriveSpdWTime(200, -80, -20);
    turn1d(180);
    move1d(1000, 80, 180);
}
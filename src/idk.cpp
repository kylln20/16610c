#include "main.h"
using namespace pros;

//setting motor variables
//Motor name(portNumber, reverse=true/false);
Motor leftF(10, true);
Motor leftPTO(9);
Motor leftB(8, true);
Motor rightF(1);
Motor rightPTO(2, true);
Motor rightB(3);
Motor cata(7);
ADIDigitalIn armLimit(char('a'), false);

Controller master(E_CONTROLLER_MASTER);



bool PTOOnMotor = false;

void initialize() {
    // holdAll();
    opcontrol();
}

void holdAll(){
    leftF.set_brake_mode(MOTOR_BRAKE_HOLD);
    leftPTO.set_brake_mode(MOTOR_BRAKE_HOLD);
    leftB.set_brake_mode(MOTOR_BRAKE_HOLD);
    rightF.set_brake_mode(MOTOR_BRAKE_HOLD);
    rightPTO.set_brake_mode(MOTOR_BRAKE_HOLD);
    rightB.set_brake_mode(MOTOR_BRAKE_HOLD);
    cata.set_brake_mode(MOTOR_BRAKE_HOLD);
}

// set left right motor speeds
void setDriveSpd(int spd, int turn){
    if (PTOOnMotor) {
        leftPTO.move(spd + turn);
        rightPTO.move(spd - turn);
    }
    leftF.move(spd + turn);
    leftB.move(spd + turn);
    rightF.move(spd - turn);
    rightB.move(spd - turn);
}

// timed drive spd
void setDriveSpdWTime(int spd, int turn, int time){
    setDriveSpd(spd, turn);
    delay(time);
    setDriveSpd(0, 0);
}

void raiseArm() {
    while (armLimit.get_value() != 1) {
        leftPTO.move(50);
        rightPTO.move(50);
    }
    leftPTO.move(0);
    rightPTO.move(0);
}

void shiftTPO () {

}

void opcontrol() {
    long long time = 0;
    int flag = 0;
    while(true) {
        //Getting speed for drivetrain
        setDriveSpd(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)); 

        //Controlling Catapult Motor
        if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){};

        delay(50);
    }
}
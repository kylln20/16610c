#include "include.hpp"

bool lWingToggle = false;
bool rWingToggle = false;
bool blockToggle = false;

void inT(){
    intake.move(127);
}
void outT(){
    intake.move(-127);
}
void stopT(){
    intake.move(0);
}

void leftwing(){    
    lWingToggle = !lWingToggle;
    if(lWingToggle)
        wing1.set_value(true);
    else
        wing1.set_value(false);
}

void rightwing(){ 
    rWingToggle = !rWingToggle;
    if(rWingToggle)
        wing2.set_value(true);
    else
        wing2.set_value(false);
}

void setblocker(){
    blockToggle = !blockToggle;
    blocker.set_value(blockToggle);
}

/*
void pto(int on){
    ptoL.set_value(on);
    ptoR.set_value(on);
}

void blocker(int on){
    blockerL.set_value(on);
    blockerR.set_value(on);
}

void wings(int on){
    wingsL.set_value(on);
    wingsR.set_value(on);
}*/

/*void spinTake(double ticks){
    intake.tare_position();
    int origDif = intake.get_position() - ticks;
    intake.move(sign(ticks) * 127);
    while (sign(intake.get_position() - ticks) == sign(origDif)) {
        delay(2);
    }
    intake.move(0);
}*/
#include "include.hpp"
//setting motor variables
//Motor name(portNumber, reverse=true/false);

int intakeSpd = 0;
int armSpd = 0;

void driveInit(){
  holdAll();
}

void normalDrive() {
    while(true) {
      //Getting speed for drivetrain
      setDriveSpd(JOY_LY, JOY_RX);

      if(master.GET_NEW_R2){
        if(intakeSpd == 0 || intakeSpd == -127) intakeSpd = 127;
        else intakeSpd = 0;
      }
      else if(master.GET_NEW_L2){
        if(intakeSpd == 0 || intakeSpd == 127) intakeSpd = -127;
        else intakeSpd = 0;
      }
      intake.move(intakeSpd);

      if(master.GET_NEW_R1){
        setleftwing();
      }

      if(master.GET_NEW_L1){
        setrightwing();
      }

      if(master.GET_NEW_UP){
        setblocker();
      }
      delay(50);
    }
}

void otherControls(){
  while(true){
    // loading position
    if(master.GET_Y){
      cata.move(-127);
    }
    else{
      cata.move(0);
    }

    if(master.GET_NEW_X){
      moveArm();
    }
    delay(50);
  }
}




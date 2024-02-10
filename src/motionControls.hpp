#ifndef MOTIONCONTROL_H
#define MOTIONCONTROL_H

void resetMotorPos();

void holdAll();

void setDriveSpd(int spd, int turn = 0);
void moveArm();
void setArmSpd(int spd);
void setDriveSpdWTime(int spd, int turn, int time);

//void turn(double targetAngle);
//void turnTo(double targetAngle, double turnSpd = 45);
//void driveTo(int x, int y, int maxspd, bool forward = true, double accelRatio = 0.333, double turnSpd = 45);
//void driveToNoTurn(int x, int y, int maxSpd, bool forward = true, double accelRatio = 0.333);
//void forward(int target, int targetHeading, int maxSpd);

//void arcTo(int x, int y, double targetAngle);

void turn1d(double targetAngle, double turnSpd = 70);
void move1d(int dist, int spd, int targetHeading);

extern bool ptoOnArm;
#endif //MOTIONCONTROL_H
#ifndef UTIL_H
#define UTIL_H

#include "include.hpp"

#define printon
#ifdef printon
#define log(x) std::cout << #x << ": " << x << " "
#define logn(x) std::cout << "\n"
#define printDouble(x) printf("%s: %f  ",#x,(double)(x))
#define printN(x) printf("\n")
#else
#define log(x) 
#define logn(x) 
#define printDouble(x) 
#define printN(x) 
#endif //printon

#define C_PI 3.14159

#define C_RDRIVE 7
#define C_LDRIVE 7
#define LR_DIST 13.25
#define WHEEL_RAD_H 1.25
#define WHEEL_RAD_V 1.75

//#define RED_HUE 70

#define JOY_LY master.get_analog(ANALOG_LEFT_Y)
#define JOY_LX master.get_analog(ANALOG_LEFT_X)
#define JOY_RY master.get_analog(ANALOG_RIGHT_Y)
#define JOY_RX master.get_analog(ANALOG_RIGHT_X)

#define GET_UP get_digital(DIGITAL_UP)
#define GET_DOWN get_digital(DIGITAL_DOWN)
#define GET_LEFT get_digital(DIGITAL_LEFT)
#define GET_RIGHT get_digital(DIGITAL_RIGHT)
#define GET_X get_digital(DIGITAL_X)
#define GET_B get_digital(DIGITAL_B)
#define GET_Y get_digital(DIGITAL_X)
#define GET_A get_digital(DIGITAL_B)
#define GET_L1 get_digital(DIGITAL_L1)
#define GET_L2 get_digital(DIGITAL_L2)
#define GET_R1 get_digital(DIGITAL_R1)
#define GET_R2 get_digital(DIGITAL_R2)

#define GET_NEW_UP get_digital_new_press(DIGITAL_UP)
#define GET_NEW_DOWN get_digital_new_press(DIGITAL_DOWN)
#define GET_NEW_LEFT get_digital_new_press(DIGITAL_LEFT)
#define GET_NEW_RIGHT get_digital_new_press(DIGITAL_RIGHT)
#define GET_NEW_X get_digital_new_press(DIGITAL_X)
#define GET_NEW_B get_digital_new_press(DIGITAL_B)
#define GET_NEW_Y get_digital_new_press(DIGITAL_Y)
#define GET_NEW_A get_digital_new_press(DIGITAL_A)
#define GET_NEW_R1 get_digital_new_press(DIGITAL_R1)
#define GET_NEW_R2 get_digital_new_press(DIGITAL_R2)
#define GET_NEW_L1 get_digital_new_press(DIGITAL_L1)
#define GET_NEW_L2 get_digital_new_press(DIGITAL_L2)

double toRad(double deg);
double toDeg(double rad);
double goodRange(double rad);
double goodRangeDeg(double deg);
double equivalentAng(double deg);

double toDist(int rotations, double wheelRad);

double dist(int x1, int y1, int x2, int y2);

double getAngle(double x, double y);

int sign(double num);

double min(double n1, double n2);

#endif //UTIL_H
#ifndef PORTDEFS_H
#define PORTDEFS_H

#include "include.hpp"
using namespace pros;

#define LIMIT_SWITCH 1

extern Motor leftF;
extern Motor leftPTO;
extern Motor leftB;
extern Motor rightF;
extern Motor rightPTO;
extern Motor rightB;

extern Motor intake;
extern Motor cata;

extern ADIDigitalOut wing1;
extern ADIDigitalOut wing2;

extern ADIDigitalOut blocker;
extern ADIDigitalOut pto;

extern ADIDigitalIn limit;

extern Imu inert;
extern Imu inert2;

extern Controller master;
extern Controller partner;

#endif //PORTDEFS_H
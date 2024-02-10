#include "include.hpp"

// convert degrees to radians
double toRad(double deg){
    return deg / 180 * C_PI;
}
// convert radians to degrees
double toDeg(double rad){
    return rad / C_PI * 180;
}

// convert radian angle to -pi ~ pi range
double goodRange(double rad){
	if (rad < -C_PI)		rad = rad + 2 * C_PI;
	else if (rad > C_PI)	rad = rad - 2 * C_PI;
	return rad;
}

double goodRangeDeg(double deg){
	while (deg < -180){
		deg = deg + 360;
	}		
	while(deg > 180){
		deg = deg - 360;
	}
	return deg;
}

double equivalentAng(double deg){
	if (deg < 0) return 360 + deg;
	else		 return -360 + deg;
}

// wheel degree to distance travelled
double toDist(int rotations, double wheelRad){
    return rotations * wheelRad * C_PI / 180;
}

// find distance between two points
double dist(int x1, int y1, int x2, int y2){
	int xerr = x2 - x1;
	int yerr = y2 - y1;
	return sqrt(xerr * xerr + yerr * yerr);
}

// find angle between 0 and given point
double getAngle(double x, double y){
	return -atan2(x, y);
}

/** 
 * @return 1 if num is positive, -1 if num is negative or zero.
 **/
int sign(double num)
{
	if (num > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

// returns min of two numbers
double min(double n1, double n2){
	return n1 > n2? n2 : n1;
}
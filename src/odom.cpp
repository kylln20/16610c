#include "include.hpp"
using namespace pros;

double G_X = 0;
double G_Y = 0;
double G_angle = 0;
double angleError;
double angleError2;

const int recordSize = 100000;
double G_XRecord[recordSize];
double G_YRecord[recordSize];
double hradiusRecord[recordSize];
double vradiusRecord[recordSize];
int G_Index;

void setCheckPoint(double x, double y, double angle){
    G_X = x;
    G_Y = y;
    G_angle = angle;
    delay(10);
}

void writeData(double arr[], double val){
    if(G_Index < recordSize)
        arr[G_Index] = val;
}

void printData(){
    int maxInd = G_Index;
    for(int i = 0; i <= maxInd; i++){
        if(i >= recordSize)
            break;
        printf("%d G_X:%f G_Y:%f hradius:%f vradius:%f\n", i, G_XRecord[i], G_YRecord[i], hradiusRecord[i], vradiusRecord[i]);
        delay(50);
    }
    G_Index = 0;
}

double getRotation(){
    return inert.get_rotation() * -1 - angleError;
}

double getRotation2(){
    return inert2.get_rotation() * -1 - angleError2;
}

double lastAngle1 = 0;
double lastAngle2 = 0;
// G_angle reading in degrees
double readInert(){
    /*
    double curReading = getRotation();
    double angleChange = curReading - lastAngle;
    lastAngle = curReading;
    if(fabs(angleChange) >= 0.01)
        G_angle = G_angle + angleChange;
    return G_angle;*/

    double curReading1 = getRotation();
    double curReading2 = getRotation2();
    double angleChange = ((curReading1 - lastAngle1) + (curReading2 - lastAngle2))/2;
    lastAngle1 = curReading1;
    lastAngle2 = curReading2;
    if(fabs(angleChange) >= 0.01)
        G_angle = G_angle + angleChange;
    return G_angle;
}

double calcAngle(double LChange, double RChange){
    if(LChange == RChange)
        return G_angle;

    double r = LR_DIST / (RChange - LChange);
    if(RChange > LChange)
        G_angle = G_angle + toDeg(LChange / r);
    else  
        G_angle = G_angle + toDeg(RChange / r);

    return G_angle;
}

// positional tracking
void tracking(){
    angleError = getRotation();
    angleError2 = getRotation2();

    // positive y direction = positive for HW, positive x direction = positive for VW
    const double VW = 0; 
    const double HW = 2;

    double lastAngle = 0;
    double newAngle;
    double angleChange;

    double lastV, lastH = 0;
    double newV, newH;
    double VChange, HChange;

    double Vchord, Hchord;

    double xChange, yChange;

    G_Index = 0;
    while(true){
        // read new positional vals, find change from old vals
        newV = toDist(vt.get_value(), WHEEL_RAD_V);
        newH = toDist(ht.get_value(), WHEEL_RAD_H);

        VChange = newV - lastV;
        HChange = newH - lastH;

        newAngle = inert.get_rotation();
        angleChange = newAngle - lastAngle;


		if (angleChange == 0){ // in case of no G_angle change, chord length = arc length
			Hchord = HChange;
			Vchord = VChange;
		}
		else{
			// calculate displacement detected by vertical wheel
			double vradius = VChange / angleChange + VW;
			Vchord = 2 * sin(angleChange / 2) * vradius;

			// calculate displacement detected by horizontal wheel
			double hradius = HChange / angleChange + HW;
			Hchord = 2 * sin(angleChange / 2) * hradius;

            //printDouble(hradius);
            //printDouble(vradius);

            writeData(hradiusRecord, hradius);
            writeData(vradiusRecord, vradius);
		}

		// combine values and rotate by average of inital and final angles
		double angleOffset = (lastAngle + angleChange / 2);
		yChange = sin(angleOffset) * Hchord + cos(angleOffset) * Vchord;
		xChange = cos(angleOffset) * Hchord - sin(angleOffset) * Vchord;

        // update xg yg
        G_X += xChange;
        G_Y += yChange;

        // update positional vals
        lastAngle = newAngle;
        lastV = newV;
        lastH = newH;

        printDouble(G_X);
        printDouble(G_Y);
        printN();

        delay(40);
        G_Index ++;
    }
}
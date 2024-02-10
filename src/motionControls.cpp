#include "include.hpp"
#include <iomanip>
#include <ctime>
bool ptoOnArm = false;

void resetMotorPos(){
    leftB.tare_position();
    rightB.tare_position();
}


double encoderReading(){
    return -(rightB.get_position()+leftB.get_position());
}

// hold all motors
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
    if (!ptoOnArm) {
        leftPTO.move(spd + turn);
        rightPTO.move(spd - turn);
    }
    leftF.move(spd + turn);
    leftB.move(spd + turn);
    rightF.move(spd - turn);
    rightB.move(spd - turn);
}

/***auton functions **/


// timed drive spd
void setDriveSpdWTime(int spd, int turn, int time){
    setDriveSpd(spd, turn);
    delay(time);
    setDriveSpd(0, 0);
}
/*
// setDriveSpd but keep speeds under 127 while preserving l:r speed ratio
void keepRatios(double spd, double turn){
    double ls = spd - turn;
    double rs = spd + turn;
    if (fabs(ls) > 127){
        rs = fabs(127 * (rs / ls)) * sign(rs);
        ls = 127 * sign(ls);
    }
    if (fabs(rs) > 127){
        ls = fabs(127 * (ls / rs)) * sign(ls);
        rs = 127 * sign(rs);
    }
    setDriveSpd(ls, rs);
}


/*
NASTY NASTY 1D CONTROLS
*/

void turn1d(double targetAngle, double turnSpd){
    double initError = goodRangeDeg(targetAngle - inert.get_rotation());
    int spd;
    int p = 1;
    int deccelAngle = 90;
    while(sign(initError) * goodRangeDeg(targetAngle - inert.get_rotation()) > 1 && fabs(goodRangeDeg(targetAngle - inert.get_rotation())) > 3){
        if (abs(goodRangeDeg(targetAngle - inert.get_rotation())/deccelAngle) >= 1){
            spd = 90 * sign(initError);
        }
        else{
            spd = (int)(goodRangeDeg(targetAngle - inert.get_rotation())/deccelAngle * turnSpd);
        }

        if (abs(spd) < 35){
            spd = 35 * sign(initError);
        }
        setDriveSpd(0, spd);
        delay(20);
    }
    setDriveSpd(0, 0);
}

int moveSpeed1d(double pos, int target, int maxSpd, int accelDist = 50)
{
    double travelled = pos;
    double error = target-pos;

	double pwr = 0;
	int minSpeed = 30;
    int decelDist = 500;
    
	// Increase speed when travelled is < 1/4 of the whole distance
	if (fabs(travelled) < min(target/2, accelDist))
	{
		pwr = maxSpd * (fabs(travelled) / fabs(error)) * (travelled/accelDist);
        
	}
    // Decrease speed when error is < 2/5 of the whole distance
	else if (fabs(error) < min(target/2, decelDist))
	{
		pwr = maxSpd * (fabs(error) / fabs(travelled)) * (travelled/decelDist);
	}
	else
	{
		pwr = maxSpd;
	}

	// Ensure that the bot is never too slow or not moving
	if (fabs(pwr) < minSpeed)
	{
		pwr = minSpeed;
	}
	return (int)pwr;
}

/**
 * @brief Move straight in some direction, 1d coordinates.
 * 
 * @param dist 
 * @param spd 
 * @param targetHeading 
 */

void move1d(int dist, int spd, int targetHeading){
    printDouble(encoderReading()); printN();
    double pos0 = encoderReading();
    double deltaPos, driveSpd, correction;
    while(abs(encoderReading()-pos0) < abs(dist)){
        deltaPos = fabs(encoderReading()-pos0);
        driveSpd = moveSpeed1d(deltaPos, dist, abs(spd));
        correction = -(inert.get_rotation()-targetHeading)*4;

        printDouble(deltaPos);
        printDouble(driveSpd);
        printDouble(correction);
        printN();

        setDriveSpd(driveSpd*sign(spd), correction);
        delay(20);
    }

    printDouble(1);
    setDriveSpd(0, 0);
}

void setArmSpd(int spd){
    if(ptoOnArm){
        leftPTO.move(spd);
        rightPTO.move(spd);
    }
}

void moveArm() {
    ptoOnArm = !ptoOnArm;
    delay(100);

    if(ptoOnArm){
        pto.set_value(ptoOnArm);
        setArmSpd(127);
        while(!limit.get_value())
            delay(50);
        armSpd = 50;
    }
    else{
        setArmSpd(-127);
        delay(500);
        armSpd = 0;
        pto.set_value(ptoOnArm);
    }
    
    setArmSpd(armSpd);
}

/*
// arc part of arcTo
void arcPart(int x0, int y0, int xt, int yt, double targetAngle,
             double centerx, double centery, double radius){
    double initAngle = G_angle;

    // calculate left right speed ratio
    double l;
    double r;
    if (targetAngle < 0){
        l = radius + C_LDRIVE;
        r = radius - C_RDRIVE;
    }
    else{
        l = radius - C_LDRIVE;
        r = radius + C_RDRIVE;
    }

    int spd, ls, rs;
    int correction;
    int c = 2;
    // while desired angle has not been reached
    while(fabs(toRad(G_angle - initAngle)) < fabs(targetAngle)){
        printDouble(G_X);
        printDouble(G_Y);

        // calculate left right wheel speeds
        spd = moveSpeed(x0, y0, xt, yt, 80, 0.333);
        ls = (double) spd * l / r;
        rs = spd;

        // correct by distance from center
        correction = c * (radius - dist(G_X, G_Y, centerx, centery)) * sign(targetAngle);

        printDouble(spd);
        printDouble(ls);
        printDouble(rs);
        printDouble(correction);
        printN();

        keepRatios(ls + correction, rs - correction);
        delay(50);
    }
}

// straight part of arcTo
void straightPart(int xt, int yt, int startx, int starty, int endx, int endy){
    double x0 = G_X, y0 = G_Y;

    double errorDist = dist(G_X, G_Y, xt, yt);
    double travelledDist = dist(G_X, G_Y, x0, y0);

    double angleError;
    double correction;

    int spd;

    int stopDist = dist(G_X, G_Y, xt, yt);
    double k = 2;
    while(travelledDist < stopDist){
        // calculate distance from target, distance already travelled
        errorDist = dist(G_X, G_Y, xt, yt);
        travelledDist = dist(G_X, G_Y, x0, y0);

        // calculate expected local x error
        angleError = getAngle(xt - G_X, yt - G_Y) - toRad(G_angle);
        correction = -sin(angleError) * errorDist * k;

        // calculate wanted move speed
        spd = moveSpeed(startx, starty, endx, endy, 127, 0.333);

        // move
        printDouble(correction); 
        printDouble(toDeg(angleError));
        printDouble(G_angle);
        printDouble(G_X);
        printDouble(G_Y);
        printDouble(errorDist);
        printN();

        keepRatios(spd + correction, spd - correction);
        delay(50);
    }
}

// move bot from current position to a target position + angle with an arc
void arcTo(int x, int y, double targetAngle){
    printN();

    double x0 = G_X;
    double y0 = G_Y;
    double angle0 = G_angle;

    // convert to local coords
    double xt = x - G_X;
    double yt = y - G_Y;

    xt = cos(toRad(angle0)) * xt - sin(toRad(angle0)) * yt;
    yt = sin(toRad(angle0)) * xt + cos(toRad(angle0)) * yt;

    targetAngle = toRad(targetAngle - angle0);

    // find circle
    double yi = yt + xt / tan(targetAngle); // y intersect if (xt, yt) is extended in direction opposite from thetat

    double originDist = yi;
    double targetDist = dist(0, yi, xt, yt);
    double tanDist = min(originDist, targetDist);

    double radius = fabs(tanDist / tan(targetAngle / 2));
    double centerx = sign(targetAngle) * -radius;
    double centery = yi - tanDist;

    printDouble(radius);
    printDouble(centerx);
    printDouble(centery);
    printN();

    // turn --> go in a straight line
    double firstTargetx;
    double firstTargety;
    if (tanDist == originDist){
        firstTargetx = - tanDist * sin(targetAngle);
        firstTargety = tanDist + tanDist * cos(targetAngle);
        printf("arc first: ");
        printDouble(firstTargetx);
        printDouble(firstTargety);
        printN();
        printN();
        
        arcPart(x0, y0, xt, yt, targetAngle,
                centerx, centery, radius);
        straightPart(xt, yt, x0, y0, xt, yt);
    }
    // go in a straight line --> turn
    else{
        firstTargetx = 0;
        firstTargety = (yi - tanDist) * 0.9;
        printf("straight first: ");
        printDouble(firstTargetx);
        printDouble(firstTargety);
        printN();
        printN();

        straightPart(firstTargetx, firstTargety, x0, y0, xt, yt);
        arcPart(x0, y0, xt, yt, targetAngle,
                centerx, centery, radius);
    }
    setDriveSpd(0, 0);
}
*/
/*
bool moveArm = false;
int armSpd = 0;
int armTime = 0;
// task controls arm movement + claws
void armControl(){
    while(true){
        if(moveArm){
            arm.move(armSpd);
            delay(armTime);
            arm.move(0);
            moveArm = false;
        }
        delay(50);
    }
}
*/
/*
bool f = false;
bool fState = false;
bool b = false;
bool bState = false;
bool s = false;
bool sState = false;
void pistons(){
    while(true){
        if(f){
            fState = !fState;
            frontClaw.set_value(fState);
            f = false;
        }
        if(b){
            bState = !bState;
            backClaw.set_value(bState);
            b = false;
        }
        if(s){
            sState = !sState;
            scam.set_value(bState);
            s = false;
        }
        delay(50);
    }
}
*/
/*
// sets target speed and time for arm
void lift(int spd, int time){
    armSpd = spd;
    armTime = time;
    moveArm = true;
}

// non-parallel running lift
void seqLift(int spd, int time){
    while(moveArm){
        delay(50);
    }
    arm.move(spd);
    delay(time);
    arm.move(0);
}*/
/*
void fGrab(){
    frontClaw.set_value(false);
}
void fDrop(){
    frontClaw.set_value(true);
}
void bGrab(){
    backClaw.set_value(false);
}
void bDrop(){
    backClaw.set_value(true);
}
*/
/*
void fnoLag(){
    f = true;
}
void bnoLag(){
    b = true;
}
void scamGo(){
    s = true;
}
*/
#ifndef OTHERCONTROL_H
#define OTHERCONTROL_H

//void rollToColour(char col, int driveSpd, int rollSpd);

extern bool lWingToggle;
extern bool rWingToggle;
extern bool blockToggle;

void inT();
void outT();
void stopT();

void setleftwing();
void setrightwing();
void setblocker();

//void pto(int on);
//void blocker(int on);
//void wings(int on);

//void spinTake(double ticks);

#endif //OTHERCONTROL_H
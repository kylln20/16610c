#ifndef ODOM_H
#define ODOM_H

extern double G_X;
extern double G_Y;
extern double G_angle;

void setCheckPoint(double x, double y, double angle);
void tracking();
void printData();

#endif //ODOM_H
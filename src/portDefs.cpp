#include "include.hpp"
using namespace pros;

Motor leftF(10, true);
Motor leftPTO(9);
Motor leftB(8, true);
Motor rightF(1);
Motor rightPTO(2, true);
Motor rightB(3);

Motor intake(5);
Motor cata(7);

ADIDigitalOut wing1('G');
ADIDigitalOut wing2('H');

ADIDigitalOut blocker('F');
ADIDigitalOut pto('E');

ADIDigitalIn limit('A');

Imu inert(12);
Imu inert2(19);

Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);
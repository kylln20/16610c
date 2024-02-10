#include "include.hpp"
using namespace pros;

bool inAuton = false;

void initialize() {
	holdAll();
	inert.reset();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	teamwork();
	//skills();
}

void opcontrol() {
	
}
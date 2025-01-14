#include "main.h"
#include "variables.h"
#include "replay.h"

#define DIGITAL_SENSOR_PORT_1 'G'
#define DIGITAL_SENSOR_PORT_2 'H'


pros::Motor left_front(18);
pros::Motor right_front(1);
pros::Motor left_back(20);
pros::Motor left_mid(19);
pros::Motor right_mid(2);
pros::Motor right_back(3);
pros::Motor roller(11);
pros::Motor lift(12);

pros::adi::DigitalOut piston_1 (DIGITAL_SENSOR_PORT_1);
pros::adi::DigitalOut piston_2 (DIGITAL_SENSOR_PORT_2);

bool drivingDirection = false; // true makes it inverted
bool pneum = false;

bool prevDrivingDirectionButton = false;
bool prevPneumButton = false;

bool lift_on = false;
bool lift_reverse = false;
bool prev_lift_state = false;
bool roller_on = false;
bool roller_reverse = false;
bool prev_roller_state = false;

//1.0 is full speed
float lift_speed_mult = 0.98;
float roller_speed_mult = 0.98;

string fileName="/usd/a_team_auton_file.txt";
string imageName="/usd/img.ppm";

void init() {
	piston_1.set_value(false);
	piston_2.set_value(false);
}

void auton() {
	
}

void drive(auto master) {
	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
		if (!prevDrivingDirectionButton) {
			drivingDirection = !drivingDirection;
		}
		prevDrivingDirectionButton = true;
	} else {
		prevDrivingDirectionButton = false;
	}

	int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	left_front.move_voltage(((right * !drivingDirection) + (-left * drivingDirection)) * MOVE_VOLT);
	right_front.move_voltage(((left * !drivingDirection) + (-right * drivingDirection)) * -MOVE_VOLT);
	left_back.move_voltage(((right * !drivingDirection) + (-left * drivingDirection)) * MOVE_VOLT);
	left_mid.move_voltage(((right * !drivingDirection) + (-left * drivingDirection)) * MOVE_VOLT);
	right_back.move_voltage(((left * !drivingDirection) + (-right * drivingDirection)) * -MOVE_VOLT);
	right_mid.move_voltage(((left * !drivingDirection) + (-right * drivingDirection)) * -MOVE_VOLT);

	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
	{
		if (!prevPneumButton) {
			pneum = !pneum;
			piston_1.set_value(pneum);
			piston_2.set_value(pneum);
		}
		prevPneumButton = true;
	} else {
		prevPneumButton = false;
	}

	roller.move_voltage(0);
	lift.move_voltage(0);

	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
		if (!prev_roller_state) {
			roller_on = !roller_on;
		}
		prev_roller_state = true;
	} else {
		prev_roller_state = false;
	}

	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		if (!prev_lift_state) {
			lift_on = !lift_on;
		}
		prev_lift_state = true;
	} else {
		prev_lift_state = false;
	}

	if (roller_on && !roller_reverse) {
		//Roller's motor is half-sized, so it gets half the voltage
		roller.move_voltage(MOVE_VOLT * 0.6 * 127.0 * roller_speed_mult);
	}
	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
		//Roller's motor is half-sized, so it gets half the voltage
		roller.move_voltage(-MOVE_VOLT * 0.6 * 127.0 * roller_speed_mult);
		roller_reverse = true;
	} else {
		roller_reverse = false;
	}

	if (lift_on && !lift_reverse) {
		//Lift's motor is half-sized, so it gets half the voltage
		lift.move_voltage(-MOVE_VOLT * 0.75 * 127.0 * lift_speed_mult);
	}
	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		//Lift's motor is half-sized, so it gets half the voltage
		lift.move_voltage(MOVE_VOLT * 0.75 * 127.0 * lift_speed_mult);
		lift_reverse = true;
	} else {
		lift_reverse = false;
	}
}
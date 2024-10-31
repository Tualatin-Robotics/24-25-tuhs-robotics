#include "main.h"
#include "variables.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(19);
pros::Motor right_front(20);
pros::Motor left_back(18);
pros::Motor right_back(17);

void init() {}

void auton() {
	left_front.move_voltage(127.0 * MOVE_VOLT);
	right_front.move_voltage(127.0 * -MOVE_VOLT);

	pros::delay(2000);

	left_front.move_voltage(0);
	right_front.move_voltage(0);

	pros::delay(2000);

	left_front.move_voltage(127.0 * MOVE_VOLT);

	pros::delay(500);

	left_front.move_voltage(0);
}

void drive() {
	int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	bool b = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);

	left_front.move_voltage(left * MOVE_VOLT * 0.5 *!b);
	right_front.move_voltage(right * -MOVE_VOLT * 0.5*!b);
}
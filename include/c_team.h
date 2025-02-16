// Paths to important files:
#include "main.h"
#include "variables.h"

// Vital information for C Team:
string fileName="/usd/c_team_auton_file.txt";//change this to an auton file path (.txt) on the SD card
string imageName="/usd/img.ppm";//change this to an image file path (.ppm) on the SD card

// Motor definitions:
pros::Motor left_front(19);
pros::Motor right_front(20);
pros::Motor left_back(18);
pros::Motor right_back(17);

void init() { //anything that needs to be initialized after the code compiles
	left_front.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_front.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	left_back.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	right_back.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

}

void auton() { //anything that needs to be called when the auton period starts
	left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

}

void drive(auto master) { //whatever the hell the bot is supposed to do when you press the little buttons on the controller
	int leftY = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int rightY = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	left_back.move_voltage(leftY * MOVE_VOLT);
	right_back.move_voltage(rightY * -MOVE_VOLT);
	left_front.move_voltage(leftY * MOVE_VOLT);
	right_front.move_voltage(rightY * -MOVE_VOLT);

	lift.move(0);

	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
		lift.move(127.0 * 0.5);
	}
	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
		lift.move(-127.0 * 0.5);
	}
}
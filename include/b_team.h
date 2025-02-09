// Paths to important files:
#include "main.h"
#include "variables.h"

// Vital information for B Team:
string fileName = "/usd/b_team_auton_file.txt";//change this to an auton file path (.txt) on the SD card
string imageName = "/usd/img.ppm";//change this to an image file path (.ppm) on the SD card

// Motor definitions:
pros::Motor left_front(20);
pros::Motor right_front(19);
pros::Motor left_back(18);
pros::Motor right_back(17);
pros::Motor lift(10);
// new ------------------------------------------------------ 
pros::Motor claw(15);

void init() { //anything that needs to be initialized after the code compiless
	lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

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
	int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	int triggle_up = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
	int triggle_down = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);;
// new ------------------------------------------------------ 
	int up = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
	int down = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

	left_front.move_voltage(left * MOVE_VOLT);
	right_front.move_voltage(right * -MOVE_VOLT);

	int left_trig = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
	int right_trig = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
	int left_bump = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
	int right_bump = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

lift.move_voltage(8000*(triggle_up-triggle_down)); // was: lift.move_voltage(12000*(triggle_up-triggle_down))
// new ------------------------------------------------------ 
claw.move_voltage(1200*(up-down));

}

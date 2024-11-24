#include "main.h"
#include "variables.h"
#include "replay.h"

pros::Motor left_front(19);
pros::Motor right_front(20);
pros::Motor left_back(18);
pros::Motor right_back(17);

pros::Motor arm(16);

void init() {
	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

string fileName="/usd/b_team_auton_file.txt";

void auton() {

}

void drive(auto master) {
	int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	left_front.move_voltage(left * MOVE_VOLT);
	right_front.move_voltage(right * -MOVE_VOLT);

	int left_trig = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
	int right_trig = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
	int left_bump = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
	int right_bump = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

	int trig = (left_bump*4 + left_trig*12) - (right_bump*4 + right_trig*12);

	arm.move_voltage(1000*trig);
}
#include "main.h"
#include "variables.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(19);
pros::Motor right_front(20);
pros::Motor left_back(18);
pros::Motor right_back(17);

pros::Motor arm(16);

void init() {
	arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void auton() {

}

void drive() {
	int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	left_front.move_voltage(left * MOVE_VOLT);
	right_front.move_voltage(right * -MOVE_VOLT);

	int left_trig = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
	int right_trig = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

	int trig = left_trig - right_trig;

	std::cout << "trig" << std::endl;

	arm.move_voltage(4000*trig);
}
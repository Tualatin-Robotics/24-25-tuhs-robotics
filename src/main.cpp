#include "main.h"

const float MOVE_VOLT = 12000.0 / 128.0;

void initialize() {
	
}

void autonomous() {

}

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor left_front(11);
	pros::Motor right_front(12);

	while (true) {
		int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		bool buttonPressed=master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
		int thing=1;
		if(buttonPressed) thing=-1;
		//int thing=(buttonPressed)-1:1;

		left_front.move_voltage(left * MOVE_VOLT * thing);
		right_front.move_voltage(right * -MOVE_VOLT * thing);
		


		pros::delay(20);
	}
}
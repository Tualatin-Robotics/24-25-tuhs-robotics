#include "main.h"
#include "variables.h"
#include "replay.h"

#define DIGITAL_SENSOR_PORT_1 'G'
#define DIGITAL_SENSOR_PORT_2 'H'


pros::Motor left_front(18);
pros::Motor right_front(1);
pros::Motor left_back(12);
pros::Motor left_mid(19);
pros::Motor right_mid(2);
pros::Motor right_back(3);
pros::Motor roller(11);
pros::Motor lift(9);

string fileName="/usd/test_auton_file.txt";//change this to an auton file path (.txt) on the SD card
string imageName="/usd/img.ppm";//change this to an image file path (.ppm) on the SD card

void init(){
	left_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_front.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_mid.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_mid.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	right_back.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void drive(auto master){
	int leftY=master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int rightY=master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	left_back.move_voltage(-leftY * MOVE_VOLT);
	right_back.move_voltage(-rightY * -MOVE_VOLT);
	left_front.move_voltage(-leftY * MOVE_VOLT);
	right_front.move_voltage(-rightY * -MOVE_VOLT);
	left_mid.move_voltage(-leftY * MOVE_VOLT);
	right_mid.move_voltage(-rightY * -MOVE_VOLT);
}
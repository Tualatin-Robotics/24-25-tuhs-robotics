#include "main.h"
#include "variables.h"
#include "replay.h"

pros::Motor left_front(2);
pros::Motor right_front(1);
pros::Motor left_back(4);
pros::Motor right_back(3);

string fileName="/usd/a_team_auton_file";//the program will automatically append ".txt"

void init(){

}

void auton(){
	
}

void drive(auto master) {
	int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	left_front.move_voltage(left * MOVE_VOLT);
	right_front.move_voltage(right * -MOVE_VOLT);
}
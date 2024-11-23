#include <fstream>
#include <cstring>
using namespace std;
#include "main.h"
#include "variables.h"
#include "replay.h"

pros::Motor left_front(19);
pros::Motor right_front(20);
pros::Motor left_back(18);
pros::Motor right_back(17);

string fileName="/usd/c_team_auton_file.txt";//change this to a file on the SD card

void init(){

}

void drive(auto master){
	int leftY=master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int rightY=master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	left_front.move_voltage(leftY * MOVE_VOLT);
	right_front.move_voltage(rightY * -MOVE_VOLT);
}
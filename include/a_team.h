#include "main.h"
#include "variables.h"
#include "replay.h"

#define DIGITAL_SENSOR_PORT 'A'

pros::Motor left_front(12);
pros::Motor right_front(11);
pros::Motor left_back(14);
pros::Motor right_back(13);

pros::adi::DigitalOut piston (DIGITAL_SENSOR_PORT);

bool drivingDirection = false; // true makes it inverted
bool pneum = false;

bool prevDrivingDirectionButton = false;
bool prevPneumButton = false;

bool is_recording_auton = false;

string fileName="/usd/a_team_auton_file.txt";

void init() {
	piston.set_value(false);
}

void auton() {
	
}

void drive(auto master) {
	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)
	&& master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)
	&& master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)
	&& master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
	//if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
		pros::delay(1000);
		is_recording_auton = true;
		//remove("/usd/a_team_auton_file.txt");
		theFile.open(fileName,std::ios_base::out);
		cout << "Recording!";
		//open_auton_file(fileName, true);
	}


	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
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
	right_back.move_voltage(((left * !drivingDirection) + (-right * drivingDirection)) * -MOVE_VOLT);

	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
	{
		if (!prevPneumButton) {
			pneum = !pneum;
			piston.set_value(pneum);
		}
		prevPneumButton = true;
	} else {
		prevPneumButton = false;
	}
}
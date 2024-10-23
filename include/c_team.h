#include "main.h"
#include "variables.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(19);
pros::Motor right_front(20);
pros::Motor left_back(18);
pros::Motor right_back(17);

void auton() {
	while(true){
		doStuff();//everything is false right now
		pros::delay(2000);//2 seconds
		//this will later be mathematically aligned with the speed at which the controller input is recorded
	}
}

void drive() {
	doStuff(
		master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X),
		master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
		master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),
		master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_A),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_B),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_X),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_Y),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_UP),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_L1),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_L2),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_R1),
		master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)
	);
	//doStuff(Ctrlr(0,0,0,0,true,false,false,false,false,false,false,false));
}

void doStuff(int leftX=0, int leftY=0, int rightX=0, int rightY=0, 
bool a=false, bool b=false, bool x=false, bool y, 
bool right=false,bool down=false, bool up=false, bool left=false,
bool l1=false, bool l2=false, bool r1=false, bool r2=false){
	//all of the functionality code for the bots goes here
	left_front.move_voltage((leftX * MOVE_VOLT * 0.5 *a) + (a*6000));
	right_front.move_voltage((leftX * -MOVE_VOLT * 0.5 *a) + (a*6000));
	//button input will eventually be recorded here
};
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
	int direction=0;
	bool throwing=false;
	while (true) {
		int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

		left_front.move_voltage(left * MOVE_VOLT);
		right_front.move_voltage(right * -MOVE_VOLT);

		int leftStick = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
		int rightStick = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		bool a_buttonPressed=master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
		bool b_buttonPressed=master.get_digital(pros::E_CONTROLLER_DIGITAL_B);
		bool x_buttonPressed=master.get_digital(pros::E_CONTROLLER_DIGITAL_X);
		bool y_buttonPressed=master.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
		bool l_buttonPressed=master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) || master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
		bool r_buttonPressed=master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) || master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

		
		if(a_buttonPressed){//accelerate
			if(leftStick>0){//right
				left_front.move_voltage(127 * MOVE_VOLT);
				right_front.move_voltage((127-leftStick) * -MOVE_VOLT);//slow down right wheel
				direction=1;
			}
			else if(leftStick<0){//left
				right_front.move_voltage(-127 * MOVE_VOLT);
				left_front.move_voltage((127-leftStick) * MOVE_VOLT);//slow down left wheel
				direction=-1;
			}
			else{//straight
				direction=0;
				left_front.move_voltage(127 * MOVE_VOLT);
				right_front.move_voltage(-127 * MOVE_VOLT);
			}
			if(direction && r_buttonPressed){//drift
				if(direction==1) right_front.move_voltage(0);//brake right motor, is there a brake() function?
				if(direction==-1) left_front.move_voltage(0);//brake left motor
			}
		}
		else if(b_buttonPressed){//brake / go backwards
			left_front.move_voltage(-127 * MOVE_VOLT);
			right_front.move_voltage(127 * MOVE_VOLT);
		}
		else{
			right_front.move_voltage(0);
			left_front.move_voltage(0);
		}

		if(l_buttonPressed){//"throw"??
			if(!throwing) throw(rightStick>0);
			throwing=true;
		}
		else{
			throwing=false;
		}

		void throw(backwards){
			print("throwing shell");
			if(backwards) print(" backwards");
		}
		


		pros::delay(20);
	}
}
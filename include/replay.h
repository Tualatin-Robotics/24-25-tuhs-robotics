#include <fstream>
#include <cstring>
#include <filesystem>
#include <cstdio>
using namespace std;

fstream theFile;//declared it up here instead. Will this work? Find out on Monday...

void logInputs(pros::Controller master,fstream &theFile){
	theFile<<master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) << " , " <<
		master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) << " , " <<
		master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) << " , " <<
		master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_X) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_B) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) << " , " <<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_A) << " ,\n";
}

void open_auton_file(string fileName, bool overwrite) {
	if (overwrite) {
		//std::filesystem::remove(fileName);
		remove("/usd/a_team_auton_file.txt");
	}
	theFile.open(fileName,std::ios_base::in);
}

class ReplayController{
	public:
	int buttons[16];
	int frame=0;
	string fileName;
	
	int32_t get_analog(int stick){
		switch(stick){
			case pros::E_CONTROLLER_ANALOG_LEFT_X: return buttons[0];
			case pros::E_CONTROLLER_ANALOG_LEFT_Y: return buttons[1];
			case pros::E_CONTROLLER_ANALOG_RIGHT_X: return buttons[2];
			case pros::E_CONTROLLER_ANALOG_RIGHT_Y: return buttons[3];
			default: return 0;
		}
	}
	int32_t get_digital(int button){
		switch(button){
			case pros::E_CONTROLLER_DIGITAL_L1: return buttons[4];
			case pros::E_CONTROLLER_DIGITAL_L2: return buttons[5];
			case pros::E_CONTROLLER_DIGITAL_R1: return buttons[6];
			case pros::E_CONTROLLER_DIGITAL_R2: return buttons[7];
			case pros::E_CONTROLLER_DIGITAL_RIGHT: return buttons[8];
			case pros::E_CONTROLLER_DIGITAL_DOWN: return buttons[9];
			case pros::E_CONTROLLER_DIGITAL_UP: return buttons[10];
			case pros::E_CONTROLLER_DIGITAL_LEFT: return buttons[11];
			case pros::E_CONTROLLER_DIGITAL_X: return buttons[12];
			case pros::E_CONTROLLER_DIGITAL_B: return buttons[13];
			case pros::E_CONTROLLER_DIGITAL_Y: return buttons[14];
			case pros::E_CONTROLLER_DIGITAL_A: return buttons[15];
			default: return 0;
		}
	}
	void updateFrame(){
		char comma;
		theFile >> buttons[0];
		theFile >> comma;
		theFile >> buttons[1];
		theFile >> comma;
		theFile >> buttons[2];
		theFile >> comma;
		theFile >> buttons[3];
		theFile >> comma;
		theFile >> buttons[4];
		theFile >> comma;
		theFile >> buttons[5];
		theFile >> comma;
		theFile >> buttons[6];
		theFile >> comma;
		theFile >> buttons[7];
		theFile >> comma;
		theFile >> buttons[8];
		theFile >> comma;
		theFile >> buttons[9];
		theFile >> comma;
		theFile >> buttons[10];
		theFile >> comma;
		theFile >> buttons[11];
		theFile >> comma;
		theFile >> buttons[12];
		theFile >> comma;
		theFile >> buttons[13];
		theFile >> comma;
		theFile >> buttons[14];
		theFile >> comma;
		theFile >> buttons[15];
		theFile >> comma;
		frame++;
	}
	ReplayController(string a){
		fileName=a;
		//theFile.open(fileName,std::ios_base::in);
	}
};
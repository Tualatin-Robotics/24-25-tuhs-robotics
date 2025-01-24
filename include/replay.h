#include <fstream>
#include <cstring>
#include <filesystem>
#include <cstdio>
using namespace std;

fstream theFile;

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
		remove("/usd/a_team_auton_file.txt");
	}
	theFile.open(fileName,std::ios_base::in);
}

class ReplayController{
	public:
	int buttons[16];
	int frame=0;
	bool donePlaying=false;
	string fileName;

	bool is_recording_auton=false;
	
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
	void updateFrame(bool optimized=false){
		frame++;
		char comma;
		for(int i=0;i<16;i++){
			theFile >> buttons[i];
			theFile >> comma;
		}
		//recursively calls updateFrame() until it finds a line that isn't all 0's
		if(!donePlaying && buttons[0]+buttons[1]+buttons[2]+buttons[3]+buttons[4]+buttons[5]+buttons[6]+buttons[7]+buttons[8]+buttons[9]+buttons[10]+buttons[11]+buttons[12]+buttons[13]+buttons[14]+buttons[15]<1024){
			if(optimized && buttons[0]==0 && buttons[1]==0 && buttons[2]==0 && buttons[3]==0 && buttons[4]+buttons[5]+buttons[6]+buttons[7]+buttons[8]+buttons[9]+buttons[10]+buttons[11]+buttons[12]+buttons[13]+buttons[14]+buttons[15]==0){
				updateFrame(true);
			}
		}
		else{
			donePlaying=false;
			for(int i=0;i<16;++i) buttons[i]=0;
			//buttons[0]=buttons[1]=buttons[2]=buttons[3]=buttons[4]=buttons[5]=buttons[6]=buttons[7]=buttons[8]=buttons[9]=buttons[10]=buttons[11]=buttons[12]=buttons[13]=buttons[14]=buttons[15]=0;
		}
		
	}
	void record(pros::Controller master,fstream &theFile){
		if(is_recording_auton){
			logInputs(master,theFile);
			if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
				theFile<<1024;//1024 is greater than the highest possible value of the sum of all the inputs
				theFile.close();
				cout<<"Recording Stopped!";
				is_recording_auton=false;
				pros::delay(1000);
			}
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)
			&& master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			if(!is_recording_auton){
				pros::delay(1000);
				theFile.open(fileName,std::ios_base::out);
				cout << "Recording!";
				is_recording_auton = true;
			}
		}
	}
	ReplayController(string a){
		fileName=a;
	}
};
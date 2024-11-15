#include <fstream>
#include <cstring>
using namespace std;

void logInputs(pros::Controller master,fstream theFile){//fstream as file argument, maybe there's a workaround?
	theFile<<
		master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)<<","<<
		master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)<<","<<
		master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)<<","<<
		master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_X)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_B)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)<<","<<
		master.get_digital(pros::E_CONTROLLER_DIGITAL_A)<<",\n";
}

void parseInputs(fstream theFile,int array[16],int lineNumber){//another fstream as file argument
	char line[64];//a line can't be longer than 50, but just to be safe, I used a power of 2
	theFile.get(line,64);
	char* t=strtok(line,",");
	for(int n=0;n<16;n++){
		if(t!=NULL)array[n]=(int)t;
		t=strtok(NULL,",");
	}
}

class ReplayController{
	private:
	int buttons[16];
	int frame=0;
	string fileName;
	//fstream theFile;//C++ also doesn't like this
	public:
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
		//parseInputs(theFile,buttons,frame);//issue here
		frame++;
	}
	ReplayController(string a){
		fileName=a;
		fstream theFile;
		theFile.open(fileName,std::ios_base::in);
		//ifstream theFile(a);
	}
};

//the main issue with the entire construct is that C++ does not like fstream/ifstream/ofstream/filebuf as function arguments
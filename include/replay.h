#include <fstream>
#include <cstring>
using namespace std;

fstream theFile;//declared it up here instead. Will this work? Find out on Monday...

void logInputs(pros::Controller master,fstream &theFile){
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

int* parseInputs(fstream &theFile,int lineNumber){
	int array[16];
	char line[64];//a line can't be longer than 50, but just to be safe, I used a power of 2
	theFile.get(line,64);
	char* t=strtok(line,",");
	for(int n=0;n<16;n++){
		if(t!=NULL)array[n]=(int)t;
		t=strtok(NULL,",");
	}
	return array;
}

class ReplayController{
	private:
	int buttons[16];
	int frame=0;
	string fileName;
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
		char temp;//if this doesn't work, I have a backup plan...
		theFile>>buttons[0]>>temp>>buttons[1]>>temp>>buttons[2]>>temp>>buttons[3]>>temp>>buttons[4]>>temp>>buttons[5]>>temp>>buttons[6]>>temp>>buttons[7]>>temp>>buttons[8]>>temp>>buttons[9]>>temp>>buttons[10]>>temp>>buttons[11]>>temp>>buttons[12]>>temp>>buttons[13]>>temp>>buttons[14]>>temp>>buttons[15>>temp];
		char*num[4];
		//for(int i=0;i<16;i++) getNextValue(i,0,num);
		frame++;
	}
	void getNextValue(int i,int j,char* num[4]){//this method recursively calls itself until the file pointer hits a comma, then converts the C-style string into an int
		char *c;
		theFile>>c;
		if(!num) char* num[4];
		if(c==","||j>=3){//3 is the highest index in num[4] so there is no point in risking a missing base case and causing at least two different errors
			buttons[i]=(int)(*num);
		}
		else{
			*num[j]=*c;
			getNextValue(i,j+1,num);
		}
	}
	ReplayController(string a){
		fileName=a;
		theFile.open(fileName,std::ios_base::in);
	}
	
};

inline bool fileExists(string&name){
	ifstream f(name.c_str());
	return f.good();
}

string newFile(string name){
	int i=0;
	char g[]={(char)i};
	string v=name+(string)g;
	while(fileExists(v)){
		i+=1;
		g[0]=(char)i;
		v=name+'_'+(string)g+".txt";
	}
	return v;
}
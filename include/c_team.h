#include <fstream>
#include <cstring>
using namespace std;
#include "main.h"
#include "variables.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor left_front(19);
pros::Motor right_front(20);
pros::Motor left_back(18);
pros::Motor right_back(17);

void auton() {
	while(true){
		int a[16];
		/*parseFileInput("c_team_auton_file.txt",a,0);
		doStuff(a[0],a[1],a[2],a[3],a[4],a[5],a[6],a[7],a[8],a[9],a[10],a[11],a[12],a[13],a[14],a[15]);*/
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
	
}

void doStuff(int leftX=0, int leftY=0, int rightX=0, int rightY=0, 
	bool a=false, bool b=false, bool x=false, bool y, 
	bool right=false,bool down=false, bool up=false, bool left=false,
	bool l1=false, bool l2=false, bool r1=false, bool r2=false){
	//all of the functionality code for the bots goes here
	left_front.move_voltage((leftX * MOVE_VOLT * 0.5 *a) + (a*6000));
	right_front.move_voltage((leftX * -MOVE_VOLT * 0.5 *a) + (a*6000));
	//button input will eventually be recorded here
	//uncomment ln55 to test logInputs()
	//logInputs("c_team_auton_file.txt",leftX,leftY,rightX,rightY,a,b,x,y,right,down,up,left,l1,l2,r1,r2);
};

void logInputs(string fileName,int leftX=0, int leftY=0, int rightX=0, int rightY=0, 
	bool a=false, bool b=false, bool x=false, bool y=false, 
	bool right=false,bool down=false, bool up=false, bool left=false,
	bool l1=false, bool l2=false, bool r1=false, bool r2=false){
		ofstream theFile(fileName);
		theFile<<leftX<<","<<leftY<<","<<rightX<<","<<rightY<<","<<a<<","<<b<<","<<x<<","<<y<<","<<right<<","<<down<<","<<up<<","<<left<<","<<l1<<","<<l2<<","<<r1<<","<<r2<<"\n";
		theFile.close();
}

void parseFileInput(string fileName,int array[16],int lineNumber){//this probably won't work as expected so be careful when testing
	ifstream theFile(fileName);
	string thing;
	getline(theFile,thing);//this is easier than converting a string to a char array
	char line[thing.length()];
	theFile.getline(line,thing.length());//still need to figure out how to get appropriate line of file
	theFile.close();
	char* t=strtok(line,",");
	int number=0;
	while(t!=NULL){
		array[number]=(int)t;//functions cannot return arrays, so this one modifies an array passed as an argument
		number++;
		t=strtok(NULL,",");
	}
	//so far, this entire function should retrieve the first line of the file, then parse it and put it into an int array
}
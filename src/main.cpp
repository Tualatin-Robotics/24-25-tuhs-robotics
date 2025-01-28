//Change team here:
#define B_TEAM

#ifdef A_TEAM
#include "a_team.h"
#endif

#ifdef B_TEAM
#include "b_team.h"
#endif

#ifdef C_TEAM
#include "c_team.h"
#endif

#include "display.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
ReplayController replay(fileName);//each team file will have to declare string fileName, providing a path to the appropriate file for the bot

void initialize() {
	init();
	
	//drawScreenImage(imageName);

	
}

void autonomous() {
	theFile.open(fileName,std::ios_base::in);
	while(true) {
		replay.updateFrame(true);//set argument to false if you want the bot to execute the replay to execute exactly as it was recorded
		drive(replay);
		pros::delay(20);
	}
	theFile.close();
}

void opcontrol() {
	while (true) {
		drive(master);
		replay.record(master,theFile);//calls a method from ReplayController (in replay.h) to record the file input
		pros::delay(20);
	}
	theFile.close();
}
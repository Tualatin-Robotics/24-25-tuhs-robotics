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

pros::Controller master(pros::E_CONTROLLER_MASTER);
ReplayController replay(fileName);

void initialize() {
	init();
}

void autonomous() {
	theFile.open(fileName,std::ios_base::in);
	while(true) {
		replay.updateFrame(false);//set argument to false if you want the bot to execute the replay to execute exactly as it was recorded
		drive(replay);
		pros::delay(replay.delayTime);
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
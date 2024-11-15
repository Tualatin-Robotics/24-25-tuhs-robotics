//Change team here:
#define C_TEAM

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
ReplayController replay(fileName);//each team file will have to declare string fileName, providing a path to the appropriate file for the bot

void initialize() {
	//init();
}

void autonomous() {
	while(true){
		drive(replay);
		pros::delay(20);
	}
}

void opcontrol() {
	theFile.open(fileName,std::ios_base::app);//theFile is declared in replay.h

	while (true) {
		drive(master);
		logInputs(master,theFile);
		pros::delay(20);
	}
	theFile.close();
}
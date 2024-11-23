//Change team here:
#define A_TEAM

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
ReplayController replay(fileName+".txt");//each team file will have to declare string fileName, providing a path to the appropriate file for the bot

void initialize() {
	//init();
}

void autonomous() {
	while(true){
		drive(replay);
		replay.updateFrame();//I believe you forgot to call this method when you were testing, see if it works now
		pros::delay(20);
	}
}

void opcontrol() {
	//theFile.open(newFile(fileName),std::ios_base::trunc);//theFile is declared in replay.h

	while (true) {
		drive(master);
		logInputs(master,theFile);//remember to comment this line out when actually driving
		pros::delay(20);
	}
	theFile.close();
}
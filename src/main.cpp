//Change team here:
#define C_TEAM
// Team names include: A_TEAM, B_TEAM, C_TEAM, and PROGRAMMER_TEAM

#ifdef A_TEAM
#include "a_team.h"
#endif

#ifdef B_TEAM
#include "b_team.h"
#endif

#ifdef C_TEAM
#include "c_team.h"
#endif

#ifdef PROGRAMMER_TEAM
#include "code_bot.h"
#endif

#include "replay.h"
#include "display.h"


pros::Controller master(pros::E_CONTROLLER_MASTER);
ReplayController replay(fileName);//each team file will have to declare string fileName, providing a path to the appropriate file for the bot

void initialize() {
	//pros::Motor::set_brake_mode(1);
	init();
	
	drawScreenImage(imageName);
}

void autonomous() {
	theFile.open(fileName,std::ios_base::in);
	auton();
	while(true) {
		replay.updateFrame(false);
		drive(replay);
		pros::delay(20);
		//pros::delay(20-pros::millis()%20);
	}
	theFile.close();
}

void opcontrol() {
	int frame=0;
	init();
	while (true) {
		drive(master);
		replay.record(master,theFile);
		//pros::delay(20);
		pros::delay(20-pros::millis()%20);
	}
	theFile.close();
}
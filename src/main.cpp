//Change team here:
#define B_TEAM;

#ifdef A_TEAM;
#include "a_team.h"
#endif

#ifdef B_TEAM;
#include "b_team.h"
#endif

#ifdef C_TEAM;
#include "c_team.h"
#endif

//int team = TEAM_C;

void initialize() {
	
}

void autonomous() {
	auton();
}

void opcontrol() {
	while (true) {
		drive();

		pros::delay(20);
	}
}
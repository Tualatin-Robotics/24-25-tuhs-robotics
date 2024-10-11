#define C_TEAM;

#include "main.h"
#include "variables.h"

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
		/*switch (team) {
			case TEAM_A:
				a_drive();
			case TEAM_B:
				b_drive();
			case TEAM_C:
				c_drive();
		}*/

		drive();

		pros::delay(20);
	}
}
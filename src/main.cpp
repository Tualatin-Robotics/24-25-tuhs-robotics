#include "main.h"
#include "a_team.h"
#include "b_team.h"
#include "c_team.h"
#include "variables.h"

int team = TEAM_MEDIA;

void initialize() {
	
}

void autonomous() {
	//This is just a test comment
}

void opcontrol() {
	while (true) {
		switch (team) {
			case TEAM_A:
				a_drive();
			case TEAM_B:
				b_drive();
			case TEAM_C:
				c_drive();
		}
		pros::delay(20);
	}
}
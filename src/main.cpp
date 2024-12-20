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

#include "stdlib.h"
#include "display/lvgl.h"
#include "pros/screen.h"
#include <iostream>
#include <string.h>

//#include "screen_image.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
ReplayController replay(fileName);//each team file will have to declare string fileName, providing a path to the appropriate file for the bot
using std::cout;

void initialize() {
	init();

	int scr_width = 100;
	int scr_height = 100;

	fstream img_file;

	img_file.open("/usd/img.ppm", std::ios_base::in);

	img_file.get();
	img_file.get();
	img_file.get();
	int img_w = img_file.get();
	img_file.get();
	int img_h = img_file.get();
	img_file.get();
	img_file.get();
	img_file.get();

	img_w = 589;
	img_h = 429;

	int x = 0;
	int y = 0;

	int red;
	int green;
	int blue;

	while (!img_file.eof() && y < img_h) {
		red = img_file.get();
		img_file.get();
		green = img_file.get();
		img_file.get();
		blue = img_file.get();
		img_file.get();

		pros::screen::set_pen(RGB2COLOR(red, green, blue));

		pros::screen::draw_pixel(x, y);
		// pros::screen::draw_pixel(x + 1, y);
		// pros::screen::draw_pixel(x, y + 1);
		// pros::screen::draw_pixel(x + 1, y + 1);

		x += 1;

		if (x >= img_w) {
			y += 1;
			x = 0;
		}
		
		
		// cout << green;
		// cout << blue;
	}

	pros::screen::set_pen(pros::Color::black);

	pros::screen::draw_rect(0, 0, 1000, 1000);


	
	// pros::screen::print(pros::E_TEXT_MEDIUM, 50, 50, string(img_w));
	// pros::screen::print(pros::E_TEXT_MEDIUM, 50, 100, static_cast<string>(img_h));

	img_file.close();
	
}

void autonomous() {
	theFile.open(fileName,std::ios_base::in);
	while(true) {
		replay.updateFrame();
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
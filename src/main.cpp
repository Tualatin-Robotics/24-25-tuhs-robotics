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
	init();
	
	int scr_width = 480;
	int scr_height = 272;


	//IMG FILE MUST BE NAMED "img.ppm"
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

	img_w = 480;
	img_h = 272;

	int x = scr_width / 2 - img_w / 4;
	x = 0;
	int y = 0;

	int draw_x = x;
	int draw_y = y;

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

		pros::screen::set_pen(RGB2COLOR(blue, green, red));

		pros::screen::draw_pixel(draw_x, draw_y);
		pros::screen::draw_pixel(draw_x + 1, draw_y);

		draw_x += 2;

		if (draw_x >= img_w + x) {
			draw_y += 1;
			draw_x = x;
		}
		
		
		// cout << green;
		// cout << blue;
	}


	// pros::screen::set_pen(RGB2COLOR(255, 255, 255));


	// pros::screen::fill_rect(0, 0, x, 1000);

	// pros::screen::fill_rect(x + (img_w / 2), 0, 1000, 1000);


	
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
		pros::delay(21);
	}
	theFile.close();
}
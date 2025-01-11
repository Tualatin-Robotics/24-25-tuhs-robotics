//can draw things on the screen!!!

void drawScreenImage(){
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
		// pros::screen::draw_pixel(draw_x, draw_y + 1);
		// pros::screen::draw_pixel(draw_x + 1, draw_y + 1);

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
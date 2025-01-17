//can draw things on the screen!!!

void drawScreenImage(string image){
    int scr_width = 480;
	int scr_height = 272;

	fstream img_file;
	img_file.open(image, std::ios_base::in);

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
	}
		
	img_file.close();
}
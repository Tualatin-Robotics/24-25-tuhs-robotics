void drive() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor left_front(2);
	pros::Motor right_front(1);
	pros::Motor left_back(4);
	pros::Motor right_back(3);

	int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

	left_front.move_voltage(left * MOVE_VOLT);
	right_front.move_voltage(right * -MOVE_VOLT);
}
#include "main.h"
#include "lemlib/api.hpp"
#include "config.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	/*if(!pros::competition::is_connected()) {
		pros::Task update_info([&](){
            while (true) {
				pros::lcd::print(0, "X: %f", chassis.getPose().x);
				pros::lcd::print(1, "Y: %f", chassis.getPose().y);
				pros::lcd::print(2, "Angle: %f", chassis.getPose().theta);
                pros::delay(50);
            } 
		});
	}
	chassis.calibrate();
	// set a known initial pose after calibration to avoid NaN from missing sensors
	chassis.setPose(0, 0, 0);*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	bool liftState = LOW;
	//bool tongueState = LOW;

	while (true) {

		// drive train
		int vertical = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y); // Y axis of the left joystick
        int horizontal = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // X axis of the right joystick

        chassis.arcade(vertical, horizontal, false); // arcarde drive

		// intake
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) intake.move(-127);
		else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) intake.move(127);
		else intake.move(0);

		// indexer
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			lift.set_value(liftState);
		}
		if (controller.get_digital_new_release(pros::E_CONTROLLER_DIGITAL_L2)) {
			liftState = !liftState;
		}

		// tongue mech
		//if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
		//	tongueState = !tongueState;
		//	tongueMech.set_value(tongueState);
		//}

		pros::delay(20); // Run for 20 ms then update
	}
}
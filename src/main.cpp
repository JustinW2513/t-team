#include "main.h"
#include "lemlib/api.hpp"
#include "config.hpp"
#include "pros/misc.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Test");
	pros::lcd::set_text(2, config::version);
	pros::lcd::set_text(3, config::upload_message);

	pros::lcd::register_btn1_cb(on_center_button);
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

	bool intakeForward = false;
	bool intakeBackward = false;
	bool intakeFrontBackward = false;
	bool indexerState = LOW;
	//bool tongueState = LOW;

	while (true) {

		// drive train
		int vertical = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y); // Y axis of the left joystick
        int horizontal = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // X axis of the right joystick

        chassis.arcade(vertical, horizontal, false, 0.45); // arcarde drive

		// intake
		//if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) intake.move(300);
		//else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) intake.move(-300);
		//else intake.move(0);
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			if (intakeForward) {
				intakeFront.move(0);
				intakeBack.move(0);
				intakeFrontBackward = false;
			} else {
				intakeFront.move(300);
				intakeBack.move(300);
				intakeBackward = false;
			}
			intakeForward = !intakeForward;
		} else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			if (intakeBackward) {
				intakeFront.move(0);
				intakeBack.move(0);
			} else {
				intakeFront.move(-300);
				intakeBack.move(-300);
				intakeForward = false;
				intakeFrontBackward = false;
			}
			intakeBackward = !intakeBackward;
		}

		if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y) && intakeForward) {
			if (intakeFrontBackward) {
				intakeFront.move(300);
			} else {
				intakeFront.move(-100);
			}
			intakeFrontBackward = !intakeFrontBackward;
		}

		// indexer
		if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			indexerState = !indexerState;
			indexerTop.set_value(indexerState);
			//indexerBottom.set_value(!indexerState);
		}

		// tongue mech
		//if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
		//	tongueState = !tongueState;
		//	tongueMech.set_value(tongueState);
		//}
		

		pros::delay(20); // Run for 20 ms then update
	}
}
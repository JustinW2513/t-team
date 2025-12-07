#include "main.h"
#include "auton.hpp"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	chassis.calibrate();
	
	pros::Task screenTask([&]() {
		while (true) {
			// print robot location to the brain screen
			pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
			pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
			pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
			// log position telemetry
			lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
			// delay to save resources
			pros::delay(50);
		}
	});
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
void autonomous() {
    // set position to x:0, y:0, heading:0
    //chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
	//chassis.turnToHeading(180, 1000);
	//chassis.waitUntilDone();
	//chassis.turnToHeading(0, 1000);
    //chassis.moveToPoint(0, 20, 100000);
	//auton();
}

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
	// r1 hold intake, r2 hold outtake
	// l1 toggle indexer toggle
	// l2 toggle tongue mech
	// a toogle intake (slow)
	// up toggle wing

	bool intakeState = false; // intake toggle mode or not toggle, false = no toggle
	bool intakeForward = false;
	bool intakeBackward = false;

	bool indexerState = false; // false = not running
	bool middleGoal = false; // false = not running

	while (true) {

		// drivetrain
		int vertical = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y); // Y axis of the left joystick
        int horizontal = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // X axis of the right joystick
		chassis.arcade(vertical, horizontal, false); // arcarde drive

		// intake
		if (intakeState) {
			if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
				if (intakeForward) {
					intake.move(0);
					indexer.move(0);
				} else {
					intake.move(127);
					if(indexerState) indexer.move(127);
					intakeBackward = false;
				}
				intakeForward = !intakeForward;
			} else if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
				if (intakeBackward) {
					intake.move(0);
				} else {
					intake.move(-127);
					indexer.move(0);
					intakeForward = false;
				}
				intakeBackward = !intakeBackward;
			}
		} else {
			if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
				intake.move(127);
				if(indexerState) indexer.move(127);
			} else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) intake.move(-127);
			else {
				intake.move(0);
				indexer.move(0);
			}
		}

		// toggle intake input method
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
			intakeState = !intakeState;
		}

		// indexer
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
			indexerState = !indexerState;
		}

		// tongue mech
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
			tongueMech.toggle();
		}

		// wing
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
			wing.toggle();
		}

		// middle goal
		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
			//middleGoalIndexerTop.toggle();
			//middleGoalIndexerBottom.toggle();
			intake.move((middleGoal)? 0 : 127);
			middleGoal = !middleGoal;
		}

		/*if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
			// set position to x:0, y:0, heading:0
			chassis.setPose(0, 0, 0);
			// turn to face heading 90 with a very long timeout
			chassis.turnToHeading(180, 1000);
			chassis.waitUntilDone();
			chassis.turnToHeading(0, 1000);
		}

		if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
			// set position to x:0, y:0, heading:0
			chassis.setPose(0, 0, 0);
			// turn to face heading 90 with a very long timeout
			chassis.turnToHeading(90, 1000);
		}*/

		pros::delay(20); // Run for 20 ms then update
	}
}
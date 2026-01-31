#pragma once

#include "config.hpp"

/*void auton() {
    chassis.setPose(-46.7, -15.825, 0);
    chassis.moveToPoint(-46.7, -47, 1000, {.forwards=false, .maxSpeed=80});
    chassis.turnToHeading(90, 600);

    // match load 
    tongueMech.toggle();
    chassis.moveToPoint(-48, -47, 1000, {.forwards=false, .maxSpeed=60, .minSpeed=60});
    while(chassis.isInMotion()) { pros::delay(20); }
    intake.move(127);
    pros::delay(1500);
    intake.move(0);

    // score long goal
    chassis.moveToPoint(-24.581, -47, 1000, {.maxSpeed=80});
    while(chassis.isInMotion()) { pros::delay(20); }
    intake.move(127);
    indexer.move(127);
    pros::delay(1500);
    intake.move(0);
    indexer.move(0);
    tongueMech.toggle();
    
    // cross field
    
    // intake mid blocks
    chassis.swingToHeading(180, lemlib::DriveSide::LEFT, 600);
    chassis.moveToPoint(-19.736, -24.518, 600, {.forwards=false, .maxSpeed=70, .minSpeed=50});
    chassis.waitUntilDone();
    tongueMech.toggle();
    intake.move(127);
    pros::delay(800);

    chassis.turnToHeading(0, 600);
    intake.move(0);

    // intakes other mid blocks
    chassis.moveToPoint(-21.49, 24.538, 2000, {.forwards=false, .maxSpeed=80, .minSpeed=40, .earlyExitRange=5});
    chassis.waitUntilDone();
    tongueMech.toggle();
    intake.move(127);
    pros::delay(800);
    intake.move(0);

    chassis.turnToHeading(135, 600, {.maxSpeed=80, .minSpeed=60});
    chassis.moveToPoint(-12, 12, 1000, {.maxSpeed=80});
    while(chassis.isInMotion()) { pros::delay(20); }
    middleGoalIndexerTop.toggle();
	middleGoalIndexerBottom.toggle();
    intake.move(90);
    pros::delay(600);
    intake.move(0);
    middleGoalIndexerTop.toggle();
	middleGoalIndexerBottom.toggle();

    // match load

    chassis.moveToPoint(-47, 47, 1200, {.forwards=false, .maxSpeed=80});
    chassis.turnToHeading(90, 600);

    tongueMech.toggle();
    chassis.moveToPoint(-65, 47, 1000, {.forwards=false, .maxSpeed=60, .minSpeed=60});
    while(chassis.isInMotion()) { pros::delay(20); }
    intake.move(127);
    pros::delay(1500);
    intake.move(0);

    // score long goal
    chassis.moveToPoint(-24.581, 47, 600, {.maxSpeed=80, .minSpeed=80});
    while(chassis.isInMotion()) { pros::delay(20); }
    intake.move(127);
    indexer.move(127);
}*/
#pragma once

#include "lemlib/api.hpp"

namespace config {
    // Drivetrain
    inline const double dt_track_width = 27;
    inline const double dt_wheel_diameter = lemlib::Omniwheel::NEW_325;

    inline int dt_rpm = 450;
    inline uint8_t dt_horizontal_drift = 2;

    inline const std::initializer_list<int8_t> right_motor_ports = {13, 12, 16};
    inline const std::initializer_list<int8_t> left_motor_ports = {-20, -14, -19};

    // Intake
    inline const int8_t intake_port = 18;
    inline const int8_t indexer_port = -15;
    inline const char tongue_ADI = 'A';
    inline const char wing_ADI = 'B';
    inline const char middle_goal_top_ADI = 'C';
    inline const char middle_goal_bottom_ADI = 'D';

    // Odom
    inline const int8_t imu_port = 3;
    inline const int8_t vertical_encoder_port = 17;
    inline const double vertical_wheel_diameter = lemlib::Omniwheel::NEW_2;
    inline const double vertical_wheel_distance = 0;

    // Lateral PID
    inline const double lateral_kP = 7.5;
    inline const double lateral_kI = 0;
    inline const double lateral_kD = 3;

    inline const double lateral_anti_windup = 0;
    inline const double lateral_small_error_range = 0;
    inline const double lateral_small_error_range_timeout = 0;
    inline const double lateral_large_error_range = 0;
    inline const double lateral_large_error_range_timeout = 0;
    inline const double lateral_slew = 0;

     // Angular PID
    inline const double angular_kP = 1.65;
    inline const double angular_kI = 0;
    inline const double angular_kD = 10;

    inline const double angular_anti_windup = 0;
    inline const double angular_small_error_range = 0;
    inline const double angular_small_error_range_timeout = 0;
    inline const double angular_large_error_range = 0;
    inline const double angular_large_error_range_timeout = 0;
    inline const double angular_slew = 0;

} // namespace config

// Controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER);

// Motors
inline pros::MotorGroup leftMotorGroup(config::left_motor_ports, pros::MotorGearset::blue);
inline pros::MotorGroup rightMotorGroup(config::right_motor_ports, pros::MotorGearset::blue);
inline pros::Motor intake(config::intake_port, pros::MotorGearset::blue);
inline pros::Motor indexer(config::indexer_port, pros::MotorGearset::blue);

// Drive train settings
inline lemlib::Drivetrain driveTrain(&leftMotorGroup, &rightMotorGroup, config::dt_track_width, config::dt_wheel_diameter, config::dt_rpm, config::dt_horizontal_drift);

// Pneumatics
inline pros::adi::Pneumatics tongueMech(config::tongue_ADI, false);
inline pros::adi::Pneumatics wing(config::wing_ADI, false);
inline pros::adi::Pneumatics middleGoalIndexerTop(config::middle_goal_top_ADI, false);
inline pros::adi::Pneumatics middleGoalIndexerBottom(config::middle_goal_bottom_ADI, true);

// Imu
inline pros::Imu imu(config::imu_port);

// Tracking Wheels
inline pros::Rotation verticalEncoder(config::vertical_encoder_port);
inline lemlib::TrackingWheel vertical(&verticalEncoder, config::vertical_wheel_diameter, config::vertical_wheel_distance);

// Sensors
inline lemlib::OdomSensors odom(&vertical, nullptr, nullptr, nullptr, &imu);
//inline pros::Optical color_sensor(color_sensor_port);

// PID
inline lemlib::ControllerSettings lateral_controller(config::lateral_kP, config::lateral_kI, config::lateral_kD, config::lateral_anti_windup, config::lateral_small_error_range, config::lateral_small_error_range_timeout, config::lateral_large_error_range, config::lateral_large_error_range_timeout, config::lateral_slew);
inline lemlib::ControllerSettings angular_controller(config::angular_kP, config::angular_kI, config::angular_kD, config::angular_anti_windup, config::angular_small_error_range, config::angular_small_error_range_timeout, config::angular_large_error_range, config::angular_large_error_range_timeout, config::angular_slew);

// Drive curves
inline lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband (out of 127)
                                            10, // minimum output for movement (out of 127)
                                            1.02 // curve gain (a - value)
);
inline lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband (out of 127)
                                        10, // minimum output for movement (out of 127)
                                        1.01 // curve gain (a - value)
);

// Chassis
inline lemlib::Chassis chassis(driveTrain, lateral_controller, angular_controller, odom, &throttleCurve, &steerCurve);
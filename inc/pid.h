#ifndef PID_H
#define PID_H

#include<math.h>

#ifndef float_number
	#define float_number float
#endif

typedef struct pid_const pid_const;
struct pid_const
{
	// The below 3 are PID controller constants
	float_number Kp;
	float_number Ki;
	float_number Kd;

	// The below attribute provides the range for the output and internal individual outputs
	float_number range;
};

typedef struct pid_state pid_state;
struct pid_state
{
	pid_const constants;

	float_number previous_value; // previous sensed value, for the derivative controller

	float_number accumulated_error; // accumulated error for the integral controller
};

// first initialization
void pid_init(pid_state* pid, float_number Kp, float_number Ki, float_number Kd, float_number range);

// to be done on a reset, if required, this keeps the constants same
void pid_reinit(pid_state* pid);

// updates pid constants
void pid_update_constants(pid_state* pid, float_number Kp, float_number Ki, float_number Kd);

// it is your responsibility to call pid_update at a regular interval in your program
// here the current_value is the output of the sensor value, while set_point is what we want it to be
// the return value is what you need to feed to your actuators/devices to bring the current_value (sensor generated) closer and closer to your set_point (what you want your sensor value to be at)
float_number pid_update(pid_state* pid, float_number current_value, float_number set_point);

/*
	For a quadcopter drone
	current_value = gyroscope value from the sensor
	set_point = input signal from the joystick that dictates what gyroscope value should be
	the return value here should be fed into the motors on both sides differentially to make the current_value reach set_point in some duration of time
*/

#endif
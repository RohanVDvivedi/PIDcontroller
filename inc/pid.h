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
float_number pid_update(pid_state* pid, float_number current_value, float_number set_point);

#endif
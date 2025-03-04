#include<pid.h>

void pid_init(pid_state* pid, float_number Kp, float_number Ki, float_number Kd, float_number range)
{
	pid->previous_value = NAN;
	pid->accumulated_error = 0.0;
	pid->constants.Kp = Kp;
	pid->constants.Ki = Ki;
	pid->constants.Kd = Kd;
	pid->constants.range = range;
}

void pid_reinit(pid_state* pid)
{
	pid->previous_value = NAN;
	pid->accumulated_error = 0.0;
}

void pid_update_constants(pid_state* pid, float_number Kp, float_number Ki, float_number Kd)
{
	pid->constants.Kp = Kp;
	pid->constants.Ki = Ki;
	pid->constants.Kd = Kd;
}

float_number pid_update(pid_state* pid, float_number current_value, float_number set_point)
{
	// this condition is when the pid_update is first called
	// we set it to current value so that the derivative component is 0, for this first iteration after a reset
	if(isnan(pid->previous_value))
		pid->previous_value = current_value;

	// calculate error
	float_number error = set_point - current_value;

	// propotional component
	float_number propotional = pid->constants.Kp * error;

	// integral component
	pid->accumulated_error += error;
	float_number integral = pid->constants.Ki * pid->accumulated_error;

	// integral component can overshoot, so make corrections if so
	{
		int integral_overshot = 1;
		if(integral > pid->constants.range)
			integral =  pid->constants.range;
		else if(integral < -pid->constants.range)
			integral = -pid->constants.range;
		else
			integral_overshot = 0;

		// if the integral overshot, then bound the accumulated error
		if(integral_overshot)
			pid->accumulated_error = integral/pid->constants.Ki;
	}

	// derivative component
	// notice: previous_error and error are both calculated using the same set_point, this is to avoid derivative componet spikes
	float_number previous_error = set_point - pid->previous_value;
	float_number derivative  = pid->constants.Kd * (error - previous_error);
	pid->previous_value = current_value; // update the previous_value with the current_value, i.e. prepare for next iteration

	// sum up all the three components
	float_number result = propotional + integral + derivative;

	// bound result if it overshoots
	if(result > pid->constants.range)
		result = pid->constants.range;
	else if(result < -pid->constants.range)
		result = -pid->constants.range;

	return result;
}
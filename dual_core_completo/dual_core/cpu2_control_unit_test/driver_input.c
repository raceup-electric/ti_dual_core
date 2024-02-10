#include "driver_input.h"
#include "atc_management.h"

// alberto patch
/*
 * Retrieve data from ATC
 */
void readThrottleBrakeSteering()
{
    throttle = atc_acceleration_pedal();
    brake = atc_brake_pedal();
    steering = atc_steering_sensor();
}

void wheels_angles()
{
    w_angles[0] = delta_steer[0] - TOE_F;
    w_angles[1] = delta_steer[1] + TOE_F;
    w_angles[2] = -TOE_R;
    w_angles[3] = TOE_R;
}

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

    int i;
    for (i = filterValCount - 1; i > 0; i--)
    {
        throttles[i] = throttles[i - 1];
        brakes[i] = brakes[i - 1];
        steerings[i] = steerings[i - 1];
    }
    throttles[0] = throttle;
    brakes[0] = brake;
    steerings[0] = steering;
    bool bSame = true, tSame = true;
    for (i = 1; i < filterValCount; i++)
    {
        if (throttles[i] != throttles[0])
        {
            tSame = false;
        }

        if (brakes[i] != brakes[0])
        {
            bSame = false;
        }
    }

    if (bSame)
    {
        brake = brakes[0];
    }
    else
    {
        float mbrake = brake;
        for (i = 0; i < filterValCount; i++)
        {
            if (brakes[i] > mbrake)
            {
                mbrake = brakes[i];
            }
        }

        float sbrake = 0, count = 0;
        for (i = 0; i < filterValCount; i++)
        {
            if (brakes[i] < mbrake)
            {
                sbrake += brakes[i];
                count += 1.0;
            }
        }
        if (count > 0)
        {
            brake = sbrake / count;
        }
        else
        {
            brake = 0;
        }
    }

    if (tSame)
    {
        throttle = throttles[0];
    }
    else
    {
        float mthrottle = throttle;
        for (i = 0; i < filterValCount; i++)
        {
            if (throttles[i] > mthrottle)
            {
                mthrottle = throttles[i];
            }
        }

        float sthrottle = 0, count = 0;
        for (i = 0; i < filterValCount; i++)
        {
            if (throttles[i] < mthrottle)
            {
                sthrottle += throttles[i];
                count += 1.0;
            }
        }

        if (count > 0)
        {
            throttle = sthrottle / count;
        }
        else
        {
            throttle = 0;
        }
    }
}

void wheels_angles()
{
    w_angles[0] = delta_steer[0] - TOE_F;
    w_angles[1] = delta_steer[1] + TOE_F;
    w_angles[2] = -TOE_R;
    w_angles[3] = TOE_R;
}

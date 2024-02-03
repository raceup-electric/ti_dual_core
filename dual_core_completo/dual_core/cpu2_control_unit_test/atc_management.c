#include "atc_management.h"
#include "dbc_gen/can2.h"

// only for compatibility with legacy code
//--------------------------------------
#include "car_management.h"
//--------------------------------------

struct atc_data
{
    can_0x053_Driver_t data_1;
    can_0x102_SuspFront_t data_2;
};

// private
static struct atc_data ATC =
    {
        .data_1.steering = 0,
        .data_1.throttle = 0,
        .data_1.brake = 0,
        .data_2.susp_fr = 0,
        .data_2.susp_fl = 0,
        .data_2.temp_ml = 0,
        .data_2.temp_mr = 0,
};

// public
void atc_update(can_obj_can2_h_t *atc_data, unsigned int message_number)
{
    can_0x053_Driver_t *driver;
    can_0x102_SuspFront_t *susp;
    switch (message_number)
    {
    case 1:
        driver = &atc_data->can_0x053_Driver;
        ATC.data_1.throttle = driver->throttle;
        ATC.data_1.brake = driver->brake;
        ATC.data_1.steering = driver->steering;
        // only for compatibility with legacy code
        //--------------------------------------
        throttle = driver->throttle;
        brake = driver->brake;
        steering = driver->steering;
        //--------------------------------------
        break;
    case 2:
        susp = &atc_data->can_0x102_SuspFront;
        ATC.data_2.susp_fl = susp->susp_fl;
        ATC.data_2.susp_fr = susp->susp_fr;
        ATC.data_2.temp_ml = susp->temp_ml;
        ATC.data_2.temp_mr = susp->temp_mr;

        // only for compatibility with legacy code
        //--------------------------------------
        suspensions[1] = susp->susp_fr;
        suspensions[0] = susp->susp_fl;
        temperatures[0] = susp->susp_fl;
        temperatures[1] = susp->susp_fr;
        //--------------------------------------
        break;
    default:
        // invalid packet
        break;
    }
}

// steering -180 + 180
unsigned int atc_steering_sensor()
{
    return ATC.data_1.steering;
}
// acceleration 0-100
unsigned char atc_acceleration_pedal()
{
    return ATC.data_1.throttle;
}
// brake 0-100
unsigned char atc_brake_pedal()
{
    return ATC.data_1.brake;
}
// suspension 0-200
unsigned int atc_front_suspension_left()
{
    return ATC.data_2.susp_fl;
}

unsigned int atc_front_suspension_right()
{
    return ATC.data_2.susp_fr;
}
// temperature 0-150
unsigned int atc_motor_temperature_left()
{
    return ATC.data_2.temp_ml;
}

unsigned int atc_motor_temperature_right()
{
    return ATC.data_2.temp_mr;
}

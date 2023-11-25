#include <stdint.h>

#include "atc_management.h"

struct atc_data{
    uint8_t throttle_pedal;
    uint8_t front_suspensions;
    int8_t motor_temperature;
    int8_t steering_sensor;
    uint8_t brake_pedal;
};


static struct atc_data ATC;

void atc_update(unsigned char atc_data[DATA_AMOUNT])
{
    ATC.throttle_pedal=atc_data[0];
    ATC.front_suspensions=atc_data[1];
    ATC.motor_temperature=atc_data[2];
    ATC.steering_sensor=atc_data[3];
    ATC.brake_pedal=atc_data[4];
}

//steering -180 + 180
unsigned char atc_steering_sensor()
{
    return ATC.steering_sensor;
}
//acceleration 0-100
unsigned char atc_acceleration_pedal()
{
    return ATC.throttle_pedal;
}
//brake 0-100
unsigned char atc_brake_pedal()
{
    return ATC.brake_pedal;   
}
//suspension 0-200
unsigned char atc_front_suspension()
{
    return ATC.front_suspensions;
}
//temperature 0-150
unsigned char atc_motor_temperature()
{
    return ATC.motor_temperature;
}


#include <stdint.h>

#include "atc_management.h"

struct atc_data{
    uint8_t throttle_pedal;
    uint8_t front_suspension_left;
    uint8_t front_suspension_right;
    int8_t motor_temperature_right;
    int8_t motor_temperature_left;
    int8_t steering_sensor;
    uint8_t brake_pedal;
};

//private
static struct atc_data ATC;

//public
void atc_update(unsigned char atc_data[DATA_AMOUNT])
{
    ATC.throttle_pedal=atc_data[0];
    ATC.front_suspension_left=atc_data[1];
    ATC.front_suspension_right=atc_data[2];
    ATC.motor_temperature_right=atc_data[3];
    ATC.motor_temperature_left=atc_data[4];
    ATC.steering_sensor=atc_data[5];
    ATC.brake_pedal=atc_data[6];
}

//steering -180 + 180
inline unsigned char atc_steering_sensor() 
{
    return ATC.steering_sensor;
}
//acceleration 0-100
inline unsigned char atc_acceleration_pedal() 
{
    return ATC.throttle_pedal;
}
//brake 0-100
inline unsigned char atc_brake_pedal() 
{
    return ATC.brake_pedal;   
}
//suspension 0-200
inline unsigned char atc_front_suspension_left() 
{
    return ATC.front_suspension_left;
}

inline unsigned char atc_front_suspension_right()
{
    return ATC.front_suspension_right;
}
//temperature 0-150
inline unsigned char atc_motor_temperature_left() 
{
    return ATC.motor_temperature_left;
}

inline unsigned char atc_motor_temperature_right() 
{
    return ATC.motor_temperature_right;
}

#include <stdint.h>

#include "atc_management.h"

struct atc_data{
    uint16_t throttle_pedal;
    uint16_t front_suspension_left;
    uint16_t front_suspension_right;
    uint16_t motor_temperature_right;
    uint16_t motor_temperature_left;
    uint16_t steering_sensor;
    uint16_t brake_pedal;
};

//private
static struct atc_data ATC;

//public
void atc_update(uint16_t *atc_data,unsigned int message_number)
{
    switch (message_number) {
        case 1:
            ATC.throttle_pedal          =atc_data[0];
            ATC.front_suspension_left   =atc_data[1];
            ATC.front_suspension_right  =atc_data[2];
            ATC.motor_temperature_right =atc_data[3];
            break;
        case 2:
            ATC.motor_temperature_left  =atc_data[0];
            ATC.steering_sensor         =atc_data[1];
            ATC.brake_pedal             =atc_data[2];
            break;
        default:
            //invalid packet
            break;
    }
}

//steering -180 + 180
inline uint16_t atc_steering_sensor() 
{
    return ATC.steering_sensor;
}
//acceleration 0-100
inline uint16_t atc_acceleration_pedal() 
{
    return ATC.throttle_pedal;
}
//brake 0-100
inline uint16_t atc_brake_pedal() 
{
    return ATC.brake_pedal;   
}
//suspension 0-200
inline uint16_t atc_front_suspension_left() 
{
    return ATC.front_suspension_left;
}

inline uint16_t atc_front_suspension_right()
{
    return ATC.front_suspension_right;
}
//temperature 0-150
inline uint16_t atc_motor_temperature_left() 
{
    return ATC.motor_temperature_left;
}

inline uint16_t atc_motor_temperature_right() 
{
    return ATC.motor_temperature_right;
}

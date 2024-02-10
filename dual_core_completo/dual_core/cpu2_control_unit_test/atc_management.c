#include "atc_management.h"

// only for compatibility with legacy code
//--------------------------------------
#include "car_management.h"
//--------------------------------------



// private



// public

void atc_update(unsigned int data[], enum type_message t) {

}


// steering -180 + 180
unsigned int atc_steering_sensor()
{
}
// acceleration 0-100
unsigned char atc_acceleration_pedal()
{
}
// brake 0-100
unsigned char atc_brake_pedal()
{
}
// suspension 0-200
unsigned int atc_front_suspension_left()
{
}

unsigned int atc_front_suspension_right()
{
}
// temperature 0-150
unsigned int atc_motor_temperature_left()
{
}

unsigned int atc_motor_temperature_right()
{
}

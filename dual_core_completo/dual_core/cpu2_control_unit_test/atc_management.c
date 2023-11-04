#include "atc_management.h"

struct atc_data
{
    char steering_sensor;
    unsigned char acc_pedal;
    unsigned char brake_pedal;
    unsigned char suspension_compression;
    unsigned char temperature_sensor;
};

static struct atc_data ATC;

void atc_rewrite(unsigned char *atc_data)
{
    ATC.steering_sensor = atc_data[0];
    ATC.acc_pedal = atc_data[1];
    ATC.brake_pedal = atc_data[2];
    ATC.suspension_compression = atc_data[3];
    ATC.temperature_sensor = atc_data[4];
}

//steering -180 + 180
unsigned char atc_steering_sensor()
{
    return ATC.steering_sensor;
}
//acceleration 0-100
unsigned char atc_acceleration_pedal()
{
    return ATC.acc_pedal;
}
//brake 0-100
unsigned char atc_brake_pedal()
{
    return ATC.brake_pedal;   
}
//suspension 200
unsigned char atc_front_suspension()
{
    return ATC.suspension_compression;
}
//temperature 0-150
unsigned char atc_motor_temperature()
{
    return ATC.temperature_sensor;
}


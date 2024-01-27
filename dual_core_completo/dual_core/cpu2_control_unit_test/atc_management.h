#ifndef _ATC_MANAGEMENT_
#define _ATC_MANAGEMENT_
#include "dbc_gen/can2.h"


//only for compatibility with legacy code
//--------------------------------------
extern int throttle;
extern int brake;
extern int steering;
extern float suspensions[4];
extern float temperatures[8];
//--------------------------------------


//steering -180 + 180
unsigned int atc_steering_sensor();
//acceleration 0-100
unsigned char atc_acceleration_pedal();
//brake 0-100
unsigned char atc_brake_pedal();
//suspension 200
unsigned int atc_front_suspension_left();

unsigned int atc_front_suspension_right();
//temperature 0-150
unsigned int atc_motor_temperature_left();

unsigned int atc_motor_temperature_right();


void atc_update(can_obj_can2_h_t *atc_data,unsigned int message_number);

#endif

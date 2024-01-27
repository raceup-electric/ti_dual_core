#ifndef _ATC_MANAGEMENT_
#define _ATC_MANAGEMENT_
#include "dbc_gen/can2.h"

//steering -180 + 180
Uint16 atc_steering_sensor();
//acceleration 0-100
unsigned char atc_acceleration_pedal();
//brake 0-100
unsigned char atc_brake_pedal();
//suspension 200
inline Uint16 atc_front_suspension_left();

inline Uint16 atc_front_suspension_right();
//temperature 0-150
inline Uint16 atc_motor_temperature_left();

inline Uint16 atc_motor_temperature_right();


void atc_update(can_obj_can2_h_t *atc_data,unsigned int message_number);

#endif

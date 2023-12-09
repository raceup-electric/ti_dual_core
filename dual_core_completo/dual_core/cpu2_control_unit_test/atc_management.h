#ifndef _ATC_MANAGEMENT_
#define _ATC_MANAGEMENT_
#include <stdint.h>


//steering -180 + 180
uint16_t atc_steering_sensor();
//acceleration 0-100
uint16_t atc_acceleration_pedal();
//brake 0-100
uint16_t atc_brake_pedal();
//suspension 200
inline uint16_t atc_front_suspension_left();

inline uint16_t atc_front_suspension_right();
//temperature 0-150
inline uint16_t atc_motor_temperature_left();

inline uint16_t atc_motor_temperature_right();


void atc_update(uint16_t *atc_data,unsigned int message_number);

#endif

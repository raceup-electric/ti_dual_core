#ifndef _ATC_MANAGEMENT_
#define _ATC_MANAGEMENT_

#define DATA_AMOUNT 7 //must coincide with the ATC

//steering -180 + 180
unsigned char atc_steering_sensor();
//acceleration 0-100
unsigned char atc_acceleration_pedal();
//brake 0-100
unsigned char atc_brake_pedal();
//suspension 200
inline unsigned char atc_front_suspension_left();

inline unsigned char atc_front_suspension_right();
//temperature 0-150
inline unsigned char atc_motor_temperature_left();

inline unsigned char atc_motor_temperature_right();


void atc_update(unsigned char *atc_data);

#endif

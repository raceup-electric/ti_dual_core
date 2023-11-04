#ifndef _ATC_MANAGEMENT_
#define _ATC_MANAGEMENT_

//steering -180 + 180
unsigned char atc_steering_sensor();
//acceleration 0-100
unsigned char atc_acceleration_pedal();
//brake 0-100
unsigned char atc_brake_pedal();
//suspension 200
unsigned char atc_front_suspension();
//temperature 0-150
unsigned char atc_motor_temperature();


void atc_rewrite(unsigned char *atc_data);

#endif

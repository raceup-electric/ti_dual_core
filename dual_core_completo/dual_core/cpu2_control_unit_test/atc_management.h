#ifndef _ATC_MANAGEMENT_
#define _ATC_MANAGEMENT_

enum type_message {TBS, SENSORS};

// only for compatibility with legacy code
//--------------------------------------
extern int throttle;
extern int brake;
extern int steering;
extern unsigned char imp;
extern float suspensions[4];
extern float temperatures[10];
//--------------------------------------

// steering -180 + 180
unsigned int atc_steering_sensor();
// acceleration 0-100
unsigned char atc_acceleration_pedal();
// brake 0-100
unsigned char atc_brake_pedal();
// suspension 200
unsigned int atc_front_suspension_left();

unsigned int atc_front_suspension_right();
// temperature 0-150
unsigned int atc_motor_temperature_left();

unsigned int atc_motor_temperature_right();

void atc_update(unsigned int data[], enum type_message t);

#endif

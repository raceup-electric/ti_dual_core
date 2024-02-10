#include "atc_management.h"

// only for compatibility with legacy code
//--------------------------------------
#include "car_management.h"
//--------------------------------------



// private



// public

void atc_update(unsigned int data[], enum type_message t) {

    switch(t){

    case TBS:
        throttle = data[0] & 0xFF;
        brake = (data[0] >> 8) & 0xFF;
        steering = data[1] & 0xFFF;
        break;

    case SENSORS:
        suspensions[1] = data[0] & 0x3FF;
        suspensions[0] = ( data[0] >> 10 ) | (( data[1] & 0xF) << 4);
        temperatures[0] = (data[1] >> 4) & 0x3FF;
        temperatures[1] = (data[1] >> 14) | data[2] << 2;

        break;
    }
}

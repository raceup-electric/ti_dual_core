#include "atc_management.h"

// only for compatibility with legacy code
//--------------------------------------
#include "car_management.h"
//--------------------------------------



// private



// public

void atc_update(unsigned int data[], enum type_message t) {

    uint64_t aux = 0;
    int i;

    switch(t){

    case TBS:
        throttle = data[0] & 0xFF;
        brake = data[1] & 0xFF;
        steering = data[2] & 0xFF | (data[3] & 0xF) << 8;
        break;

    case SENSORS:

        for (i = 4; i >= 0; i--)
        {
            aux = aux << 8;
            aux |= (0x00FF & data[i]);
        }


        for (i = 0; i < 2; i++)
        {
            suspensions[i] = (0x3FF & aux);
            aux >>= 10;
        }

        for (i = 0; i < 2; i++)
        {
            temperatures[i] = (0x3FF & aux);
            aux >>= 10;
        }

        break;
    }
}

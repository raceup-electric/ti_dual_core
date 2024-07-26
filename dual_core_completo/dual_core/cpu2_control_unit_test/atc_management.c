#include "atc_management.h"
#include "F28x_Project.h"

// public
void atc_update(unsigned int data[], enum type_message t) {

    uint64_t aux = 0;
    int i;

    for (i = 4; i >= 0; i--)
    {
        aux = aux << 8;
        aux |= (0x00FF & data[i]);
    }

    switch(t){

    case TBS:
        throttle = data[0] & 0xFF;
        brake = data[1] & 0xFF;
        steering = (int)((data[2] & 0xFF) | ((data[3] & 0xF) << 8)) - 90;
        imp = !((data[3] >> 4) & 0x01);

        time_elapsed_ATC = time_elapsed;

        break;
    case SUSPS:
        for (i = 0; i < 2; i++)
        {
            suspensions[i] = (0xFFF & aux) / 10;
            aux >>= 12;
        }
        break;
    case TEMPS:
        for (i = 0; i < 2; i++)
        {
            temperatures[8+i] = (0x3FF & aux);
            aux >>= 10;
        }
        break;
    }
}

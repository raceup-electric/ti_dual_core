
#include "epwm_management.h"


/*
 * Logic is not inverted
 */
void setFanSpeed(int speed){
    TXCANA_ATMega_Data[0] = fan_enable | (speed<<1);
}

/*
 * Logic is not inverted
 */
void setPumpSpeed(int speed){
    TXCANA_ATMega_Data[1] = pump_enable | (speed<<1);
}

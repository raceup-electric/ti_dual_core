#ifndef GPIO_MANAGEMENT_H_
#define GPIO_MANAGEMENT_H_

#include "F28x_Project.h"
#include "global_definitions.h"
#include "can_management.h"


extern Uint16 Air1_State;
extern Uint16 Air2_State;
extern Uint16 Imd_State;
extern Uint16 Bms_State;
extern Uint16 Sdc1_State;
extern Uint16 Sdc2_State;
extern Uint16 Sdc3_State;
extern Uint16 Sdc4_State;
extern Uint16 Sdc5_State;
extern Uint16 Sdc6_State;

extern unsigned char fan_enable;
extern unsigned char pump_enable;


void GPIOSetup();
void updateGPIOState();

#endif

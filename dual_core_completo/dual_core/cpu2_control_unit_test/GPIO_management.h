#ifndef GPIO_MANAGEMENT_H_
#define GPIO_MANAGEMENT_H_

#include "F28x_Project.h"
#include "global_definitions.h"


extern bool Imd_State;
extern bool Bms_State;
extern bool Sdc1_State;
extern bool Sdc2_State;
extern bool Sdc3_State;
extern bool Sdc4_State;
extern bool Sdc5_State;
extern bool Sdc6_State;

void GPIOSetup();

#endif

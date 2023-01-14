/*
 * epwm_management.h
 *
 *  Created on: Jan 29, 2022
 *      Author: Xhemali
 *      email: xhemali.sheshori1@gmail.com
 */

#ifndef EPWM_MANAGEMENT_H_
#define EPWM_MANAGEMENT_H_

#include "F28x_Project.h"
//#include "F2837xD_device.h"
//#include "F2837xD_Examples.h"
#include "global_definitions.h"
#include "can_management.h"

#define A   1
#define B   2


extern unsigned char epwm4B;
extern unsigned char epwm5A;
extern unsigned char epwm5B;
extern unsigned char epwm6A;


//
// prototypes
//

void initEPWM4();
void initEPWM5();
void initEPWM6();


void epwmSetup();

//void setDutyCycle(Uint32 base, Uint16 module, int perc);


// utils

Uint16 convertPercent(int perc); //passa da percentuale (0-100) a parametro epwm

void setFanSpeed(int fan, int speed);

void setPumpSpeed(int pump, int speed);


#endif /* EPWM_MANAGEMENT_H_ */

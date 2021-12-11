#ifndef EPWM_MANAGEMENT_H_
#define EPWM_MANAGEMENT_H_


#define A   1
#define B   2


//
// includes
//
#include "global_definitions.h"
#include "driverlib.h"
#include "device.h"
#include "epwm.h"
#include "interrupt.h"

//
// prototypes
//
void initEPWM(uint32_t base);

void epwmSetup();

void setDutyCycle(uint32_t base, uint16_t module, int perc);


// utils

uint16_t convertPercent(int perc); //passa da percentuale (0-100) a parametro epwm

void setFanSpeed(int fan, int speed);

void setPumpSpeed(int pump, int speed);

#endif

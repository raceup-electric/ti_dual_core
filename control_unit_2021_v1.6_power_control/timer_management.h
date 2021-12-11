#ifndef TIMER_MANAGEMENT_H_
#define TIMER_MANAGEMENT_H_

//
// includes
//
#include "gpio.h"
#include "device.h"
#include "can_management.h"
#include "driver_input.h"
#include "torque_management.h"
#include "car_management.h"
#include "motor_management.h"
#include "power_controller.h"
#include "epwm_management.h"
#include "adc_management.h"
#include "global_definitions.h"
#include "utils.h"
#include "dac_management.h"

//
// variables
//
extern volatile uint32_t txID;
extern volatile uint32_t rxID;
extern uint16_t rxMsg[8];
extern uint16_t txMsg[8];
extern volatile uint16_t cpuTimer0IntCount;
extern volatile uint16_t cpuTimer1IntCount;
extern volatile uint16_t cpuTimer2IntCount;
extern volatile uint32_t pinValue;
extern volatile int setupOk;

extern bool checkPower;

extern struct StatStruct stat;
extern struct AllData dts;
extern uint8_t var;


//
// prototypes
//
void timerSetup();

void initCPUTimers(void);

void configCPUTimer(uint32_t cpuTimer, float freq, float period);

__interrupt void cpuTimer0ISR(void);

__interrupt void cpuTimer1ISR(void);

__interrupt void cpuTimer2ISR(void);

#endif

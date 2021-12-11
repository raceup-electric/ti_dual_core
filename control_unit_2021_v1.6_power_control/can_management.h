#ifndef CAN_MANAGEMENT_H_
#define CAN_MANAGEMENT_H_

//
// includes
//
#include "global_definitions.h"
#include "gpio.h"
#include "device.h"
#include "timer_management.h"
#include "motor_management.h"
#include "can.h"
#include "car_management.h"
#include "inc/hw_can.h"
#include "adc_management.h"

//
// const
//

//
// variables
//
extern volatile uint32_t errorFlag;
extern volatile uint32_t rxAMsgCount;
extern volatile uint32_t rxBMsgCount;

extern int errorFrameCounterB;
extern int errorFrameCounterA;

extern uint8_t RX_A_temp[8];
extern bool temp_warning;

extern int driving_configuration;
extern bool powerOK;
extern uint8_t powersetup[8];

//
// prototypes
//
void canSetup();

__interrupt void canISR_B(void);

__interrupt void canISR_A(void);

uint32_t getMessageID(uint32_t base, uint32_t objID);

#endif

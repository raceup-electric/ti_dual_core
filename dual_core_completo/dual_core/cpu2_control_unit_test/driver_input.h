#ifndef DRIVER_INPUT_H_
#define DRIVER_INPUT_H_

//
// include
//
#include <math.h>
#include "utils.h"
#include "adc_management.h"
#include "global_definitions.h"

//
// defines
//


// acc1
#define ACC1_LOW_TH    2800
#define ACC1_HIGH_TH   3900
#define ACC1_INPUT_RANGE (ACC1_HIGH_TH - ACC1_LOW_TH)

// acc2
#define ACC2_LOW_TH    2000
#define ACC2_HIGH_TH   3150
#define ACC2_INPUT_RANGE (ACC2_HIGH_TH - ACC2_LOW_TH)

// acc
#define ACC1_DISC_THRES 100  //ABSOLUTE VAL
#define ACC2_DISC_THRES 100  //ABSOLUTE VAL
#define ACC_IMPL_THRES 10 // implausibility threshold 10%

// brake
#define BRK_LOW_TH    2050
#define BRK_HIGH_TH   2700
#define BRK_INPUT_RANGE (BRK_HIGH_TH-BRK_LOW_TH)

#define BRK_DISC_THRES 200  //ABSOLUTE VAL


// steering
#define STZ_LOW_TH 1700
#define STZ_HIGH_TH 3000

#define IMPL_LIMIT 5

#define THROTTLE_IMPL_THRESHOLD     35      //% of throttle
#define BRAKE_IMPL_THRESHOLD        30      //% of brake

//
// variables
//
extern bool brk_disconnected;
extern const int filterValCount;
extern const int filterDiscardCount;
extern int throttles[];
extern int brakes[];
extern int steerings[];

extern int actualVelocityRPM;
extern float actualVelocityKMH;
extern int brake;
extern int steering;
extern int throttle;
extern uint16_t value;
extern float AccPot1;
extern float AccPot2;
extern float BrkPot;

//
// prototypes
//
int Read_throttle();

int Read_brake(int);

int Read_steering(void);

void readThrottleBrakeSteering();

#endif

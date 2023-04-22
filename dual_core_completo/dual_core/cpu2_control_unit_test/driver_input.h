#ifndef DRIVER_INPUT_H_
#define DRIVER_INPUT_H_

#include <math.h>
#include "utils.h"
#include "adc_management.h"
#include "global_definitions.h"


/*
 * Those variables are fundamental for pedal calibration.
 * The calibration method is the following:
 *      for every potentiometer read the value (from 0 to 4095) at rest and at the maximum
 *      to set the low threshold add 30/40 to the real value
 *      to set the high threshold remove 20/30 to the real value
 *      THEN ALWAYS VERIFY IT IS WORKING RIGHT
 */

// acc1
#define ACC1_LOW_TH_INITIAL    2800
#define ACC1_HIGH_TH_INITIAL   3900
#define ACC1_INPUT_RANGE (pedals_log.acc1_high_calibration - pedals_log.acc1_low_calibration)

// acc2
#define ACC2_LOW_TH_INITIAL    2000
#define ACC2_HIGH_TH_INITIAL   3150
#define ACC2_INPUT_RANGE (pedals_log.acc2_high_calibration - pedals_log.acc2_low_calibration)

// acc
#define ACC1_DISC_THRES 100  //ABSOLUTE VAL
#define ACC2_DISC_THRES 100  //ABSOLUTE VAL
#define ACC_IMPL_THRES 10 // implausibility threshold 10%

// brake
#define BRK_LOW_TH_INITIAL    2050
#define BRK_HIGH_TH_INITIAL   2520
#define BRK_INPUT_RANGE (pedals_log.brk_high_calibration-pedals_log.brk_low_calibration)

#define BRK_DISC_THRES 200  //ABSOLUTE VAL


// steering
#define STZ_LOW_TH 1700
#define STZ_HIGH_TH 3000

#define IMPL_LIMIT 5

#define THROTTLE_IMPL_THRESHOLD     25      //% of throttle
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

extern struct Pedals_Log pedals_log;

//
// prototypes
//

void setup_intialValue_pedals();

int Read_throttle();

int Read_brake(int);

int Read_steering(void);

void readThrottleBrakeSteering();

#endif

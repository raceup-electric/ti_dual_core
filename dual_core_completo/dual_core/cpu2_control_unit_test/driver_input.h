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
#define ACC1_LOW_TH_INITIAL    2630
#define ACC1_HIGH_TH_INITIAL   3830

// acc2
#define ACC2_LOW_TH_INITIAL    1910
#define ACC2_HIGH_TH_INITIAL   3170

// acc
#define ACC1_DISC_THRES 100  //ABSOLUTE VAL
#define ACC2_DISC_THRES 100  //ABSOLUTE VAL
#define ACC_IMPL_THRES 10 // implausibility threshold 10%

// brake
#define BRK_LOW_TH_INITIAL    2170
#define BRK_HIGH_TH_INITIAL   2450

#define BRK_DISC_THRES 200  //ABSOLUTE VAL

#define INPUT_RANGE(x, y) (x-y)


// steering
#define STZ_LOW_TH 480
#define STZ_HIGH_TH 1320

#define IMPL_LIMIT 5

#define THROTTLE_IMPL_THRESHOLD     25      //% of throttle
#define BRAKE_IMPL_THRESHOLD        15      //% of brake

//
// variables
//
extern bool brk_disconnected;
extern const int filterValCount;
extern const int filterDiscardCount;
extern int throttles[];
extern int brakes[];
extern int steerings[];

extern double w_angles[4];
extern double delta_steer[2];

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

void wheels_angles();

#endif

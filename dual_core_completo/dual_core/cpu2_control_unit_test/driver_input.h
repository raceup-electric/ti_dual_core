#ifndef DRIVER_INPUT_H_
#define DRIVER_INPUT_H_

#include <math.h>
#include "utils.h"
#include "adc_management.h"
#include "car_management.h"
#include "global_definitions.h"

/*
 * Those variables are fundamental for pedal calibration.
 * The calibration method is the following:
 *      for every potentiometer read the value (from 0 to 4095) at rest and at the maximum
 *      to set the low threshold add 30/40 to the real value
 *      to set the high threshold remove 20/30 to the real value
 *      THEN ALWAYS VERIFY IT IS WORKING RIGHT
 */

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
extern float AccPot1;
extern float AccPot2;
extern float BrkPot;

extern struct Pedals_Log pedals_log;

//
// prototypes
//

void readThrottleBrakeSteering();

void wheels_angles();

#endif

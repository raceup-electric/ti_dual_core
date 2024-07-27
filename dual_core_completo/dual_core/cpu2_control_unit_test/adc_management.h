#ifndef ADC_MANAGEMENT_H_
#define ADC_MANAGEMENT_H_

//
// includes
//
#include "F28x_Project.h"
#include "global_definitions.h"
#include <math.h>


// #SOC  |  GPIO     |  PIN    |   FUNZIONE      |       SENSORE
// A
// SOC0 --> ADCINA0 --> PIN30 --> Acc2
// SOC1 --> ADCINA1 --> PIN70 --> Free
// SOC2 --> ADCINA2 --> PIN29 --> Acc1
// SOC3 --> ADCINA3 --> PIN26 --> BrakePress1 (Front)
// SOC4 --> ADCINA4 --> PIN69 --> Not Connected
// SOC5 --> ADCINA5 --> PIN66 --> BrakePress2 (Rear)
// C
// SOC9 --> ADCINC4 --> PIN67 --> CurrSens

extern int brakePress1;
extern int brakePress2;


//
// prototypes
//
void adcSetup(void); // setup degli adc e dei soc

void readAllADC(void);

void readADC_Bank(int num_bank);

float getVoltage(Uint16 digital); // scala la tensione (0-3)

#endif

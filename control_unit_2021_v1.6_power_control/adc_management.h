#ifndef ADC_MANAGEMENT_H_
#define ADC_MANAGEMENT_H_

#define TEMP_TYRE_FRONT_R   0
#define TEMP_TYRE_FRONT_L   1
#define BRAKE_CLEAN         2
#define SUSP_BACK_R         3
#define SUSP_FRONT_L        4
#define TEMP_RAD_OUT        5
#define STEERING            6
#define TEMP_TYRE_BACK_L    7
#define BRAKE_PRS_BACK      8
#define TEMP_RAD_IN         9
#define ACC_1               10
#define TEMP_TYRE_BACK_R    11
#define SUSP_BACK_L         12
#define ACC_2               13
#define SUSP_FRONT_R        14


    //#SOC  |  GPIO     |  PIN    |   FUNZIONE      |       SENSORE
    //A
    //SOC0 --> ADCINA0 --> PIN30 --> TempTyreFrontR     --> ZTP-135SR
    //SOC1 --> ADCINA2 --> PIN29 --> TempTyreFrontL     --> ZTP-135SR
    //SOC2 --> ADCINA3 --> PIN26 --> BrakeClean         --> Aviorace DIA9,5-75
    //SOC3 --> ADCINA4 --> PIN69 --> SuspBackR          --> Aviorace DIA9,5-75
    //SOC4 --> ADCINA5 --> PIN66 --> SuspFrontL         --> Aviorace DIA9,5-75
    //B
    //SOC5 --> ADCINB2 --> PIN28 --> TempRadOut         --> Aviorace PT1000
    //SOC6 --> ADCINB3 --> PIN25 --> Steering           --> Aviorace AR 006-10
    //SOC7 --> ADCINB4 --> PIN68 --> TempTyreBackL      --> ZTP-135SR
    //SOC8 --> ADCINB5 --> PIN65 --> BrakePressureBack  --> Aviorace SP100
    //C
    //SOC9 --> ADCINC2 --> PIN27 --> TempRadIN          --> Aviorace PT1000
    //SOC10--> ADCINC3 --> PIN24 --> Acc1               --> Aviorace DIA9,5-75
    //SOC11--> ADCINC4 --> PIN67 --> TempTyreBackR      --> ZTP-135SR
    //SOC12--> ADCINC5 --> PIN64 --> SuspBackL          --> Aviorace DIA9,5-75
    //
    //SOC13--> ADCIN14 --> PIN23 --> Acc2               --> Aviorace DIA9,5-75
    //SOC14--> ADCIN15 --> PIN63 --> SuspFrontR         --> Aviorace DIA9,5-75

//
// includes
//
#include "global_definitions.h"
#include "adc.h"
#include "device.h"
#include <math.h>

//
// prototypes
//
void adcSetup();                        //setup degli adc e dei soc

uint16_t readADC(int numAdc);           //legge la tensione dell'adc (0-14)

uint8_t getTempAvPT1000(uint16_t digital);  //converte la lettura digitale in temperatura (°C) per il sensore AvioracePT1000

uint8_t getTempZTP135SR(uint16_t digital);  //converte la lettura digitale in temperatura (°C) per il sensore ZTP-135SR

uint8_t getPressAvSP100(uint16_t digital);  //converte la lettura digitale in pressione (bar) per il sensore Aviorace SP100

float getVoltage(uint16_t digital);     //scala la tensione (0-3)


#endif

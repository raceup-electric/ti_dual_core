#ifndef ADC_MANAGEMENT_H_
#define ADC_MANAGEMENT_H_


//
// includes
//
#include "F28x_Project.h"
#include "global_definitions.h"
#include <math.h>

    //NUOVI VERIFICARE CON BALDO

    //#SOC  |  GPIO     |  PIN    |   FUNZIONE      |       SENSORE
    //A
    //SOC0 --> ADCINA0 --> PIN30 --> Acc2
    //SOC1 --> ADCINA1 --> PIN70 --> CurrSens
    //SOC2 --> ADCINA2 --> PIN29 --> Acc1
    //SOC3 --> ADCINA3 --> PIN26 --> BrakeClean
    //SOC4 --> ADCINA4 --> PIN69 --> BrakePressure
    //SOC? --> ADCINA5 --> PIN66 --> free
    //SOC5 --> ADCIN14 --> PIN23 --> Steering
    //B
    //SOC6 --> ADCINB2 --> PIN28 --> TempRadOutL
    //SOC7 --> ADCINB3 --> PIN25 --> TempRadOutRC
    //SOC? --> ADCINB5 --> PIN65 --> free
    //C
    //SOC8 --> ADCINC2 --> PIN27 --> TempRadINL
    //SOC9 --> ADCINC3 --> PIN24 --> TempRadINR


extern Uint16 Acc2_temp;
extern Uint16 CurrSens_temp;
extern Uint16 Acc1_temp;
extern Uint16 BrakeClean_temp;
extern Uint16 BrakePress_temp;
extern Uint16 Steering_temp;
extern Uint16 TempRadOutLC_temp;
extern Uint16 TempRadOutRC_temp;
extern Uint16 TempRadInLC_temp;
extern Uint16 TempRadInRC_temp;


//
// prototypes
//
void adcSetup(void);                        //setup degli adc e dei soc

void readAllADC(void);

void readADC_Bank(int num_bank);



Uint16 getTempAvPT1000(Uint16 digital);  //converte la lettura digitale in temperatura (°C) per il sensore AvioracePT1000

Uint16 getTempZTP135SR(Uint16 digital);  //converte la lettura digitale in temperatura (°C) per il sensore ZTP-135SR

int getPressAvSP100(Uint16 digital);  //converte la lettura digitale in pressione (bar) per il sensore Aviorace SP100

float getVoltage(Uint16 digital);     //scala la tensione (0-3)

#endif

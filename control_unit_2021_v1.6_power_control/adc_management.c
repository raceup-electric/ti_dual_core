#include "adc_management.h"

void adcSetup()
{

    //
    // Configure and power up ADCs A, B
    //
    //

    // Set ADCCLK divider to /4
    //
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);
    ADC_setPrescaler(ADCB_BASE, ADC_CLK_DIV_4_0);
    ADC_setPrescaler(ADCC_BASE, ADC_CLK_DIV_4_0);
    ADC_setPrescaler(ADCD_BASE, ADC_CLK_DIV_4_0);

    //
    // Set resolution and signal mode and load
    // corresponding trims.
    //
    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    ADC_setMode(ADCB_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    ADC_setMode(ADCC_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    ADC_setMode(ADCD_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);
    ADC_setInterruptPulseMode(ADCB_BASE, ADC_PULSE_END_OF_CONV);
    ADC_setInterruptPulseMode(ADCC_BASE, ADC_PULSE_END_OF_CONV);
    ADC_setInterruptPulseMode(ADCD_BASE, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADCs and then delay for 1 ms
    //
    ADC_enableConverter(ADCA_BASE);
    ADC_enableConverter(ADCB_BASE);
    ADC_enableConverter(ADCC_BASE);
    ADC_enableConverter(ADCD_BASE);

    DEVICE_DELAY_US(1000);

    //#SOC  |  GPIO     |  PIN    |  FUNZIONE      |       SENSORE
    //A
    //SOC0 --> ADCINA0 --> PIN30 --> TempBackR          --> Aviorace PT1000
    //SOC1 --> ADCINA2 --> PIN29 --> TempTyreFrontL     --> ZTP-135SR
    //SOC2 --> ADCINA3 --> PIN26 --> BrakeClean         --> Aviorace DIA9,5-75
    //SOC3 --> ADCINA4 --> PIN69 --> SuspBackR          --> Aviorace DIA9,5-75
    //SOC4 --> ADCINA5 --> PIN66 --> SuspFrontL         --> Aviorace DIA9,5-75
    //B
    //SOC5 --> ADCINB2 --> PIN28 --> TempTyreFrontR     --> ZTP-135SR
    //SOC6 --> ADCINB3 --> PIN25 --> Steering           --> Aviorace AR 006-10
    //SOC7 --> ADCINB4 --> PIN68 --> TempTyreBackL      --> ZTP-135SR
    //SOC8 --> ADCINB5 --> PIN65 --> BrakePressureBack  --> Aviorace SP100
    //C
    //SOC9 --> ADCINC2 --> PIN27 --> TempBackL          --> Aviorace PT1000
    //SOC10--> ADCINC3 --> PIN24 --> Acc1               --> Aviorace DIA9,5-75
    //SOC11--> ADCINC4 --> PIN67 --> TempTyreBackR      --> ZTP-135SR
    //SOC12--> ADCINC5 --> PIN64 --> SuspBackL          --> Aviorace DIA9,5-75
    //
    //SOC13--> ADCIN14 --> PIN23 --> Acc2               --> Aviorace DIA9,5-75
    //SOC14--> ADCIN15 --> PIN63 --> SuspFrontR         --> Aviorace DIA9,5-75



    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN0, ACQPS);

    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN2, ACQPS);

    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN3, ACQPS);

    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN4, ACQPS);

    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN5, ACQPS);

    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN2, ACQPS);

    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN3, ACQPS);

    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN4, ACQPS);

    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER8, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN5, ACQPS);

    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER9, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN2, ACQPS);

    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN3, ACQPS);

    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER11, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN4, ACQPS);

    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER12, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN5, ACQPS);

    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER13, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN14, ACQPS);

    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER14, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN15, ACQPS);

    //
    // Set SOC1 to set the interrupt 1 flag. Enable the interrupt and make
    // sure its flag is cleared.
    //
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER2);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER3);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER4);

    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER2);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER3);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER4);

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4);

    ADC_setInterruptSource(ADCB_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER5);
    ADC_setInterruptSource(ADCB_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER6);
    ADC_setInterruptSource(ADCB_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER7);
    ADC_setInterruptSource(ADCB_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER8);

    ADC_enableInterrupt(ADCB_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCB_BASE, ADC_INT_NUMBER2);
    ADC_enableInterrupt(ADCB_BASE, ADC_INT_NUMBER3);
    ADC_enableInterrupt(ADCB_BASE, ADC_INT_NUMBER4);

    ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER2);
    ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER3);
    ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER4);

    ADC_setInterruptSource(ADCC_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER9);
    ADC_setInterruptSource(ADCC_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER10);
    ADC_setInterruptSource(ADCC_BASE, ADC_INT_NUMBER3, ADC_SOC_NUMBER11);
    ADC_setInterruptSource(ADCC_BASE, ADC_INT_NUMBER4, ADC_SOC_NUMBER12);

    ADC_enableInterrupt(ADCC_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCC_BASE, ADC_INT_NUMBER2);
    ADC_enableInterrupt(ADCC_BASE, ADC_INT_NUMBER3);
    ADC_enableInterrupt(ADCC_BASE, ADC_INT_NUMBER4);

    ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER2);
    ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER3);
    ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER4);

    ADC_setInterruptSource(ADCD_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER13);
    ADC_setInterruptSource(ADCD_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER14);

    ADC_enableInterrupt(ADCD_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCD_BASE, ADC_INT_NUMBER2);

    ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER2);

}

uint16_t readADC(int numAdc)
{
    uint16_t adcResult = 0;

    switch (numAdc)
    {
    case 0:
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);
        //
        // Wait for ADCA to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1) == false)
        {
        }
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);

        break;

    case 1:
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER1);
        //
        // Wait for ADCA to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2) == false)
        {
        }
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);

        break;

    case 2:
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER2);
        //
        // Wait for ADCA to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3) == false)
        {
        }
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);

        break;

    case 3:
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER3);
        //
        // Wait for ADCA to complete, then acknowledge flag
        //
//        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4) == false)
//        {
//        }
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER3);

        break;

    case 4:
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER4);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4) == false)
        {
        }
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER4);

        break;

    case 5:
        ADC_forceSOC(ADCB_BASE, ADC_SOC_NUMBER5);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCB_BASE, ADC_INT_NUMBER1) == false)
        {
        }
        ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER5);

        break;

    case 6:
        ADC_forceSOC(ADCB_BASE, ADC_SOC_NUMBER6);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCB_BASE, ADC_INT_NUMBER2) == false)
        {
        }
        ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER2);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER6);

        break;

    case 7:
        ADC_forceSOC(ADCB_BASE, ADC_SOC_NUMBER7);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCB_BASE, ADC_INT_NUMBER3) == false)
        {
        }
        ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER3);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER7);

        break;

    case 8:
        ADC_forceSOC(ADCB_BASE, ADC_SOC_NUMBER8);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCB_BASE, ADC_INT_NUMBER4) == false)
        {
        }
        ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER4);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER8);

        break;

    case 9:
        ADC_forceSOC(ADCC_BASE, ADC_SOC_NUMBER9);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1) == false)
        {
        }
        ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER9);

        break;

    case 10:
        ADC_forceSOC(ADCC_BASE, ADC_SOC_NUMBER10);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCC_BASE, ADC_INT_NUMBER2) == false)
        {
        }
        ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER2);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER10);

        break;

    case 11:
        ADC_forceSOC(ADCC_BASE, ADC_SOC_NUMBER11);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCC_BASE, ADC_INT_NUMBER3) == false)
        {
        }
        ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER3);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER11);

        break;


    case 12:
        ADC_forceSOC(ADCC_BASE, ADC_SOC_NUMBER12);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCC_BASE, ADC_INT_NUMBER4) == false)
        {
        }
        ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER4);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER12);

        break;

    case 13:
        ADC_forceSOC(ADCD_BASE, ADC_SOC_NUMBER13);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1) == false)
        {
        }
        ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER13);

        break;

    case 14:
        ADC_forceSOC(ADCD_BASE, ADC_SOC_NUMBER14);
        //
        // Wait for ADCB to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCD_BASE, ADC_INT_NUMBER2) == false)
        {
        }
        ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER2);

        //
        // Store results
        //
        adcResult = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER14);

        break;

    default:
        adcResult = 0;
        break;
    }

    return adcResult;
}

float getVoltage(uint16_t digital){
    return ((float)(digital))*3/4095;
}


uint8_t getTempAvPT1000(uint16_t digital)
{
    float vin = getVoltage(digital);
    float aux = (vin*1000.0f)/(3.3f-vin);
    return (uint8_t) ((0.263f*aux)-263.168f);
}


uint8_t getTempZTP135SR(uint16_t digital){
    float vin = getVoltage(digital);
    float aux = vin/(3.3f-vin);
    float tempK = (298.15f*3960)/(3960+(298.15f*log(aux))); //#include <math.h>
    return (uint8_t)(tempK - 273.15f);
}

uint8_t getPressAvSP100(uint16_t digital) {return 0;}


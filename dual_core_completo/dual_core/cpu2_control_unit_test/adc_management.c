#include "adc_management.h"


void adcSetup()
{
    EALLOW;
    CpuSysRegs.PCLKCR13.bit.ADC_A = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_B = 1;
    CpuSysRegs.PCLKCR13.bit.ADC_C = 1;
    EDIS;

    //
    // Configure and power up ADCs A, B, C, D
    //
    //
    EALLOW;
    // Set ADCCLK divider to /4
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4

    //
    // Set resolution and signal mode and load
    // corresponding trims.
    //
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //
    // Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    // Power up the ADCs and then delay for 1 ms
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    DELAY_US(1000);
    EDIS;

    EALLOW;

    //ADCA

    //ADCINA0
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = ACQPS_;

    //ADCINA1
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 1;
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = ACQPS_;

    //ADCINA2
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 2;
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = ACQPS_;

    //ADCINA3
    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 3;
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = ACQPS_;

    //ADCINA4
    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = ACQPS_;

    //ADCIN14
    AdcaRegs.ADCSOC5CTL.bit.CHSEL = 14;
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = ACQPS_;

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 5;
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared


    //ADCB

    //ADCINB2
    AdcbRegs.ADCSOC6CTL.bit.CHSEL = 2;
    AdcbRegs.ADCSOC6CTL.bit.ACQPS = ACQPS_;

    //ADCINB3
    AdcbRegs.ADCSOC7CTL.bit.CHSEL = 3;
    AdcbRegs.ADCSOC7CTL.bit.ACQPS = ACQPS_;

//    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 6;
//    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;
//    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    AdcbRegs.ADCINTSEL1N2.bit.INT2SEL = 7;
    AdcbRegs.ADCINTSEL1N2.bit.INT2E = 1;
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;


    //ADCC

    //ADCINC2
    AdccRegs.ADCSOC8CTL.bit.CHSEL = 2;
    AdccRegs.ADCSOC8CTL.bit.ACQPS = ACQPS_;

    //ADCINC3
    AdccRegs.ADCSOC9CTL.bit.CHSEL = 3;
    AdccRegs.ADCSOC9CTL.bit.ACQPS = ACQPS_;

//    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 8;
//    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;
//    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    AdccRegs.ADCINTSEL1N2.bit.INT2SEL = 9;
    AdccRegs.ADCINTSEL1N2.bit.INT2E = 1;
    AdccRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;

}

void readAllADC()
{
    readADC_Bank(1);
    readADC_Bank(2);
    readADC_Bank(3);
}

void readADC_Bank(int num_bank)
{
    switch (num_bank)
    {
    case 1:
        AdcaRegs.ADCSOCFRC1.all = 0x003F; //SOC0 and SOC5

        while(AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0);
                AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

        Acc2_temp = AdcaResultRegs.ADCRESULT0;    //acc2 temp
        CurrSens_temp = AdcaResultRegs.ADCRESULT1;    //curr sens
        Acc1_temp = AdcaResultRegs.ADCRESULT2;    //acc1 temp
        BrakeClean_temp = AdcaResultRegs.ADCRESULT3;    //brakeclean
        BrakePress_temp = AdcaResultRegs.ADCRESULT4;    //brake press
        Steering_temp = AdcaResultRegs.ADCRESULT5;

    case 2:
        AdcbRegs.ADCSOCFRC1.all = 0x00C0; //SOC6 and SOC7

//        while(AdcbRegs.ADCINTFLG.bit.ADCINT1 == 0);
//                AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

        while(AdcbRegs.ADCINTFLG.bit.ADCINT2 == 0);
                AdcbRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;

        TempRadOutLC_temp = AdcbResultRegs.ADCRESULT6;    //rad out lc
        TempRadOutRC_temp = AdcbResultRegs.ADCRESULT7;    //rad out rc
    case 3:
        AdccRegs.ADCSOCFRC1.all = 0x0300; //SOC8 and SOC9

//        while(AdccRegs.ADCINTFLG.bit.ADCINT1 == 0);
//        AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

        while(AdccRegs.ADCINTFLG.bit.ADCINT2 == 0);
        AdccRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;

        TempRadInLC_temp = AdccResultRegs.ADCRESULT8;    //rad in lc
        TempRadInRC_temp = AdccResultRegs.ADCRESULT9;    //rad in rc
    }
}

Uint16 readADC(int numAdc)
{
//    uint16_t adcResult = 0;
//
//    switch (numAdc)
//    {
//    case TEMP_BACK_R:
//        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);
//        //
//        // Wait for ADCA to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
//
//        break;
//
//    case TEMP_TYRE_FRONT_L:
//        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER1);
//        //
//        // Wait for ADCA to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);
//
//        break;
//
//    case BRAKE_CLEAN:
//        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER2);
//        //
//        // Wait for ADCA to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);
//
//        break;
//
//    case SUSP_BACK_R:
//        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER3);
//        //
//        // Wait for ADCA to complete, then acknowledge flag
//        //
////        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4) == false)
////        {
////        }
//        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER3);
//
//        break;
//
//    case SUSP_FRONT_L:
//        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER4);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER4);
//
//        break;
//
//    case TEMP_TYRE_FRONT_R:
//        ADC_forceSOC(ADCB_BASE, ADC_SOC_NUMBER5);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCB_BASE, ADC_INT_NUMBER1) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER1);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER5);
//
//        break;
//
//    case STEERING:
//        ADC_forceSOC(ADCB_BASE, ADC_SOC_NUMBER6);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCB_BASE, ADC_INT_NUMBER2) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER2);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER6);
//
//        break;
//
//    case TEMP_TYRE_BACK_L:
//        ADC_forceSOC(ADCB_BASE, ADC_SOC_NUMBER7);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCB_BASE, ADC_INT_NUMBER3) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER3);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER7);
//
//        break;
//
//    case BRAKE_PRS_BACK:
//        ADC_forceSOC(ADCB_BASE, ADC_SOC_NUMBER8);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCB_BASE, ADC_INT_NUMBER4) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER4);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER8);
//
//        break;
//
//    case TEMP_BACK_L:
//        ADC_forceSOC(ADCC_BASE, ADC_SOC_NUMBER9);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER9);
//
//        break;
//
//    case ACC_1:
//        ADC_forceSOC(ADCC_BASE, ADC_SOC_NUMBER10);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCC_BASE, ADC_INT_NUMBER2) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER2);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER10);
//
//        break;
//
//    case TEMP_TYRE_BACK_R:
//        ADC_forceSOC(ADCC_BASE, ADC_SOC_NUMBER11);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCC_BASE, ADC_INT_NUMBER3) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER3);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER11);
//
//        break;
//
//
//    case SUSP_BACK_L:
//        ADC_forceSOC(ADCC_BASE, ADC_SOC_NUMBER12);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCC_BASE, ADC_INT_NUMBER4) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER4);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER12);
//
//        break;
//
//    case ACC_2:
//        ADC_forceSOC(ADCD_BASE, ADC_SOC_NUMBER13);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER1);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER13);
//
//        break;
//
//    case SUSP_FRONT_R:
//        ADC_forceSOC(ADCD_BASE, ADC_SOC_NUMBER14);
//        //
//        // Wait for ADCB to complete, then acknowledge flag
//        //
//        while(ADC_getInterruptStatus(ADCD_BASE, ADC_INT_NUMBER2) == false)
//        {
//        }
//        ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER2);
//
//        //
//        // Store results
//        //
//        adcResult = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER14);
//
//        break;
//
//    default:
//        adcResult = 0;
//        break;
//    }
//
//    return adcResult;
return 0;
}

float getVoltage(uint16_t digital){
    return ((float)(digital))*3/4095;
}


Uint16 getTempAvPT1000(uint16_t digital)
{
    float vin = getVoltage(digital);
    float aux = (vin*1000.0f)/(3.3f-vin);
    return (Uint16) ((0.263f*aux)-263.168f);
}


Uint16 getTempZTP135SR(uint16_t digital){
    float vin = getVoltage(digital);
    float aux = vin/(3.3f-vin);
    float tempK = (298.15f*3960)/(3960+(298.15f*log(aux))); //#include <math.h>
    return (Uint16)(tempK - 273.15f);
}

Uint16 getPressAvSP100(uint16_t digital) {return 0;}


#include "adc_management.h"
#include "car_management.h"

/*
 * ADCs are grouped in banks. ADCs reading i triggered via software interrupt through the function readADC_Bank().
 * Every ADC is binded to a SOC.
 */
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
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; // set ADCCLK divider to /4
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; // set ADCCLK divider to /4
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; // set ADCCLK divider to /4

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

    // ADCA

    // ADCINA5
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 5;
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = ACQPS_;


    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // end of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   // enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // make sure INT1 flag is cleared

    // ADCC

    // ADCINC4
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 4;
    AdccRegs.ADCSOC0CTL.bit.ACQPS = ACQPS_;


    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // end of SOC0 will set INT2 flag
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;   // enable INT1 flag
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // clear INT1 flag
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
        AdcaRegs.ADCSOCFRC1.all = 0x0001; // SOC0

        while (AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0)
            ;
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
        brakePress2 = getSP150BrakePress(AdcaResultRegs.ADCRESULT0);
        break;
    case 2:
        break;
    case 3:
        AdccRegs.ADCSOCFRC1.all = 0x0001; // SOC0

        while (AdccRegs.ADCINTFLG.bit.ADCINT1 == 0)
            ;
        AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
        brakePress1 = getSP100BrakePress(AdccResultRegs.ADCRESULT0);
        break;
    }
}

/*
 * Old functions to convert voltage values.
 */
float getVoltage(Uint16 digital)
{
    return ((float)(digital)) * 3 / 4095;
}

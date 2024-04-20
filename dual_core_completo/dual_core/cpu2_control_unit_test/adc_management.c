#include "adc_management.h"

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

    // ADCINA0
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = ACQPS_;

    // ADCINA1
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 1;
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = ACQPS_;

    // ADCINA2
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 2;
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = ACQPS_;

    // ADCINA3
    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 3;
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = ACQPS_;

    // ADCINA4
    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;
    AdcaRegs.ADCSOC4CTL.bit.ACQPS = ACQPS_;

    // ADCIN14
    AdcaRegs.ADCSOC5CTL.bit.CHSEL = 14;
    AdcaRegs.ADCSOC5CTL.bit.ACQPS = ACQPS_;

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 5; // end of SOC5 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   // enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // make sure INT1 flag is cleared

    // ADCB

    // ADCINB2
    AdcbRegs.ADCSOC6CTL.bit.CHSEL = 2;
    AdcbRegs.ADCSOC6CTL.bit.ACQPS = ACQPS_;

    // ADCINB3
    AdcbRegs.ADCSOC7CTL.bit.CHSEL = 3;
    AdcbRegs.ADCSOC7CTL.bit.ACQPS = ACQPS_;

    //    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 6;
    //    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;
    //    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    AdcbRegs.ADCINTSEL1N2.bit.INT2SEL = 7; // end of SOC7 will set INT2 flag
    AdcbRegs.ADCINTSEL1N2.bit.INT2E = 1;
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;

    // ADCC

    // ADCINC2
    AdccRegs.ADCSOC8CTL.bit.CHSEL = 2;
    AdccRegs.ADCSOC8CTL.bit.ACQPS = ACQPS_;

    // ADCINC3
    AdccRegs.ADCSOC9CTL.bit.CHSEL = 3;
    AdccRegs.ADCSOC9CTL.bit.ACQPS = ACQPS_;

    //    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 8;
    //    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;
    //    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    AdccRegs.ADCINTSEL1N2.bit.INT2SEL = 9; // end of SOC7 will set INT2 flag
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
        AdcaRegs.ADCSOCFRC1.all = 0x003F; // SOC0 and SOC5

        while (AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0)
            ;
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
        break;

    case 2:
        AdcbRegs.ADCSOCFRC1.all = 0x00C0; // SOC6 and SOC7

        //        while(AdcbRegs.ADCINTFLG.bit.ADCINT1 == 0);
        //                AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

        while (AdcbRegs.ADCINTFLG.bit.ADCINT2 == 0)
            ;
        AdcbRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;

        break;
    case 3:
        AdccRegs.ADCSOCFRC1.all = 0x0300; // SOC8 and SOC9

        //        while(AdccRegs.ADCINTFLG.bit.ADCINT1 == 0);
        //        AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

        while (AdccRegs.ADCINTFLG.bit.ADCINT2 == 0)
            ;
        AdccRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;
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

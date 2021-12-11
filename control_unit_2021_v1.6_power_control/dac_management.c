#include "dac_management.h"

//
// Configure DAC - Setup the reference voltage and output value for the DAC
//
void
setupDAC(void)
{
    //
    // Set VDAC as the DAC reference voltage.
    // Edit here to use ADC VREF as the reference voltage.
    //
    DAC_setReferenceVoltage(DACB_BASE, DAC_REF_ADC_VREFHI);

    //
    // Enable the DAC output
    //
    DAC_enableOutput(DACB_BASE);

    //
    // Set the DAC shadow output to 0
    //
    DAC_setShadowValue(DACB_BASE, 0);

    //
    // Delay for buffered DAC to power up
    //
    DEVICE_DELAY_US(10);
}

void setDACValue(uint16_t value)
{
    DAC_setShadowValue(DACB_BASE, value);
}

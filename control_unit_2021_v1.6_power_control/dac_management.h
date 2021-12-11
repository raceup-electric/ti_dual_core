#ifndef DAC_MANAGEMENT_H_
#define DAC_MANAGEMENT_H_

#include "driverlib.h"
#include "device.h"

//prototypes
void setupDAC(void);

void setDACValue(uint16_t value);

#endif

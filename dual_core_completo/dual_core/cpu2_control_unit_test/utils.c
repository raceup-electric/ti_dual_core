#include "utils.h"

float convertBMSvoltage(Uint16 voltage){
  return 3000 + (1.2*voltage);
}

float convertBMStemp(Uint16 temp){
  return 27*(-1) + 0.2*temp;
}

float changeRange(float val, float currentMin, float currentMax, float newMin, float newMax) {
    float ratioX = (val - currentMin) / (currentMax - currentMin);  // 0 .. 1
    float newRange = ratioX * (newMax - newMin);  // new range between new min and new max
    return newMin + newRange;  // new min .. new max
}

Uint16 saturateUnsigned(Uint16 signal, Uint16 upperBound, Uint16 lowerBound)
{
    if (lowerBound >= upperBound)
        return 0;

    if (signal > upperBound)
        return upperBound;
    else if (signal < lowerBound)
        return lowerBound;
    else
        return signal;
}

float saturateFloat(float signal, float upperBound, float lowerBound)
{
    if (lowerBound >= upperBound)
        return 0;

    if (signal > upperBound)
        return upperBound;
    else if (signal < lowerBound)
        return lowerBound;
    else
        return signal;
}

float saturateInt(int signal, int upperBound, int lowerBound)
{
    if (lowerBound >= upperBound)
        return 0;

    if (signal > upperBound)
        return upperBound;
    else if (signal < lowerBound)
        return lowerBound;
    else
        return signal;
}

//turn on/off LED1 (blue led) every period*10 ms
void debugLight(int period)
{
//    if (cpuTimer0IntCount % period == 0)
//        GPIO_togglePin(RED_BLINK);
}

float uint32_to_float(Uint32 u)
{
    union
    {
        Uint32 u;
        float f;
    } temp;
    temp.u=u;

    return temp.f;
}

float torqueSetpointToNM(int setpoint)
{
    return (setpoint/1000.0)*M_N;
}

int NMtoTorqueSetpoint(float torqueNM)
{
    return (torqueNM/M_N)*1000;
}

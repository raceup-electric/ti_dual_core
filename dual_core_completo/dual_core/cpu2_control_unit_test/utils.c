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

void imu_calibration_1(float accelerations[3]){
    float norma = sqrt(pow(accelerations[0],2) + pow(accelerations[1],2)+pow(accelerations[2],2));
    int i;
        for (i = 0; i<3; i++){
            versz[i]=accelerations[i]/norma;
        }
}

void imu_calibration_2(float accelerations[3]){
    int i, j;
    float gi_z;
    for(i=0; i<3;i++){
        gi_z = gi_z + accelerations[i]*versz[i];
    }
    float gi_x[3];
    for(i=0; i<3; i++){
        gi_x[i] = accelerations[i] - gi_z * versz[i];
    }
    float norma = sqrt(pow(gi_x[0],2) + pow(gi_x[1],2)+pow(gi_x[2],2));
    for(i=0; i<3; i++){
            versx[i] = gi_x[i]/norma;
        }
    //prodotto vettoriale hard coded
    versy[0]=versz[1]*versx[2] - versz[2]*versx[1];
    versy[1]=versz[2]*versx[0] - versz[0]*versx[2];
    versy[2]=versz[0]*versx[1] - versz[1]*versx[0];

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
                if(i == 0){
                    V[i][j] = versx[j];
                }else if(i == 1){
                    V[i][j] = versy[j];
                }else if(i == 2){
                    V[i][j] = versz[j];
                }
        }
    }
}

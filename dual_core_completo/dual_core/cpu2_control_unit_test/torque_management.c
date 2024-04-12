#include "torque_management.h"


void readVelocity()
{
    actualVelocityRPM = readRPMVelocity();
    actualVelocityKMH = actualVelocityRPM * RPM_TO_KMH;  // average speed kph
}

float readRPMVelocity()
{
    float sum = 0.0;
    int i;
    for (i = 0; i < NUM_OF_MOTORS; i++) {
        sum += motorVal1[i].AMK_ActualVelocity;
    }

    float avg = sum / NUM_OF_MOTORS;
    return avg;
}

//torque_reg_IPM in uscita � POSITIVO
void regBrake()
{
    float sumrip = repFz[0] + repFz[1] + repFz[2] + repFz[3];
    int rpm = car_settings.max_speed;
    float rads = rpm*PI/30;

    float V_zero = batteryPackTension + RBATT * lem_current;
    float current_batterylimit = (600-V_zero)/(RBATT+0.1f);

    float current_limit = fminf(current_batterylimit, car_settings.max_regen_current);
    //float Pemax = (sendyne_voltage+RBATT*max_regen_current)*max_regen_current/ETA_INV; //sendyne_deprecated
    float Pemax = (V_zero+RBATT*current_limit)*current_limit/ETA_INV;

    float Pmot = 0;
    float a = 0;
    float b = 0;
    float c = 0;
    float Iq = 0, Id = 0;
    int mot;

    for(mot = 0; mot < 4; mot++)
    {
        Pmot = Pemax/sumrip*repFz[mot];
        float rade = rads*P;

        a = 3/2*(R*(1+1/pow(TALPHA, 2))+rade*(LD-LQ)/TALPHA);
        b = 3/2*rade*FLUX_MG;
        c = -Pmot;
        Iq = (-b+sqrt(pow(b, 2)-4*a*c))/(2*a);
        Id = Iq/TALPHA;

        float Ploss = 3/2*R*(pow(Id, 2)+pow(Iq, 2));
        float Pw = (Pmot+Ploss);

        Pw = Pw/SATURAZIONE;
        float T_max_an_IPM = Pw/rads;

        //T_lim = 21-0.000857*(rpm-13000); da matlab
        float T_lim = 21.0f - 0.000857*(fabsf(motorVal1[mot].AMK_ActualVelocity) - 13000.0f); //da riga 47
        T_lim=saturateFloat(T_lim,-car_settings.max_neg_torque,0.0f);

        if(T_max_an_IPM > T_lim)
            torque_reg_IPM[mot] = T_lim;
        else
            torque_reg_IPM[mot] = T_max_an_IPM;
//#ifdef NO_TORQUE_VECTORING
        //Sovrascrive il valore sia che ci sia o no TV
        negTorquesNM[mot] = -((brakeReq/100.0)*torque_reg_IPM[mot]);
//#endif
    }


}
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

void performancePack()
{
    int i;
    for(i=0; i<4; i++){
        AMK_TorqueLimitPositive[i] = MAX_POS_TORQUE;
        AMK_TorqueLimitNegative[i] = MAX_NEG_TORQUE;
    }

    th = throttleReq/100.0f;   //change range from 0-100 to 0-1
    brk = brakeReq/100.0f;     //change range from 0-100 to 0-1
    str = steering;
    ax = accelerations[X];  //m/s2
    ay = accelerations[Y];  //m/s2
    yaw_r = omegas[Z];      //rad/s

    for (i = 0; i < NUM_OF_MOTORS; i++)
            motorSpeeds[i] = motorVal1[i].AMK_ActualVelocity;

        saturationsAndConversions();

        FzCalculatorTV();
        speedCalculatorTV();

        float Torque_max[4];

        for(i = 0; i < NUM_OF_MOTORS; i++){
            Torque_max[i] = 21.0f - 0.000857*(fabsf(motorVal1[i].AMK_ActualVelocity) - 13000.0f);
        }

        for(i = 0; i < NUM_OF_MOTORS; i++){
            if (AMK_TorqueLimitPositive[i] > Torque_max[i]) AMK_TorqueLimitPositive[i] = Torque_max[i];
                if (AMK_TorqueLimitNegative[i] < -Torque_max[i]) AMK_TorqueLimitNegative[i] = -Torque_max[i];
        }


        for (i = 0; i < NUM_OF_MOTORS; i++)
            posTorqueCandidate[i][0] = AMK_TorqueLimitPositive[i];

        torqueVectoring();

        for (i = 0; i < NUM_OF_MOTORS; i++)
        {
            posTorquesNM[i] = fminf(posTorqueCandidate[i][0], posTorqueCandidate[i][1]);
            negTorquesNM[i] = negTorqueCandidate[i];
        }

}

void saturationsAndConversions()
{
    //Saturations
    ax = saturateFloat(ax, ACC_X_UPPER_BOUND, ACC_X_LOWER_BOUND);
    ay = saturateFloat(ay, ACC_Y_UPPER_BOUND, ACC_Y_LOWER_BOUND);
    str = saturateInt(str, STR_UPPER_BOUND, STR_LOWER_BOUND);
    yaw_r = saturateFloat(yaw_r, YAW_R_UPPER_BOUND, YAW_R_LOWER_BOUND);

    int i;
    for (i = 0; i < NUM_OF_MOTORS; i++)
        motorSpeeds[i] = saturateInt(motorSpeeds[i], MOTOR_SPEED_UPPER_BOUND, MOTOR_SPEED_LOWER_BOUND);

    steers[0] = str*K_DELTA;
    steers[1] = str*K_DELTA;
    steers[2] = 0;
    steers[3] = 0;

    //Conversions

    for (i = 0; i < NUM_OF_MOTORS; i++)
        motorSpeeds[i] = (motorSpeeds[i]*PI_FLOAT*TAU)/30;

}

void speedCalculatorTV()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        re[i] = R0 - (fz[i] * 3.016126E-6f);
    }

    float tmp = ((th + brk)*0.1f)+1;

    float steers_tmp[4];
    for (i = 0; i < 4; i++)
    {
        steers_tmp[i] = cosf(steers[i]);
    }

    float calc_tmp[4];
    for(i = 0; i < 4; i++)
    {
        calc_tmp[i] = re[i]*motorSpeeds[i];
        calc_tmp[i] = calc_tmp[i]/tmp;
        calc_tmp[i] = calc_tmp[i]/steers_tmp[i];
    }

    for (i = 0; i < 4; i++)
    {
        steers_tmp[i] = tanf(steers[i]);
        steers_tmp[i]*=((FZF*W)/FZR);
        steers_tmp[i]*=yaw_r;
    }

    float sum = 0;
    for (i = 0; i < 4; i++)
    {
        calc_tmp[i] = calc_tmp[i] - steers_tmp[i];
        sum+=calc_tmp[i];
    }

    speedTv = sum * 0.25;
}

void FzCalculatorTV()
{
    float tmp_x = (ax*MASS*Z_G)/(W*2);
    float tmp_yf = (ay*MASS*Z_G*K_F)/T_F;
    float tmp_yr = (ay*MASS*Z_G*K_R)/T_R;
    float tmp_u1 = speedTv*speedTv*0.25f*RHO*C_Z_A*((1-A_A)/W);
    float tmp_u2 = (speedTv*speedTv*0.25f*RHO*C_Z_A*A_A)/W;

    fz[0] = -tmp_x;
    fz[0]+= -tmp_yf;
    fz[0]+= FZF*G_ACC;
    fz[0]+= tmp_u1;

    fz[1] = -tmp_x;
    fz[1]+= tmp_yf;
    fz[1]+= FZF*G_ACC;
    fz[1]+= tmp_u1;

    fz[2] = tmp_x;
    fz[2]+= -tmp_yr;
    fz[2]+= FZR*G_ACC;
    fz[2]+= tmp_u2;

    fz[3] = tmp_x;
    fz[3]+= tmp_yr;
    fz[3]+= FZR*G_ACC;
    fz[3]+= tmp_u2;

    int i;
    for (i = 0; i < 4; i++)
        fz[i] = saturateFloat(fz[i], FZ_UPPER_BOUND, FZ_LOWER_BOUND);

}

void torqueVectoring()
{
   torqueRepartition();
   int i;
   for (i = 0; i < 4; i++)
   {
       posTorqueCandidate[i][1] = repFz[i]*th*4*AMK_TorqueLimitPositive[i];
       negTorqueCandidate[i] = repFz[i]*brk*4*AMK_TorqueLimitNegative[i];
   }

}

void torqueRepartition()
{
    //Sum of forces
    float fzSum = 0;
    int i;
    for (i = 0; i < 4; i++)
        fzSum+= fz[i];

    float fzSumDef = fzSum;
    //front repartition
    float repF = (fz[0] + fz[1])/fzSumDef;
    //Lateral front repartition
    repFz[0] = (fz[0]/(fz[0] + fz[1]))*repF;
    repFz[1] = (fz[1]/(fz[0] + fz[1]))*repF;

    fzSum = fzSum - (fz[0] + fz[1]);
    fzSum = fz[3]/fzSum;

    //Lateral rear repartition
    repFz[2] = (1 - fzSum)*(1-repF);
    repFz[3] = fzSum*(1-repF);




}

//torque_reg_IPM in uscita é POSITIVO
void regBrake()
{
    float sumrip = repFz[0] + repFz[1] + repFz[2] + repFz[3];
    int rpm = SPEED_LIMIT;
    float rads = rpm*PI/30;

    float V_zero = batteryPackTension + RBATT * lem_current;
    float current_batterylimit = (600-V_zero)/(RBATT+0.1f);

    float current_limit = fminf(current_batterylimit, max_regen_current);
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
        T_lim=saturateFloat(T_lim,-MAX_NEG_TORQUE,0.0f);

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


void onePedalDriving()
{
    float brake_point_limit = 35;

    if(throttleReq > brake_point_limit){
            throttleReq = ((throttleReq - brake_point_limit)*100)/(100-brake_point_limit);
            brakeReq = 0;

    }
    else if(throttleReq==0 && brake > 5){
        brakeReq = 100;
        velocityRef = 0;    //per setpoint AMK4
    }
    else{
        if(actualVelocityKMH > 5.f){

            brakeReq = (100 - throttleReq*100/brake_point_limit);
            throttleReq = 0;
            velocityRef = 0;    //per setpoint AMK4
        }
        else{
            //sotto i 35 con throttle e velocità < 5 --> brake when slow --> solo freno meccanico
            throttleReq = 0;
            brakeReq = 0;
        }

    }

}




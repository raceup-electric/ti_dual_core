#include "torque_management.h"

//Save of last state
float posTorqueNM_last[4] = {0, 0, 0 ,0};
float negTorqueNM_last[4] = {0, 0, 0 ,0};

float minTorquePos[4];

double vecErrorP_last[4] = {0,0,0,0};
double vecErrorM_last[4] = {0,0,0,0};

double errP_last[4] = {0, 0, 0, 0};
double errM_last[4] = {0, 0, 0, 0};


//---------------------------------------------------------
//
//Simplified version for initial testing
//

//---------------------------------------------------------
void SimplifiedTractionControl(double T){
    //Velocity estimation [use speedTv from TV instead of estimated velocity]
    double vx = speedTv;
    double vy = 0.f;

    //Riporto vx alle ruote
    double tmp1 = yaw_r*T_F/2;
    double tmp1a = vx-tmp1;
    double tmp1b = vx+tmp1;

    double tmp2 = yaw_r*T_R/2;
    double tmp2a = vx-tmp2;
    double tmp2b = vx+tmp2;

    double vec1[] = {tmp1a,tmp1b,tmp2a,tmp2b};

    //Riporto vy alle route
    double tmp3 = yaw_r*A;
    double tmp3a = vy+tmp3;

    double tmp4 = yaw_r*(-B);
    double tmp4a = -vy+tmp4;

    double vec2[] = {tmp3a,tmp3a,tmp4a,tmp4a};

    //Determino l'angolo delle gomme
    double temp_angle1[4];
    double temp_angle2[4];

    //Uso steers  che sono le w_angles
    temp_angle1[0] = cos(steers[0]);
    temp_angle1[1] = cos(steers[1]);
    temp_angle1[2] = cos(steers[2]);
    temp_angle1[3] = cos(steers[3]);

    temp_angle2[0] = sin(steers[0]);
    temp_angle2[1] = sin(steers[1]);
    temp_angle2[2] = sin(steers[2]);
    temp_angle2[3] = sin(steers[3]);

    //Moltiplico vettore per temp angles
    double x1[] = {0,0,0,0};
    mulvecElementWise(vec1, temp_angle1, x1, 1, 4);

    double x2[] = {0,0,0,0};
    mulvecElementWise(vec2, temp_angle2, x2, 1, 4);


    double result1[] = {0,0,0,0};
    add(x1,x2,result1,4);

    //Utilizzo di v_wheels
    double temp1[] = {0,0,0,0};
    double temp2[] = {0,0,0,0};

    mulscal(result1, 1+S_MAX, temp1, 1, 4);
    mulscal(result1, 1+S_MIN, temp2, 1, 4);

    double vecErrorP[] = {0,0,0,0};
    double vecErrorM[] = {0,0,0,0};

    //Calcolo v_wheels
    int i = 0;
    for(i = 0; i < NUM_OF_MOTORS; i++){
        v_wheels[i] = re[i]*motorSpeeds[i];
    }

    sub(v_wheels, temp1, vecErrorP, 4);
    sub(temp2, v_wheels, vecErrorM, 4);

    double errP[4];
    double errM[4];
    for(i = 0; i < NUM_OF_MOTORS; i++){
      errP[i] = max(vecErrorP[i],0);
      errM[i] = max(vecErrorM[i],0);
    }

      double vecError2P[4] = {0,0,0,0};
      double vecError2M[4] = {0,0,0,0};


      sub(vecErrorP, vecErrorP_last, vecError2P, 4);
      sub(vecErrorM, vecErrorM_last, vecError2M, 4);

      mulscal(vecError2P,1/T,vecError2P,1,4);
      mulscal(vecError2M,1/T,vecError2M,1,4);

     double err2P[4];
     double err2M[4];
     for(i = 0; i < NUM_OF_MOTORS; i++){
         err2P[i] = max(vecError2P[i], 0)*D_POS;
         err2M[i] = max(vecError2M[i], 0)*D_NEG;
     }

     double rP[4] = {0,0,0,0};
     double rM[4] = {0,0,0,0};

     for(i = 0; i < NUM_OF_MOTORS; i++){
         if(errP[i] != 0){
             rP[i] = 1.f;
         }
         if(errM[i] != 0){
             rM[i] = 1.f;
         }
     }
     double intermediateP[4] = {0,0,0,0};
     double intermediateM[4] = {0,0,0,0};
     add(errP_last, errP, intermediateP,4);
     add(errM_last, errM, intermediateM,4);

     mulvecElementWise(intermediateP, rP, intermediateP, 1, 4);
     mulscal(intermediateP,I_POS, intermediateP,1,4);

     mulvecElementWise(intermediateM, rM, intermediateM, 1, 4);
     mulscal(intermediateM,I_NEG, intermediateM,1,4);

     double val1Pos[4] = {0,0,0,0};
     double val1Neg[4] = {0,0,0,0};

     for(i = 0; i < NUM_OF_MOTORS; i++){
         val1Pos[i] = min(max_I_pos, intermediateP[i]);
         val1Neg[i] = min(max_I_neg, intermediateM[i]);
     }

     double resultPos[4] = {0,0,0,0};
     double resultNeg[4] = {0,0,0,0};

     for(i = 0; i < NUM_OF_MOTORS; i++){
         errP_last[i] = errP[i];
         errM_last[i] = errM[i];
     }


     mulscal(errP, P_POS,errP, 1, 4);
     mulscal(errM, P_NEG,errM, 1, 4);

     add(val1Pos, err2P, resultPos, 4);
     add(resultPos, errP, resultPos, 4);

     add(val1Neg, err2M, resultNeg, 4);
     add(resultNeg, errM, resultNeg, 4);

     for(i = 0; i < NUM_OF_MOTORS; i++){
         resultPos[i] = saturate(resultPos[i],0,1);
         resultNeg[i] = saturate(resultNeg[i], 0, 1);
     }

     for(i = 0; i < NUM_OF_MOTORS; i++){
         TC_pos[i] = 1 - resultPos[i];
         TC_neg[i] = 1 - resultNeg[i];
     }

      //int i = 0;
      for(i = 0; i<4; i++){

          vecErrorP_last[i] = vecErrorP[i];
          vecErrorM_last[i] = vecErrorM[i];

      }


}

/*void TractionControl(double T){

    velocity_estimation(T);

    double vx = speed_state[0];
    double vy = speed_state[1];


    double tmp1 = yaw_r*T_F/2;
    double tmp1a = vx-tmp1;
    double tmp1b = vx+tmp1;

    double tmp2 = yaw_r*T_R/2;
    double tmp2a = vx-tmp2;
    double tmp2b = vx+tmp2;

    double vec1[] = {tmp1a,tmp1b,tmp2a,tmp2b};


    double tmp3 = yaw_r*A;
    double tmp3a = vy+tmp3;

    double tmp4 = yaw_r*(-B);
    double tmp4a = -vy+tmp4;

    double vec2[] = {tmp3a,tmp3a,tmp4a,tmp4a};


    double temp_angle1[4];
    double temp_angle2[4];

    temp_angle1[0] = cos(w_angles[0]);
    temp_angle1[1] = cos(w_angles[1]);
    temp_angle1[2] = cos(w_angles[2]);
    temp_angle1[3] = cos(w_angles[3]);

    temp_angle2[0] = sin(w_angles[0]);
    temp_angle2[1] = sin(w_angles[1]);
    temp_angle2[2] = sin(w_angles[2]);
    temp_angle2[3] = sin(w_angles[3]);

    double x1[] = {0,0,0,0};
    mulvecElementWise(vec1, temp_angle1, x1, 1, 4);

    double x2[] = {0,0,0,0};
    mulvecElementWise(vec2, temp_angle2, x2, 1, 4);

    double result1[] = {0,0,0,0};
    add(x1,x2,result1,4);

    double temp1[] = {0,0,0,0};
    double temp2[] = {0,0,0,0};

    mulscal(result1, 1+S_MAX, temp1, 1, 4);
    mulscal(result1, 1+S_MIN, temp2, 1, 4);

    double vecErrorP[] = {0,0,0,0};
    double vecErrorM[] = {0,0,0,0};

    sub(v_wheels, temp1, vecErrorP, 4);
    sub(temp2, v_wheels, vecErrorM, 4);

    double errP = max(max_vect(vecErrorP,4),0);
    double errM = max(max_vect(vecErrorM,4),0);

    double vecError2P[4] = {0,0,0,0};
    double vecError2M[4] = {0,0,0,0};


    sub(vecErrorP, vecErrorP_last, vecError2P, 4);
    sub(vecErrorM, vecErrorM_last, vecError2M, 4);

    mulscal(vecError2P,1/T,vecError2P,1,4);
    mulscal(vecError2M,1/T,vecError2M,1,4);

    double err2P = max(max_vect(vecError2P,4),0);
    err2P = err2P*D_POS;

    double err2M = max(max_vect(vecError2M,4),0);
    err2M = err2M*D_NEG;

    double rP = 0;
    if(errP != 0)
        rP = 1;

    double rM = 0;
    if(errM != 0)
        rM = 1;

    double intermetidateP = errP_last + errP;
    double intermetidateM = errM_last + errM;

    intermetidateP = intermetidateP*rP*I_POS;
    intermetidateM = intermetidateM*rM*I_NEG;

    double val1Pos = min(max_I_pos,intermetidateP);
    double val1Neg = min(max_I_neg,intermetidateM);

    double resultPos =  val1Pos+err2P+errP*P_POS;
    double resultNeg =  val1Neg+err2M+errM*P_NEG;

    resultPos = saturate(resultPos,0,1);
    resultNeg = saturate(resultNeg,0,1);

    TC_pos = 1-resultPos;
    TC_neg = 1-resultNeg;


    int i = 0;
    for(i = 0; i<4; i++){

        vecErrorP_last[i] = vecErrorP[i];
        vecErrorM_last[i] = vecErrorM[i];

    }

    errP_last = errP;
    errM_last = errM;


 // update I_POS etc in define global definition
}
*/


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

    //Traction refers to previous samples values
    //SimplifiedTractionControl(T_s);

    //Blocco di ingressi e saturatazioni e conversioni

    //PRIMO candidato: valore massimo di torque per ogni ruota
    int i;
    for(i=0; i<4; i++){
        AMK_TorqueLimitPositive[i] = car_settings.max_pos_torque;
        AMK_TorqueLimitNegative[i] = car_settings.max_neg_torque;
    }

    th = throttleReq/100.0f;   //change range from 0-100 to 0-1
    brk = brakeReq/100.0f;     //change range from 0-100 to 0-1
    str = steering;
    ax = accelerations[X];  //m/s2
    ay = accelerations[Y];  //m/s2
    yaw_r = omegas[Z];      //rad/s

    for (i = 0; i < NUM_OF_MOTORS; i++){
        motorSpeeds[i] = motorVal1[i].AMK_ActualVelocity;
    }

    saturationsAndConversions();


    //Blocco dei calcoli preliminari
    FzCalculatorTV();
    speedCalculatorTV();

    float Torque_max[4];

    for(i = 0; i < NUM_OF_MOTORS; i++){
        Torque_max[i] = 21.0f - 0.000857*(fabsf(motorVal1[i].AMK_ActualVelocity) - 13000.0f);
    }

    for(i = 0; i < NUM_OF_MOTORS; i++){
        if (AMK_TorqueLimitPositive[i] > Torque_max[i]){
            AMK_TorqueLimitPositive[i] = Torque_max[i];
        }
        if (AMK_TorqueLimitNegative[i] < -Torque_max[i]){
            AMK_TorqueLimitNegative[i] = -Torque_max[i];
        }
    }


    for (i = 0; i < NUM_OF_MOTORS; i++){
        //Primo candidato (numero 0) c he � il torque massimo
        posTorqueCandidate[i][0] = AMK_TorqueLimitPositive[i];
    }


    //Funzione di controllo e calcolo dei candidati
    torqueVectoring();          //Secondo candidato calcolato secondo TV2019, con ripartizione front rear
    torqueLimit1();             //Terzo candidato calcolato con TorqueLimit1, ripartizione con Re e steer
    //launch_control();

    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
            //Save last setting of pos and neg troque
        minTorquePos[i] = fminf(posTorqueCandidate[i][0], posTorqueCandidate[i][2]);
        minTorquePos[i] = fminf(minTorquePos[i], posTorqueCandidate[i][1]);

       posTorqueNM_last[i] = posTorqueNM_last[i] - 0.2*(posTorqueNM_last[i] - (minTorquePos[i]));
       negTorqueNM_last[i] = negTorqueNM_last[i] - 0.2*(negTorqueNM_last[i] - (negTorqueCandidate[i]));

       //Send them out of TV
       posTorquesNM[i] = minTorquePos[i];
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
    for (i = 0; i < NUM_OF_MOTORS; i++){
        motorSpeeds[i] = saturateInt(motorSpeeds[i], MOTOR_SPEED_UPPER_BOUND, MOTOR_SPEED_LOWER_BOUND);
    }

    steering_to_delta_wheels();

    //Calcolo angolo in radianti delle ruote
    steers[0] = delta_steer[0] - TOE_F;
    steers[1] = delta_steer[1] + TOE_F;
    steers[2] = -TOE_R;
    steers[3] = TOE_R;


    //Conversions

    for (i = 0; i < NUM_OF_MOTORS; i++){
        motorSpeeds[i] = (motorSpeeds[i]*PI_FLOAT*TAU_TC)/30.0f;
    }

}

void speedCalculatorTV()
{
    int i;
    for (i = 0; i < 4; i++)
    {
        re[i] = R0 - (fz[i] * k_Re);
    }

    float tmp = ((th + brk)*0.1f)+1.0f;

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
        steers_tmp[i]*=((B*W)/A);
        steers_tmp[i]*=yaw_r;
    }

    float sum = 0;
    for (i = 0; i < 4; i++)
    {
        calc_tmp[i] = calc_tmp[i] - steers_tmp[i];
        sum+=calc_tmp[i];
    }

    //Speed estimation
    speedTv = sum * 0.25f;
    speedTv = saturateFloat(speedTv, SPEED_UPPER_BOUND, SPEED_LOWER_BOUND);
}

void FzCalculatorTV()
{
    //Calcolo delle forze applicate su ogni ruota
    float tmp_x = (ax*MASS*Z_COG)/(W*2.0f);

#ifdef TV_ACC
    float tmp_yf = 0;
    float tmp_yr = 0;
#else
    float tmp_yf = (ay*MASS*Z_COG*K_F)/T_F;
    float tmp_yr = (ay*MASS*Z_COG*K_R)/T_R;
#endif

    float tmp_u1 = speedTv*speedTv*0.25f*RHO*C_Z_A*((1-A_A)/W);
    float tmp_u2 = (speedTv*speedTv*0.25f*RHO*C_Z_A*A_A)/W;

    fz[0] = -tmp_x;
    fz[0] += -tmp_yf;
    fz[0] += MASS*B/W/2.0f*G_ACC;
    fz[0] += tmp_u1;

    fz[1] = -tmp_x;
    fz[1]+= tmp_yf;
    fz[1]+= MASS*B/W/2.0f*G_ACC;
    fz[1]+= tmp_u1;

    fz[2] = tmp_x;
    fz[2]+= -tmp_yr;
    fz[2]+= MASS*A/W/2.0f*G_ACC;
    fz[2]+= tmp_u2;

    fz[3] = tmp_x;
    fz[3]+= tmp_yr;
    fz[3]+= MASS*A/W/2.0f*G_ACC;
    fz[3]+= tmp_u2;

    int i;
    for (i = 0; i < 4; i++){
        fz[i] = saturateFloat(fz[i], FZ_UPPER_BOUND, FZ_LOWER_BOUND);
    }

}

void FZCalculatorTC(){
    /*
     * parameters are: ax, ay, speed_state[0]
     */
    double vx = speed_state[0];
    double temp1 = MASS*G_ACC*B/(2*W);
    double temp2 = ay*MASS*(B*zRC_f/W+kr_f/(kr_f+kr_r)*(Z_COG-(zRC_f+(zRC_r-zRC_f)*A/W)))/T_F;
    double temp3 = ay*(MASS*(A*zRC_r/W+kr_r/(kr_f+kr_r)*(Z_COG-(zRC_f+(zRC_r-zRC_f)*A/W)))/T_R);
    double temp4 = ax*(MASS*Z_COG)/(2*W);
    static double FI = RHO*CLA/2;
    double temp5 = vx*vx*FI*0.5*B_A/W;
    double temp6 = vx*vx*FI*0.5*A_A/W;
    double temp7 = MASS*G_ACC*A/(2*W);

    fzTC[0] = temp1 - temp2 - temp4 + temp5;
    fzTC[1] = temp1 - temp3 + temp2 + temp5;
    fzTC[2] = temp6 - temp3 - temp4 + temp7;
    fzTC[3] = temp6 + temp3 + temp4 + temp7;

    int i;
    for(i = 0; i < 4; i++){
        if (fzTC[i] < 0)
            fzTC[i] = 0;
        if (fzTC[i] > 2000)
            fzTC[i] = 2000;
    }
}

void RECalculatorTC(){
    double old_FZ[4];
    int i;
    for(i = 0; i < 4; i++){
            reTC[i] = R0 - old_FZ[i]*k_Re;
    }

    for(i = 0; i < 4; i++){
        if (reTC[i] > R0)
            reTC[i] = R0;
        if (reTC[i] < 0.95*R0)
            reTC[i] = 0.95*R0;
    }

    for(i = 0; i < 4; i++){
        old_FZ[i] = fzTC[i];
    }

    for(i = 0; i < 4; i++){
        v_wheels[i] = reTC[i]*RPM_TO_RADS*motorVal1[i].AMK_ActualVelocity;
    }

}

void torqueVectoring()
{
   float t_ratio = 0.5f;
   torqueRepartition();
   int i;
   for (i = 0; i < 4; i++)
   {
       //SECONDO CANDIDATO
       if(i == MOTOR_FL || i == MOTOR_FR){
           posTorqueCandidate[i][1] = repFz[i]*th*2.0f*T_MAX_HC*t_ratio;//*4*AMK_TorqueLimitPositive[i];
           negTorqueCandidate[i] = repFz[i]*brk*4.0f*MAX_NEG_TORQUE;
       }else{
           posTorqueCandidate[i][1] = repFz[i]*th*2.0f*T_MAX_HC*(1-t_ratio);
           negTorqueCandidate[i] = repFz[i]*brk*4.0f*MAX_NEG_TORQUE;
       }
   }

}

void torqueRepartition()
{
    //Sum of forces
    float fzSum = 0;
    int i;
    for (i = 0; i < 4; i++)
        fzSum+= fz[i];

    float fzSumDef = fz[2]+fz[3];
    //front repartition
    float repF = (fz[0])/(fz[0]+fz[1]);
    //Lateral front repartition
    repFz[0] = repF;
    repFz[1] = 1-repFz[0];

    //Rear repartition
    float repR = fz[3]/fzSumDef;
    //Lateral rear repartition
    repFz[3] = repR;
    repFz[2] = (1-repFz[3]);





}

void torqueLimit1(){
    float tmp_fz[4];
    int i = 0;
    for(i = 0; i < NUM_OF_MOTORS; i++){
        tmp_fz[i] = fz[i]*NU1 + pow(fz[i],2.0f)*NU2 + pow(fz[i],3.0f)*NU3 + pow(fz[i],4.0f)*NU4 + pow(fz[i],5.0f)*NU5 + pow(fz[i],6.0f)*NU6;
    }
    float tmp_steer[4];
    for(i = 0; i < NUM_OF_MOTORS; i++){
        steers[i] = tanf(steers[i]);
        steers[i] = saturateFloat(steers[i],0.2f, -0.2f);
        tmp_steer[i] = ALPHA0 + steers[i]*ALPHA1 + pow(steers[i], 2.0f)*ALPHA2 + pow(steers[i], 3.0f)*ALPHA3 + pow(steers[i], 4.0f)*ALPHA4 + pow(steers[i], 5.0f)*ALPHA5;
    }

    float tmp_y[4];

    for(i = 0; i < NUM_OF_MOTORS; i++){
        tmp_y[i] = saturateFloat(tmp_fz[i],2*fz[i], 1.0f);
    }

    for(i = 0; i < NUM_OF_MOTORS; i++){
        //TERZO CANDIDATO
        //1.0f cond di grip ideale 0.0grip inesistente
        posTorqueCandidate[i][2] = tmp_steer[i] * tmp_y[i] * re[i];
        posTorqueCandidate[i][2] *= TAU;
    }
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

/*
 * https://github.com/simondlevy/TinyEKF
 */
void ExtendedKalmanFilter(double T){

    /*
     * PARAMETERS
     */
    double x[2] = {speed_state[0], speed_state[1]};

    /*
     * MATRICES
     */
    double A_k[4] = {1, yaw_r*T, -yaw_r*T, 1};  //2x2
    double B_k[4] = {T, 0, 0, T};       // 2x2
    static double H[2] = {1, 0};         // 1x2
    double W_k[6] = {-x[0]*T, -T, 0, x[1], 0, -T}; //2x3

    static int n = 2, m = 3;

    static double P_k[4] = {0, 0, 0, 0};  //2x2
    static double Pnew_k[4] = {0,0,0,0};     //2x2
    double K_k[2] = {0,0};  //2x1
    static double Q[4] = {0, 0, 0, 0};  //2x2
    static double * R_tc = 0;   //scalar

    double AT_k[4];
    double WT_k[6];     //3x2
    double HT[2];
    transpose(H, HT, 1, 2);

    double Temp_1[4] = {0,0,0,0};   //2x2
    double Temp_2[4] = {0,0,0,0};   //2x2
    /*
     *  Temp_2 = (A * P_k-1 * A')
     */
    transpose(A_k, AT_k, n, n);
    mulmat(A_k, P_k, Temp_1, n, n, n);
    mulmat(Temp_1, AT_k, Temp_2, n, n, n);

    double Temp_3[6];        //2x3
    /*
     * Temp_3 = (W * Q * W')
     */
    transpose(W_k, WT_k, n, m);
    mulmat(W_k, Q, Temp_3, n, m, m);
    mulmat(Temp_3, WT_k, Temp_1, n, m, n);

    add(Temp_1, Temp_2, Pnew_k, n);


    double Temp_4[2];       //2x1
    double Temp_5[2];       //2x1
    double * Temp_6 = 0;    //scalar
    mulmat(Pnew_k, HT, Temp_4, 2, 2, 1);
    /*
     * Temp_6 = (H * Pnew * H') + R
     */
    mulmat(Pnew_k, HT, Temp_5, 2, 2, 1);
    mulmat(H, Temp_5, Temp_6, 1, 2, 1);
    accum(Temp_6, R_tc, 1, 1);

    mulscal(Temp_5, (1/(*Temp_6)), K_k, 2, 1);

    double Temp_7[4];   //2x2
    /*
     * P_k = ( I - K_k ) * Pnew
     */
    mulmat(K_k, H, Temp_7, 2, 1, 2);

    negate(Temp_7, n, n);
    mat_addeye(Temp_7, n);

    mulmat(Temp_7, Pnew_k, P_k, n, n, n);

    /*
     * Time update
     */

        /*
         * Temp_4 = A_k * x_k-1
         */
        mulmat(A_k, x, Temp_4, 2, 2, 1);


        /*
         * Temp_5 = B * u_k-1
         */
        double u[2] = {ax, ay};
        mulmat(B_k, u, Temp_5, 2, 2, 1);

        /*
         * x-_k = temp_x_minus = Temp_4 + Temp_5
         */
        double temp_x_minus[2];
        add(Temp_4, Temp_5, temp_x_minus, 2);

    /*
     * Measurement
     */
    double z_k = ZK_compute(T);


    /*
     * Measurement Update
     */
        double Temp_9[1];
        double Temp_err[2];
        double New_x[2];
        mulmat(H, temp_x_minus, Temp_6, 1, 2, 1);
        sub(&z_k, Temp_6, Temp_9, 1);
        mulmat(K_k, Temp_9, Temp_err, 2, 1, 1);
        add(Temp_err, temp_x_minus, New_x, 2);

    /*
     * R0 check
     */
        if( yaw_r <= SMALL_R0 ){
            New_x[1] = 0;
        }

    /*
     * Update current state
     */
     speed_state[0] = New_x[0];
     speed_state[1] = New_x[1];
}

double ZK_compute(double T){
    /*
     * Parameters
     *  ax, r_k, wheels_angles, v_wheels, vx_k-1
     *  In our code
     *  ax, yaw_r, w_angles, v_wheels, speed_state[0]
     */

    double Temp_rk[4] = {yaw_r*T_F/2.f, -yaw_r*T_F/2.f, yaw_r*T_R/2.f, -yaw_r*T_R/2.f};

    w_angles[0] = cos(w_angles[0]);
    w_angles[1] = cos(w_angles[1]);
    w_angles[2] = cos(w_angles[2]);
    w_angles[3] = cos(w_angles[3]);

    static double Vi[4] = {0,0,0,0};
    static double old_Vi[4] = {0,0,0,0};
    static double delta_Vi[4] = {0,0,0,0};
    old_Vi[0] = Vi[0];
    old_Vi[1] = Vi[1];
    old_Vi[2] = Vi[2];
    old_Vi[3] = Vi[3];
    Vi[0] =  w_angles[0]*v_wheels[0] + Temp_rk[0];
    Vi[1] =  w_angles[0]*v_wheels[1] + Temp_rk[1];
    Vi[2] =  w_angles[0]*v_wheels[2] + Temp_rk[2];
    Vi[3] =  w_angles[0]*v_wheels[3] + Temp_rk[3];

    double Temp_ax[3] = {0,0,0};
    if ( ax > AX0 ){
        Temp_ax[0] = 1;
    }
    if ( ax < -AX0 ){
        Temp_ax[2] = 1;
    }
    if ( ax >= -AX0 && ax < AX0){
            Temp_ax[1] = 1;
    }

    double vi_max = max_vect(Vi, 4);
    double vi_min = min_vect(Vi, 4);

    /*
     * Compute Weights
     */
    double temp_1[4] = {0,0,0,0};
    double partial_1, partial_2;
    sub(v_wheels, Vi, temp_1, 4);
    partial_1 = magnitude_squared(temp_1, 4) / pow(SIGMA_W2, 2);

    double temp_2[4] = {0,0,0,0};
    sub(Vi, old_Vi, delta_Vi, 4);
    mulscal(delta_Vi, 1/T, temp_2, 4, 1);

    temp_2[0] = AX0 - temp_2[0];
    temp_2[1] = AX0 - temp_2[1];
    temp_2[2] = AX0 - temp_2[2];
    temp_2[3] = AX0 - temp_2[3];
    partial_2 = magnitude_squared(temp_2, 4) / pow(SIGMA_W1, 2);

    double temp_3 = (double)(exp(-0.5*(partial_1 + partial_2)));

    double temp_4[4] = {0,0,0,0};
    mulscal(Vi, temp_3, temp_4, 4, 1);

    double final_mux[3] = {0,0,0};
    final_mux[0] = vi_min;
    final_mux[1] = element_sum(temp_4, 4)/temp_3;
    final_mux[2] = vi_max;

    double z_vect[3] = {0,0,0};
    z_vect[0] = final_mux[0]*Temp_ax[0];
    z_vect[1] = final_mux[1]*Temp_ax[1];
    z_vect[2] = final_mux[2]*Temp_ax[2];

    return element_sum(z_vect, 3);
}

void velocity_estimation(double T){
    steering_to_delta_wheels();
    wheels_angles();

    RECalculatorTC();

    ExtendedKalmanFilter(T);
}





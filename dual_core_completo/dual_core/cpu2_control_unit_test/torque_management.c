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
            Torque_max[i] = MAX_POS_TORQUE - 0.000857*(fabsf(motorVal1[i].AMK_ActualVelocity) - ((21.0f - MAX_POS_TORQUE)/0.000857) - 13000.0f);
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
       posTorqueCandidate[i][1] = repFz[i]*th*2*AMK_TorqueLimitPositive[i];
       negTorqueCandidate[i] = repFz[i]*brk*2*AMK_TorqueLimitNegative[i];
   }

}

void torqueRepartition()
{
    repFz[0] = fz[0]/(fz[0] + fz[1]);
    repFz[1] = 1 - repFz[0];

    float fzSum = 0;
    int i;
    for (i = 0; i < 4; i++)
        fzSum+= fz[i];

    fzSum = fzSum - (fz[0] + fz[1]);
    fzSum = fz[3]/fzSum;

    repFz[2] = 1 - fzSum;
    repFz[3] = fzSum;
}

//DEPRECATED
//
//float getInnerTorque(float requestedTorque, float speed, float steering, float k)
//{
//    float absSteer = steering;
//    if (absSteer < 0) {
//        absSteer *= -1.0;
//    }
//
//    float x = changeRange(absSteer, 0, STZ_RANGE, 0, 1);
//    x = 1 - x;  // lots of steering -> less torque
//    x = changeRange(x, 0, 1, 0.5, 0.8);
//    float newTorque = requestedTorque * x;
//    return newTorque;
//}
//
//float getOuterTorque(float requestedTorque, float speed, float steering, float k)
//{
//    float absSteer = steering;
//    if (absSteer < 0) {
//        absSteer *= -1.0;
//    }
//
//    float x = changeRange(absSteer, 0, STZ_RANGE, 1.1, 1.3);
//    float newTorque = requestedTorque * x;
//    return newTorque;
//}
//
//bool isLeftTurn()
//{
//    return steering > STEERING_DEADBAND;
//}
//
//bool isRightTurn()
//{
//    return steering < -STEERING_DEADBAND;
//}
//
//bool isInnerMotor(int motor)
//{
//    if (isLeftTurn()) {
//        return motor == MOTOR_FL || motor == MOTOR_RL;
//    } else if (isRightTurn()) {
//        return motor == MOTOR_FR || motor == MOTOR_RR;
//    }
//
//    return false;
//}
//
//bool isOuterMotor(int motor)
//{
//    if (isLeftTurn()) {
//        return motor == MOTOR_FR || motor == MOTOR_RR;
//    } else if (isRightTurn()) {
//        return motor == MOTOR_FL || motor == MOTOR_RL;
//    }
//
//    return false;
//}
//
//float getMotorScale(int motor)
//{
//    if (motor == MOTOR_FL || motor == MOTOR_FR) {
//        return FRONT_MOTOR_SCALE;
//    }
//
//    return REAR_MOTOR_SCALE;
//}




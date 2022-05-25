#include "motor_management.h"


//attenzione passare 8 bit
void read_AMK_Values1(Uint16 canMsg[], int indexMotor) {

    if (indexMotor != 0 && indexMotor != 1 && indexMotor != 2 && indexMotor != 3)
        return ;

    motorVal1[indexMotor].AMK_bSystemReady = getBit(canMsg[1],0);
    motorVal1[indexMotor].AMK_bError = getBit(canMsg[1],1);
    motorVal1[indexMotor].AMK_bWarn = getBit(canMsg[1],2);
    motorVal1[indexMotor].AMK_bQuitDcOn = getBit(canMsg[1],3);
    motorVal1[indexMotor].AMK_bDcOn = getBit(canMsg[1],4);
    motorVal1[indexMotor].AMK_bQuitInverterOn = getBit(canMsg[1],5);
    motorVal1[indexMotor].AMK_bInverterOn = getBit(canMsg[1],6);
    motorVal1[indexMotor].AMK_bDerating = getBit(canMsg[1],7);

    motorVal1[indexMotor].AMK_ActualVelocity = canMsg[2] | canMsg[3] << 8;
    motorVal1[indexMotor].AMK_TorqueCurrent = (canMsg[4] | canMsg[5] << 8) * AMK_CURR_SCALE;
    motorVal1[indexMotor].AMK_MagnetizingCurrent = (canMsg[6] | canMsg[7] << 8) * AMK_CURR_SCALE;

    // see PDK
    float torqueCurr = motorVal1[indexMotor].AMK_TorqueCurrent;
    float magnCurr = motorVal1[indexMotor].AMK_MagnetizingCurrent;
    float curr = 0.243 * torqueCurr + 0.0009 * torqueCurr * magnCurr;
    motorVal1[indexMotor].AMK_Current = curr;

    //Send data to logger
//    if (amkVal1ForwardCounter[indexMotor] >= 20)
//    {
//        //CAN_sendMessage(CANA_BASE, (OBJ_ID_AMK1_DATA_BASE + indexMotor), MSG_DATA_LENGTH, canMsg);
//        amkVal1ForwardCounter[indexMotor] = 0;
//    }
//    else
//        amkVal1ForwardCounter[indexMotor]++;

}


void read_AMK_Values2(Uint16 canMsg[], int indexMotor) {

    if (indexMotor != 0 && indexMotor != 1 && indexMotor != 2 && indexMotor != 3)
        return ;

    motorVal2[indexMotor].AMK_TempMotor = (canMsg[0] | canMsg[1] << 8) / 10;
    motorVal2[indexMotor].AMK_TempInverter = (canMsg[2] | canMsg[3] << 8) / 10;
    motorVal2[indexMotor].AMK_TempIGBT = (canMsg[6] | canMsg[7] << 8) / 10;
    motorVal2[indexMotor].AMK_ErrorInfo = (canMsg[4] | canMsg[5] << 8);

    //Send data to logger once every 100 message received -> every second
//    if (amkVal2ForwardCounter[indexMotor] >= 100)
//    {
//        //CAN_sendMessage(CANA_BASE, (OBJ_ID_AMK2_DATA_BASE + indexMotor), MSG_DATA_LENGTH, canMsg);
//        amkVal2ForwardCounter[indexMotor] = 0;
//    }
//    else
//        amkVal2ForwardCounter[indexMotor]++;
}

void send_AMK_SetPoints(int indexMotor, int velocity, int posTorque, int negTorque) {
    unsigned char tmp[2];
    if (indexMotor != 0 && indexMotor != 1 && indexMotor != 2 && indexMotor != 3)
        return ;

    // Byte 0 is reserved
    set_SetPoint(indexMotor, velocity, posTorque, negTorque);
    CAN_AMK_SET_POINT[indexMotor][1] = getByte(indexMotor);
    TXB_Setpoints_Data[indexMotor][1] = getByte(indexMotor);

    int2Bytes(tmp, motorSetP[indexMotor].AMK_TargetVelocity);
    CAN_AMK_SET_POINT[indexMotor][2] = tmp[0];
    TXB_Setpoints_Data[indexMotor][2] = tmp[0];
    CAN_AMK_SET_POINT[indexMotor][3] = tmp[1];
    TXB_Setpoints_Data[indexMotor][3] = tmp[1];

    int2Bytes(tmp, motorSetP[indexMotor].AMK_TorqueLimitPositive);
    CAN_AMK_SET_POINT[indexMotor][4] = tmp[0];
    TXB_Setpoints_Data[indexMotor][4] = tmp[0];
    CAN_AMK_SET_POINT[indexMotor][5] = tmp[1];
    TXB_Setpoints_Data[indexMotor][5] = tmp[1];

    int2Bytes(tmp, motorSetP[indexMotor].AMK_TorqueLimitNegative);
    CAN_AMK_SET_POINT[indexMotor][6] = tmp[0];
    TXB_Setpoints_Data[indexMotor][6] = tmp[0];
    CAN_AMK_SET_POINT[indexMotor][7] = tmp[1];
    TXB_Setpoints_Data[indexMotor][7] = tmp[1];

    CANMessageSet(CANB_BASE, (14 + indexMotor), &TXCANB_Setpoints_Message[indexMotor], MSG_OBJ_TYPE_TX);

}

void initializeMotor(int indexMotor)
{
    // removeError(indexMotor);

    motorSetP[indexMotor].AMK_bDcOn = 0;
    motorSetP[indexMotor].AMK_bInverterOn = 0;
    motorSetP[indexMotor].AMK_bEnable = 0;
    motorSetP[indexMotor].AMK_bErrorReset = 0;

    if(motorVal1[indexMotor].AMK_bSystemReady == 1) {
        motorSetP[indexMotor].AMK_bDcOn = 1;
    }

    if(motorVal1[indexMotor].AMK_bQuitDcOn && enableMotor) {
        motorSetP[indexMotor].AMK_bEnable = 1;
        motorSetP[indexMotor].AMK_bInverterOn = 1;
    } else {
        motorSetP[indexMotor].AMK_bEnable = 0;
        motorSetP[indexMotor].AMK_bInverterOn = 0;
    }

    send_AMK_SetPoints(indexMotor,0,0,0);

    if(motorVal1[indexMotor].AMK_bSystemReady && motorVal1[indexMotor].AMK_bQuitDcOn && motorVal1[indexMotor].AMK_bQuitInverterOn) {
        motorInitialized[indexMotor] = 1;
    }
}

void set_SetPoint(int indexMotor, int velocity, int posTorque, int negTorque)
{
    switch(drivingMode) {
    case FORWARD_ACC:
        motorSetP[indexMotor].AMK_TargetVelocity = velocity;
        motorSetP[indexMotor].AMK_TorqueLimitPositive = posTorque;
        motorSetP[indexMotor].AMK_TorqueLimitNegative = negTorque;  //negative sign is included
        break;
    case COASTING:
        motorSetP[indexMotor].AMK_TargetVelocity = velocity;
        motorSetP[indexMotor].AMK_TorqueLimitPositive = 0;
        motorSetP[indexMotor].AMK_TorqueLimitNegative = 0;
        break;
    case BRAKES_POS:
        motorSetP[indexMotor].AMK_TargetVelocity = 0;
        motorSetP[indexMotor].AMK_TorqueLimitPositive = 0;
        motorSetP[indexMotor].AMK_TorqueLimitNegative = negTorque;  //negative sign is included
        break;
    case BRAKES_NEG:
        motorSetP[indexMotor].AMK_TargetVelocity = 0;
        motorSetP[indexMotor].AMK_TorqueLimitPositive = posTorque;
        motorSetP[indexMotor].AMK_TorqueLimitNegative = 0;
        break;
    case REVERSE_ACC:
        motorSetP[indexMotor].AMK_TargetVelocity = velocity;        //negative sign is included
        motorSetP[indexMotor].AMK_TorqueLimitPositive = posTorque;
        motorSetP[indexMotor].AMK_TorqueLimitNegative = negTorque;  //negative sign is included
        break;
    default:
        break;
    }
}

void deactiveMotor(int indexMotor) {
    send_AMK_SetPoints(indexMotor,0,0,0);

    motorSetP[indexMotor].AMK_bInverterOn = 0;
    send_AMK_SetPoints(indexMotor,0,0,0);   //Send SetPoint with AMK_bInverterOn = 0

    motorSetP[indexMotor].AMK_bEnable = 0;
    send_AMK_SetPoints(indexMotor,0,0,0);   //Send SetPoint with AMK_bEnable = 0

    while(motorVal1[indexMotor].AMK_bQuitDcOn == 1) {
        //Wait until AMK_bQuitDcOn = 0
    }

    motorSetP[indexMotor].AMK_bDcOn = 0;
    send_AMK_SetPoints(indexMotor,0,0,0);   //Send SetPoint with AMK_bDcOn = 0

    while(motorVal1[indexMotor].AMK_bQuitDcOn == 1) {
        // Wait until AMK_bQuitDcOn = 0
    }

    motorInitialized[indexMotor] = 0;
}

void removeError(int indexMotor) {
    motorSetP[indexMotor].AMK_bInverterOn = 0;
    motorSetP[indexMotor].AMK_bEnable = 0;
    motorSetP[indexMotor].AMK_bErrorReset = 1;
    send_AMK_SetPoints(indexMotor,0,0,0);   // Send SetPoint with AMK_bErrorReset = 1
}

void set_AMK_Drive_Mode(int mode)
{
    drivingMode = mode;
}

char getByte(int i)
{
    char c = 0b0000;
    if(motorSetP[i].AMK_bErrorReset)
        c |= 0b1000;
    if(motorSetP[i].AMK_bEnable)
        c |= 0b0100;
    if(motorSetP[i].AMK_bDcOn)
        c |= 0b0010;
    if(motorSetP[i].AMK_bInverterOn)
        c |= 0b0001;

    return c;
}

bool getBit(char c, int bitNumber) {
   return (c & (1 << bitNumber)) != 0;
}


int getMotorIndex(int id)
{
    int index = -1;
    int i;
    for (i = 0; i<4; i++)
    {
        if (id == AMK_VAL_1_IDS[i] || id == AMK_VAL_2_IDS[i])
            index = i;
    }

    return index;
}

int getAMKValNumber(int id)
{
    int i;
    for (i = 0; i<4; i++)
    {
        if (id == AMK_VAL_1_IDS[i])
            return 1;
    }

    for (i = 0; i<4; i++)
    {
        if (id == AMK_VAL_2_IDS[i])
            return 2;
    }

    return -1;
}

void int2Bytes(unsigned char* bytes_temp, int int_variable)
{
    bytes_temp[0] = int_variable & 0xFF;
    bytes_temp[1] = int_variable >> 8 & 0xFF;
}

void sendAMKDataMotor(int motor, int posTorque, int negTorque) {
    if(!motorInitialized[motor] && motorVal1[motor].AMK_bSystemReady == 1) {
        initializeMotor(motor);
    } else if(motorInitialized[motor] == 1 && motorVal1[motor].AMK_bQuitInverterOn == 1) {
        send_AMK_SetPoints(motor, velocityRef, posTorque, negTorque);
    } else if(motorVal1[motor].AMK_bError) {
        send_AMK_SetPoints(motor, 0, 0, 0);
        removeError(motor);
        motorInitialized[motor] = 0;
    } else {
        motorSetP[motor].AMK_bDcOn = 0;
        motorSetP[motor].AMK_bInverterOn = 0;
        motorSetP[motor].AMK_bEnable = 0;
        motorSetP[motor].AMK_bErrorReset = 0;
        send_AMK_SetPoints(motor, 0, 0, 0);
        motorInitialized[motor] = 0;
    }
}

void sendAMKData() {

#ifndef NO_ONE_PEDAL
    onePedalDriving();
#endif
    int i = 0;

    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        posTorquesNM[i] = torqueSetpointToNM(throttleReq*THROTTLE_POWER_SCALE);
        negTorquesNM[i] = torqueSetpointToNM(brakeReq*REG_POWER_SCALE);
    }


#ifndef NO_TORQUE_VECTORING
    //TORQUE VECTORING
     performancePack();

#endif

#ifndef NO_REG_BRAKE
     regBrake();
#endif

#ifndef NO_POWER_CONTROL
    //POWER CONTROL
    if (throttleReq > 0 && brakeReq == 0)
        powerControl();
    else
        anti_wind_up = 0;
#endif

    for (i = 0; i < NUM_OF_MOTORS; i++) {
        int posTorque, negTorque;

        //RIPARTIZIONE DI COPPIA SEMPLICE
        if (i == MOTOR_FL || i == MOTOR_FR)
        {
            posTorque = NMtoTorqueSetpoint(saturateFloat(posTorquesNM[i]*FRONT_MOTOR_SCALE, MAX_POS_TORQUE, 0.0f));
            negTorque = NMtoTorqueSetpoint(saturateFloat(negTorquesNM[i]*FRONT_MOTOR_SCALE,0,MAX_NEG_TORQUE));
        }
        else if (i == MOTOR_RR || i == MOTOR_RL)
        {
            posTorque = NMtoTorqueSetpoint(saturateFloat(posTorquesNM[i]*REAR_MOTOR_SCALE, MAX_POS_TORQUE, 0.0f));
            negTorque = NMtoTorqueSetpoint(saturateFloat(negTorquesNM[i]*REAR_MOTOR_SCALE,0,MAX_NEG_TORQUE));
        }

        sendAMKDataMotor(i, posTorque, negTorque);
    }
}

void setAMK(int newVelocityRef, int newPosTorqueLim, int newNegTorqueLim) {
    velocityRef = newVelocityRef;
    throttleReq = newPosTorqueLim;
    brakeReq = newNegTorqueLim;
}

void stopAMK() {
    setAMK(0, 0, 0);
}

void brakeAMK(int negTorqueLim) {
    setAMK(0, 0, negTorqueLim);

}

void throttleAMK(int posTorqueLim) {
    setAMK(SPEED_LIMIT, posTorqueLim, 0);
}

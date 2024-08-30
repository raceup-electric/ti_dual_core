#include "motor_management.h"
#include "TV/Torque_Vectoring_2024_forsecontiu.h"
#include "car_management.h"


//attenzione passare 8 bit
//void read_AMK_Values1(Uint16 canMsg[], int indexMotor) {
//
//    if (indexMotor != 0 && indexMotor != 1 && indexMotor != 2 && indexMotor != 3)
//        return ;
//
//    motorVal1[indexMotor].AMK_bSystemReady = getBit(canMsg[1],0);
//    motorVal1[indexMotor].AMK_bError = getBit(canMsg[1],1);
//    motorVal1[indexMotor].AMK_bWarn = getBit(canMsg[1],2);
//    motorVal1[indexMotor].AMK_bQuitDcOn = getBit(canMsg[1],3);
//    motorVal1[indexMotor].AMK_bDcOn = getBit(canMsg[1],4);
//    motorVal1[indexMotor].AMK_bQuitInverterOn = getBit(canMsg[1],5);
//    motorVal1[indexMotor].AMK_bInverterOn = getBit(canMsg[1],6);
//    motorVal1[indexMotor].AMK_bDerating = getBit(canMsg[1],7);
//
//    motorVal1[indexMotor].AMK_ActualVelocity = canMsg[2] | canMsg[3] << 8;
//    motorVal1[indexMotor].AMK_TorqueCurrent = (canMsg[4] | canMsg[5] << 8) * AMK_CURR_SCALE;
//    motorVal1[indexMotor].AMK_MagnetizingCurrent = (canMsg[6] | canMsg[7] << 8) * AMK_CURR_SCALE;
//
//    // see PDK
//    float torqueCurr = motorVal1[indexMotor].AMK_TorqueCurrent;
//    float magnCurr = motorVal1[indexMotor].AMK_MagnetizingCurrent;
//    float curr = 0.243 * torqueCurr + 0.0009 * torqueCurr * magnCurr;
//    motorVal1[indexMotor].AMK_Current = curr;
//
//}

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

    motorVal1[indexMotor].AMK_ActualVelocity = unsigned_to_signed((canMsg[2] | canMsg[3] << 8));
    motorVal1[indexMotor].AMK_TorqueCurrent = (canMsg[4] | canMsg[5] << 8) * AMK_CURR_SCALE;
    // it should be AMK Magnetizing current, but ...
    motorVal1[indexMotor].AMK_Voltage = (canMsg[6] | canMsg[7] << 8);

    // see PDK - TODO: to be removed
    motorVal1[indexMotor].AMK_Current = motorVal1[indexMotor].AMK_TorqueCurrent;
}


void read_AMK_Values2(Uint16 canMsg[], int indexMotor) {

    if (indexMotor != 0 && indexMotor != 1 && indexMotor != 2 && indexMotor != 3)
        return ;

    motorVal2[indexMotor].AMK_TempMotor = (canMsg[0] | canMsg[1] << 8) / 10;
    motorVal2[indexMotor].AMK_TempInverter = (canMsg[2] | canMsg[3] << 8) / 10;
    motorVal2[indexMotor].AMK_TempIGBT = (canMsg[6] | canMsg[7] << 8) / 10;
    motorVal2[indexMotor].AMK_ErrorInfo = (canMsg[4] | canMsg[5] << 8);
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

    CANMessageSet(CANB_BASE, (TX_OBJ_AMK_SETPOINTS + indexMotor), &TXCANB_Setpoints_Message[indexMotor], MSG_OBJ_TYPE_TX);

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
    // TODO: ridondante
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

/*
 * This function is responsible for initializing and managing the motors.
 */
void sendAMKDataMotor(int motor, int posTorque, int negTorque) {

    //if motor is not initialized and is ready -> initialize motor
    if(!motorInitialized[motor] && motorVal1[motor].AMK_bSystemReady == 1) {
        initializeMotor(motor);
    }
    // if error, stop motor
    else if(motorVal1[motor].AMK_bError) {
        send_AMK_SetPoints(motor, 0, 0, 0);
        removeError(motor);
        motorInitialized[motor] = 0;
    }
    //if motor is initialized and RF is on -> send setpoints
    else if(motorInitialized[motor] == 1 && motorVal1[motor].AMK_bQuitInverterOn == 1) {
        send_AMK_SetPoints(motor, velocityRef, posTorque, negTorque);
    }
    //limit case - motor destroyed
    else {
        motorSetP[motor].AMK_bDcOn = 0;
        motorSetP[motor].AMK_bInverterOn = 0;
        motorSetP[motor].AMK_bEnable = 0;
        motorSetP[motor].AMK_bErrorReset = 0;
        send_AMK_SetPoints(motor, 0, 0, 0);
        motorInitialized[motor] = 0;
    }
}

/*
 * This function is responsible for sending instruction (setpoints) to the motors.
 * This function implements the right order of operations to merge all features (REGEN,
 * TORQUE_VECTORING, POWER_CONTROL, ONE_PEDAL -in future-).
 *
 * The basic idea is that posTorquesNM are processed by different functions in a
 * precise order and at the end they are converted to setpoints and sent to AMK motors.
 */
void sendAMKData() {

    int posTorque[4], negTorque[4];

    int i = 0;
    // check AMK motors datasheet pg.1 rmp torque curve
    // Safety limit to torque at high speed (decrease torque limit with increasing rpm)
    float actual_max_pos_torque = saturateFloat(MAX_MOTOR_TORQUE - 0.000857*(motorVal1[i].AMK_ActualVelocity - 13000.0f), car_settings.max_pos_torque, 0.0f);
    float actual_max_neg_torque = -saturateFloat(MAX_MOTOR_TORQUE - 0.000857*(motorVal1[i].AMK_ActualVelocity - 13000.0f), -car_settings.max_neg_torque, 0.0f);

    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        /*
         * 0 - 100 throttle and brake to Nm (setpoint is relative to nominal torque and goes in 0.1% that's why there is * 10)
         * Setpoints are scaled to obtain desired torque repartition that inverts during braking
         * Negative torques are computed in regBrake() 
         */
        if (i == MOTOR_FL || i == MOTOR_FR) {
            posTorquesNM[i] = torqueSetpointToNM(throttleReq * (actual_max_pos_torque/M_N) * 10 * (car_settings.front_motor_repartition / (1 - car_settings.front_motor_repartition)));
            negTorquesNM[i] = 0.0f;
        }
        else if (i == MOTOR_RR || i == MOTOR_RL) {
            posTorquesNM[i] = torqueSetpointToNM(throttleReq * (actual_max_pos_torque/M_N) * 10);
            negTorquesNM[i] = 0.0f;
        }
    }

    // Reg brake makes the negative torques from positive to negative
    regBrake();

    if(car_settings.torque_vectoring) {

        int j;
        for(j = 0; j < 4; j++) {
            posTorquesNM[j] = rtY.T_pos[j];
        }
    }


    #ifndef NO_POWER_CONTROL
        //POWER CONTROL
        if (throttleReq > 0 && brakeReq >= 0)
            powerControl();
        else
            anti_wind_up = 0;
    #endif


    for (i = 0; i < NUM_OF_MOTORS; i++) {
        posTorque[i] = NMtoTorqueSetpoint(saturateFloat(posTorquesNM[i], actual_max_pos_torque, 0.0f));
        negTorque[i] = NMtoTorqueSetpoint(saturateFloat(negTorquesNM[i], 0.0f, actual_max_neg_torque));
    }


    for (i = 0; i < NUM_OF_MOTORS; i++) {
        if (posTorque[i] > 0 && negTorque[i] < 0) {
            sendAMKDataMotor(i, 0, negTorque[i]);
        }
        else {
            sendAMKDataMotor(i, posTorque[i], negTorque[i]);
        }
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
    setAMK(car_settings.max_speed, posTorqueLim, 0);
}

/*
 * Battery pack tension is sent to Bms-Host to implement precharge
 */
void sendHostData() {

    TXA_Host_Data[0] = batteryPackTension & 0x00FF;
    TXA_Host_Data[1] = (batteryPackTension >> 8) & 0x00FF;
    CANMessageSet(CANA_BASE, TX_OBJ_TO_HOST, &TXCANA_BmsHost_Message, MSG_OBJ_TYPE_TX);
}

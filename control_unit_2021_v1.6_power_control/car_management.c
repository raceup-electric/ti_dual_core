#include "car_management.h"

#ifdef DEBUG_HV
bool hvDebugging = false; //debug
bool hvGoneWrong[4] = {1,1,1,1};

bool rfDebugging = false; //debug
bool rfGoneWrong[4] = {1,1,1,1};

#endif

#if defined(DEBUG_NO_HV) || defined(DEBUG_HV)
    int leftFanDebug = 0;
    int rightFanDebug = 0;
#endif

void read_SENDYNE_message(unsigned char sendyne_values[]){
    reassembled_data= 0;
    uint8_t tmp= sendyne_values[0];
    tmp^= 1 <<7;
    reassembled_data |= ((uint32_t)(tmp) << 24);
    reassembled_data |= ((uint32_t)(sendyne_values[1]) << 16);
    reassembled_data |= ((uint32_t)(sendyne_values[2]) << 8);
    reassembled_data |= ((uint32_t)(sendyne_values[3]) << 0);
    sendyne_current = (int32_t)(reassembled_data) / 1000.0;

    reassembled_data= 0;
    reassembled_data |= ((uint32_t)(sendyne_values[4]) << 24);
    reassembled_data |= ((uint32_t)(sendyne_values[5]) << 16);
    reassembled_data |= ((uint32_t)(sendyne_values[6]) << 8);
    reassembled_data |= ((uint32_t)(sendyne_values[7]) << 0);
    sendyne_voltage = (-1)*(int32_t)(reassembled_data) / 1000000.0;

    total_power = sendyne_voltage*sendyne_current;

    CAN_sendMessage(CANA_BASE, OBJ_ID_SENDYNE_FORWARD, 8, (uint16_t *) sendyne_values);

}

void read_IMU_message(uint8_t imu_values[], int id)
{
    uint32_t aux_1 = 0;
    uint32_t aux_2 = 0;

    aux_1 |= ((int32_t)(imu_values[3])<<24);
    aux_1 |= ((int32_t)(imu_values[2])<<16);
    aux_1 |= ((int32_t)(imu_values[1])<<8);
    aux_1 |= ((int32_t)(imu_values[0])<<0);

    aux_2 |= ((int32_t)(imu_values[7])<<24);
    aux_2 |= ((int32_t)(imu_values[6])<<16);
    aux_2 |= ((int32_t)(imu_values[5])<<8);
    aux_2 |= ((int32_t)(imu_values[4])<<0);

    if (id == MSG_ID_IMU_1)
    {
        accelerations[X] = uint32_to_float(aux_1);
        accelerations[Y] = uint32_to_float(aux_2);
    }
    else if (id == MSG_ID_IMU_2)
    {
        accelerations[Z] = uint32_to_float(aux_1);
        omegas[X] = uint32_to_float(aux_2);
    }
    else if (id == MSG_ID_IMU_3)
    {
        omegas[Y] = uint32_to_float(aux_1);
        omegas[Z] = uint32_to_float(aux_2);
    }
}

void read_BMS_VOLTAGE_message(uint8_t bms_values[]){
    uint16_t tmp = 0;
    tmp=(bms_values[0] | bms_values[1]<<8);
    max_bms_voltage = convertBMSvoltage(tmp);
    tmp=(bms_values[2] | bms_values[3]<<8);
    min_bms_voltage = convertBMSvoltage(tmp);
    tmp=(bms_values[4] | bms_values[5]<<8);
    mean_bms_voltage = convertBMSvoltage(tmp);

}

void read_BMS_TEMP_message(uint8_t bms_values[]){
    uint16_t tmp = 0;
      tmp=(bms_values[0] | bms_values[1]<<8);
      max_bms_temp = convertBMStemp(tmp);
      tmp=(bms_values[2] | bms_values[3]<<8);
      min_bms_temp = convertBMStemp(tmp);
      tmp=(bms_values[4] | bms_values[5]<<8);
      mean_bms_temp = convertBMStemp(tmp);
}

void read_power_control_message(uint8_t val[]){
    power_limit = val[0]*1000.0f;
}

void brakeLight()
{
    if (brake > BRAKE_LIGHT_MIN) {
        GPIO_writePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_ON);  // ON
    } else {
        GPIO_writePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_OFF);  // OFF
    }

}

void playRTDS()
{
    GPIO_writePin(RTDS, 1U);  // sound
    cpuTimer1IntCount = 0;
    CPUTimer_startTimer(CPUTIMER1_BASE);    //timer for sound
}

void R2D_On()
{
    playRTDS();
    GPIO_writePin(R2D, R2D_LED_ON);  // led
    GPIO_writePin(POMPA_DX_Abil, 1U);  // pompa dx on
    GPIO_writePin(POMPA_SX_Abil, 1U);  // pompa sx on
    GPIO_writePin(VENTOLA_Abil, 1U);  // ventole on

}

void R2D_Off()
{
    GPIO_writePin(RTDS, 0U);  // sound
    GPIO_writePin(R2D, R2D_LED_OFF);  // led
    GPIO_writePin(POMPA_DX_Abil, 0U);  // pompa dx off
    GPIO_writePin(POMPA_SX_Abil, 0U);  // pompa sx off
    GPIO_writePin(VENTOLA_Abil, 0U);  // ventole off

}

void R2D_init()
{
    if(R2D_first_state){
        while(brake > R2D_BRAKE_TRESHOLD){
            if(readRF() && isHVOn()){
                R2D_state = 1;
                R2D_first_state = 0;
                R2D_On();
                break;
            }
            else{
                R2D_state = 0;
                break;
            }
        }
    }


    if(!R2D_state && !readRF()){
       R2D_first_state = 1;
    }
    else{
        R2D_first_state = 0;
    }

    if(!isHVOn() || !readRF()){
        R2D_state = 0;
        R2D_Off();
    }
}


//void checkHV()      //HV COUNTER OFF-->ON ON-->OFF
//{
//    int i;
//
//    for (i = 0; i < NUM_OF_MOTORS; i++)
//    {
//        if ((inverterHV[i] != motorVal1[i].AMK_bQuitDcOn) && (hvCounter[i] < HV_TRAP))
//                hvCounter[i]++;
//
//        else if ((inverterHV[i] != motorVal1[i].AMK_bQuitDcOn) && (hvCounter[i]>= HV_TRAP))
//        {
//            inverterHV[i] = motorVal1[i].AMK_bQuitDcOn;
//            hvCounter[i] = 0;
//        }
//        else if ((inverterHV[i] == motorVal1[i].AMK_bQuitDcOn) && (hvCounter[i] > 0))
//            hvCounter[i] = 0;
//    }
//}

void checkHV()      //HV COUNTER ON-->OFF
{
    int i;

    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        if ((motorVal1[i].AMK_bQuitDcOn == false) && (hvCounter[i] < HV_TRAP))
                hvCounter[i]++;

        else if ((motorVal1[i].AMK_bQuitDcOn == false) && (hvCounter[i]>= HV_TRAP))
        {
            inverterHV[i] = motorVal1[i].AMK_bQuitDcOn;
            hvCounter[i] = 0;
        }
        else if (motorVal1[i].AMK_bQuitDcOn == true)
        {
            inverterHV[i] = motorVal1[i].AMK_bQuitDcOn;
            hvCounter[i] = 0;
        }
    }
}

//void checkHV()    //HV ALWAYS ON
//{
//    int i;
//
//    for (i = 0; i < NUM_OF_MOTORS; i++)
//    {
//        if ((motorVal1[i].AMK_bQuitDcOn == false) && (inverterHV[i] == false))
//            inverterHV[i] = false;
//        else if ((motorVal1[i].AMK_bQuitDcOn == true) && (inverterHV[i] == false))
//            inverterHV[i] = true;
//        else if ((motorVal1[i].AMK_bQuitDcOn == false) && (inverterHV[i] == true))
//            inverterHV[i] = true;
//    }
//}


//void checkRF()  //RF ALWAYS ON ONCE ENABLED
//{
//    int i;
//
//    for (i = 0; i < NUM_OF_MOTORS; i++)
//    {
//        if ((motorVal1[i].AMK_bQuitInverterOn == false) && (inverterRF[i] == false))
//            inverterRF[i] = false;
//        else if ((motorVal1[i].AMK_bQuitInverterOn == true) && (inverterRF[i] == false))
//            inverterRF[i] = true;
//        else if ((motorVal1[i].AMK_bQuitInverterOn == false) && (inverterRF[i] == true))
//            inverterRF[i] = true;
//    }
//}

void checkRF()   //RF COUNTER ON-->OFF
{
    int i;

    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        if ((motorVal1[i].AMK_bQuitInverterOn == false) && (rfCounter[i] < RF_TRAP))
                rfCounter[i]++;

        else if ((motorVal1[i].AMK_bQuitInverterOn == false) && (rfCounter[i]>= RF_TRAP))
        {
            inverterRF[i] = motorVal1[i].AMK_bQuitInverterOn;
            rfCounter[i] = 0;
        }
        else if (motorVal1[i].AMK_bQuitInverterOn == true)
        {
            inverterRF[i] = motorVal1[i].AMK_bQuitInverterOn;
            rfCounter[i] = 0;
        }
    }
}


//void checkRF()    //RF COUNTER OFF-->ON ON-->OFF
//{
//    int i;
//
//    for (i = 0; i < NUM_OF_MOTORS; i++)
//    {
//        if ((inverterRF[i] != motorVal1[i].AMK_bQuitInverterOn) && (rfCounter[i] < RF_TRAP))
//                rfCounter[i]++;
//
//        else if ((inverterRF[i] != motorVal1[i].AMK_bQuitInverterOn) && (rfCounter[i]>= RF_TRAP))
//        {
//            inverterRF[i] = motorVal1[i].AMK_bQuitInverterOn;
//            rfCounter[i] = 0;
//        }
//        else if ((inverterRF[i] == motorVal1[i].AMK_bQuitInverterOn) && (rfCounter[i] > 0))
//            rfCounter[i] = 0;
//    }
//}

bool isHVOn()
{
    bool hv = false;

//    return true; //debug talebano

    int i;
    for (i = 0; i < NUM_OF_MOTORS; i++)
    {

//        hv &= motorVal1[i].AMK_bQuitDcOn;     codice vecchio

        hv |= inverterHV[i];

#ifdef DEBUG_HV
        if ((motorVal1[i].AMK_bQuitDcOn==0) && hvDebugging)
            hvGoneWrong[i] = motorVal1[i].AMK_bQuitDcOn;
#endif
    }

#ifdef DEBUG_NO_HV
    return true;
#endif
    return hv;
}


bool readRF()
{
    bool rf = false;

    int i;
    for (i = 0; i < NUM_OF_MOTORS; i++) {
//        rf &= motorVal1[i].AMK_bQuitInverterOn;       //vecchio codice
        rf |= inverterRF[i];

#ifdef DEBUG_HV
        if ((motorVal1[i].AMK_bQuitInverterOn==0) && rfDebugging)
            rfGoneWrong[i] = motorVal1[i].AMK_bQuitInverterOn;
#endif
    }

#ifdef DEBUG_NO_HV
    return true;
#endif
    return rf;

}

void checkImplausibility()
{
    if (implBrakeAndThrottle)
    {
        implBrakeAndThrottle = (throttle > 5);  // regardless of brake
    }
    else
    {
        implBrakeAndThrottle = ((brake > BRAKE_IMPL_THRESHOLD) && (throttle > THROTTLE_IMPL_THRESHOLD));
    }
}

void fanControl()
{
    if (!R2D_state)
    {
        leftFanSpeed = 0;
        rightFanSpeed = 0;
    }
    else
    {
        int leftTemp = fmax(motorVal2[0].AMK_TempInverter, motorVal2[2].AMK_TempInverter);
        int rightTemp = fmax(motorVal2[1].AMK_TempInverter, motorVal2[3].AMK_TempInverter);

        leftFanSpeed = fanSpeedFunction(leftTemp);
        rightFanSpeed = fanSpeedFunction(rightTemp);

    }

#if defined(DEBUG_NO_HV) || defined(DEBUG_HV)
        leftFanSpeed = leftFanDebug;
        rightFanSpeed = rightFanDebug;
#endif

    setFanSpeed(VENTOLA_SX, leftFanSpeed);
    setFanSpeed(VENTOLA_DX, rightFanSpeed);
}

//
//  Velocità della ventola (duty cycle %) in funzione della temperatura:
//  temperatura > 65°           ---> ventola spenta
//  65° < temperatura < 75°     ---> velocità scala linearmente da 20% a 100%
//  75° > temperatura           ---> 100%
//

uint8_t fanSpeedFunction(int temp){
#ifndef CONST_FAN_SPEED
    if (temp < 65)
        return 0;
    else if (temp > 75)
        return 100;
    else
        return (8*temp) - 500;
#endif

#ifdef CONST_FAN_SPEED
    return 50;
#endif

}

//void checkPumps(){      //deprecated
//    //if car is standing for more than 150ms stop pumps
//    if(actualVelocityKMH == 0){
//            stopPumpLimit++;
//
//            if(stopPumpLimit >= 150){
//                 WAT_PUMP_STATE = 0;
//                 OIL_PUMP_STATE = 0;
//                 stopPumpLimit = 160;
//                 enablePumpLimit = 0;
//                }
//            }
//    //if car is moving for more then 150ms restart pumps
//            else{
//                if(enablePumpLimit > 150){
//                    WAT_PUMP_STATE = 1;
//                    OIL_PUMP_STATE = 1;
//                    stopPumpLimit = 0;
//                    enablePumpLimit = 160;
//                }
//                else{
//                    enablePumpLimit++;
//                }
//        }
//    //pumps on if car is r2d
//    if (R2D_state)
//    {
//        GPIO_writePin(POMPA_DX_Abil, 1U);  // pompa dx on
//        GPIO_writePin(POMPA_SX_Abil, 1U);  // pompa sx on
//    }
//    else
//    {
//        GPIO_writePin(POMPA_DX_Abil, 0U);  // pompa dx off
//        GPIO_writePin(POMPA_SX_Abil, 0U);  // pompa sx off
//    }
//
//
//}

void checkTemps(){

    int i;
    int tmp = 0;

    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        if (motorVal2[i].AMK_TempInverter >= 75)
            tmp++;
    }

    if (tmp>0)
        temp_warning = true;
    else
        temp_warning = false;

    Temps[0]=getTempAvPT1000(readADC(TEMP_RAD_IN));
    Temps[1]=getTempAvPT1000(readADC(TEMP_RAD_OUT));
    Temps[2]=getTempZTP135SR(readADC(TEMP_TYRE_FRONT_L));
    Temps[3]=getTempZTP135SR(readADC(TEMP_TYRE_FRONT_R));
    Temps[4]=getTempZTP135SR(readADC(TEMP_TYRE_BACK_L));
    Temps[5]=getTempZTP135SR(readADC(TEMP_TYRE_BACK_R));
    Temps[6]=leftFanSpeed;
    Temps[7]=rightFanSpeed;
}


void checkStatus()
{
    //STATUS
    //bit       | 7  |    6    |    5     |  4  |     3     |    2    |    1     | 0  |
    //meaning   | RF | imp_b_t | brk_disc | r2d | PRECHARGE | TEMP_OK | LV_ALARM | HV |

    uint8_t mstatus = 0b00000000;
    if (isHVOn())
        mstatus |= 0b00000001;
//    if (GPIO_readPin(LV_ALARM))
//        mstatus |= 0b00000010;
    mstatus |= 0b00000000;

    if (temp_warning)
        mstatus |= 0b00000100;
    if (enableMotor)
        mstatus |= 0b00001000;
    if (R2D_state)
        mstatus |= 0b00010000;
    if (brk_disconnected)
        mstatus |= 0b00100000;
    if (implBrakeAndThrottle)
        mstatus |= 0b01000000;
    if (readRF())
        mstatus |= 0b10000000;

    status = mstatus;
}

void sendDataToLogger()
{
    sendStatusToLogger();
    sendSetpointsToLogger();

    if (cpuTimer0IntCount % 100 == 0)   //Pacchetto temp inviato ogni secondo
        sendTempsToLogger();

}

void sendStatusToLogger()
{
    uint8_t tmp[7];

    tmp[0] = throttle;
    tmp[1] = steering;
    tmp[2] = steering >>8;
    tmp[3] = brake;
    tmp[4] = getPressAvSP100(readADC(BRAKE_PRS_BACK)); //brake_pressure;
    tmp[5] = status;
    tmp[6] = (uint8_t) ((int)actualVelocityKMH);

    CAN_sendMessage(CANA_BASE, OBJ_ID_CAR_STATUS, 7, tmp);
}

void sendTempsToLogger()
{
    CAN_sendMessage(CANA_BASE, OBJ_ID_TEMPS, 8, Temps);
}

void sendSetpointsToLogger(){

    uint8_t setpoints[8];
    setpoints[0]=(uint8_t)(posTorquesNM[0]*10);
    setpoints[1]=(uint8_t)(posTorquesNM[1]*10);
    setpoints[2]=(uint8_t)(posTorquesNM[2]*10);
    setpoints[3]=(uint8_t)(posTorquesNM[3]*10);
    setpoints[4]=(uint8_t)(negTorquesNM[0]*-10);
    setpoints[5]=(uint8_t)(negTorquesNM[1]*-10);
    setpoints[6]=(uint8_t)(negTorquesNM[2]*-10);
    setpoints[7]=(uint8_t)(negTorquesNM[3]*-10);

    CAN_sendMessage(CANA_BASE, OBJ_ID_AMK_SETPOINTS, 8, setpoints);

}

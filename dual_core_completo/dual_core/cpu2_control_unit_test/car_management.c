#include "car_management.h"

int calibration_status = 0;
int NUM_SMU_TEMP = 5;
int NUM_SMU_SUSP = 4;


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
    Uint16 tmp= sendyne_values[0];
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

}

void read_LEM_message(unsigned char lem_values[]){
    reassembled_data= 0;
    Uint16 tmp= lem_values[0];
    tmp^= 1 <<7;
    reassembled_data |= ((uint32_t)(tmp) << 24);
    reassembled_data |= ((uint32_t)(lem_values[1]) << 16);
    reassembled_data |= ((uint32_t)(lem_values[2]) << 8);
    reassembled_data |= ((uint32_t)(lem_values[3]) << 0);
    lem_current = (int32_t)(reassembled_data) / 1000.0;

}

void read_IMU_message(Uint16 imu_values[], int id)
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

void read_SMU_Message(Uint16 smu_values[], int id){

    uint64_t aux = 0;
    int i;

    for(i = 7; i >= 0; i--){
        //Insert smu_values in a auxiliary variable to extract it later
        //Taking the 8 last bits of each Uint16 represeting a char(1byte) and shifting by 8*i position
        //aux |= ((0x00FF & smu_values[i]) << (8*i));
        aux = aux << 8;
        aux |= (0x00FF & smu_values[i]);
    }


    if(id == MSG_ID_SMU_TEMPERATURES){
        for(i = 0; i < NUM_SMU_TEMP; i++)
        {
            temperatures[i] = ConvertTempToKelvin(0x3FF & aux );
            aux>>=10;
        }

    }else if(id == MSG_ID_SMU_SUSPENSIONS){
        for(i = 0; i < NUM_SMU_SUSP; i++)
        {
            suspensions[i] = (Uint32)(0x3FF & aux );
            aux>>=10;
        }
    }

}

void read_BMSLV_message(Uint16 bmslv_values[], int id){
    //TODO implement reading of the BMSLV packets
    int i = 0;
    if (id == 1)
    {
        for (i = 0; i < 8; i=i+2){
            bms_lv_cell[i/2] = (bmslv_values[i] & 0xff) | ((bmslv_values[i+1] & 0xff) << 8);
        }
    } else if (id == 2) {
        for (i = 0; i < 8; i=i+2){
            bms_lv_cell[(i+8)/2] = (bmslv_values[i] & 0xff) | ((bmslv_values[i+1] & 0xff) << 8);
        }
        bms_lv_cell[6] = convert_temp_lv(bms_lv_cell[6]*0.0001);
        bms_lv_cell[7] = convert_temp_lv(bms_lv_cell[7]*0.0001);
    }
}

void read_BMS_VOLTAGE_message(Uint16 bms_values[]){
    Uint16 tmp = 0;
    tmp=(bms_values[0] | bms_values[1]<<8);
    max_bms_voltage = convertBMSvoltage(tmp);
    tmp=(bms_values[2] | bms_values[3]<<8);
    min_bms_voltage = convertBMSvoltage(tmp);
    tmp=(bms_values[4] | bms_values[5]<<8);
    mean_bms_voltage = convertBMSvoltage(tmp);

}

void read_BMS_TEMP_message(Uint16 bms_values[]){
    Uint16 tmp = 0;
      tmp=(bms_values[0] | bms_values[1]<<8);
      max_bms_temp = convertBMStemp(tmp);
      tmp=(bms_values[2] | bms_values[3]<<8);
      min_bms_temp = convertBMStemp(tmp);
      tmp=(bms_values[4] | bms_values[5]<<8);
      mean_bms_temp = convertBMStemp(tmp);
}

void read_power_control_message(Uint16 val[]){
    powersetup[0]=val[0];
    power_limit = val[0]*1000.0f;
}

void read_steering_wheel_message(Uint16 val[], int id){

    int currentPage = display.page;
    if (id == MSG_ID_STEERING_WHEEL_BASE){
        if(val[0] == NEXT_PAGE){
            currentPage++;
            currentPage = currentPage % 10;
            display.page = currentPage;
        }
        else if(val[0] == PREVIOUS_PAGE){
            currentPage = currentPage - 1 + 10;
            currentPage = currentPage % 10;
            display.page = currentPage;
        }else if(val[0] == CALIBRATION){
            if(calibration_status){
                //Z-axe calibration
                //reset_calibration();
                imu_calibration_1(&accelerations);
                calibration_status++;
            }else{
               //Other axes calibration
                imu_calibration_2(&accelerations);
                send_calibration(V);
                calibration_status--;
            }
        }

    }

    if(id == MSG_ID_STEERING_WHEEL_CHANGE_SETUP){
        display.selector = val[0];
    }
    else if(id == MSG_ID_STEERING_WHEEL_BASE && val[0] == CONFIRMATION){
        if(display.page == POWER_CONTROL_PAGE && !R2D_state){
            display.ack = display.selector;
            //manca mandare il messaggio
            powersetup[0]=presets_power[display.ack];
            power_limit = powersetup[0]*1000.0f;
        }else if(display.page == REGEN_PAGE && !R2D_state){
             display.ack = display.selector;
             max_regen_current = presets_regen[display.ack];
        }

    } else if(id == MSG_ID_STEERING_WHEEL_BASE && val[0] == START_LAUNCH) {
        // si vedrà quello che faremo
    }

}

void brakeLight()
{
    if (brake > BRAKE_LIGHT_MIN) {
        GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_ON);  // ON
    } else {
        GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_OFF);  // OFF
    }

}

//da cambiare
void playRTDS()
{
    GPIO_WritePin(RTDS, 1U);  // sound
    CpuTimer2.InterruptCount = 0;
    CpuTimer2Regs.TCR.bit.TSS = 0;      //Start timer 2
    //CPUTimer_startTimer(CPUTIMER1_BASE);    //timer for sound
}

void R2D_On()
{
    playRTDS();
    GPIO_WritePin(R2D, R2D_LED_ON);  // led
//    GPIO_WritePin(POMPA_DX_Abil, 1U);  // pompa dx on
//    GPIO_WritePin(POMPA_SX_Abil, 1U);  // pompa sx on
    GPIO_WritePin(ENABLE_PUMPS, 1U);  // pompa sx off
    GPIO_WritePin(VENTOLA_Abil, 1U);  // ventole on

}

void R2D_Off()
{
    GPIO_WritePin(RTDS, 0U);  // sound
    GPIO_WritePin(R2D, R2D_LED_OFF);  // led
//    GPIO_WritePin(POMPA_DX_Abil, 0U);  // pompa dx off
//    GPIO_WritePin(POMPA_SX_Abil, 0U);  // pompa sx off
    GPIO_WritePin(ENABLE_PUMPS, 0U);  // pompa sx off
    GPIO_WritePin(VENTOLA_Abil, 0U);  // ventole off

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
//  Velocitï¿½ della ventola (duty cycle %) in funzione della temperatura:
//  temperatura > 65ï¿½           ---> ventola spenta
//  65ï¿½ < temperatura < 75ï¿½     ---> velocitï¿½ scala linearmente da 20% a 100%
//  75ï¿½ > temperatura           ---> 100%
//

Uint16 fanSpeedFunction(int temp){
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
//        GPIO_WritePin(POMPA_DX_Abil, 1U);  // pompa dx on
//        GPIO_WritePin(POMPA_SX_Abil, 1U);  // pompa sx on
//    }
//    else
//    {
//        GPIO_WritePin(POMPA_DX_Abil, 0U);  // pompa dx off
//        GPIO_WritePin(POMPA_SX_Abil, 0U);  // pompa sx off
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

    Temps[0]=getTempAvPT1000(TempRadOutLC_temp);
    Temps[1]=getTempAvPT1000(TempRadOutRC_temp);
    Temps[2]=getTempAvPT1000(TempRadInLC_temp);
    Temps[3]=getTempAvPT1000(TempRadInRC_temp);
    Temps[4]=0;
    Temps[5]=0;
    Temps[6]=leftFanSpeed;
    Temps[7]=rightFanSpeed;

//    Temps[0]=getTempAvPT1000(readADC(TEMP_RAD_IN));
//    Temps[1]=getTempAvPT1000(readADC(TEMP_RAD_OUT));
//    Temps[2]=getTempZTP135SR(readADC(TEMP_TYRE_FRONT_L));
//    Temps[3]=getTempZTP135SR(readADC(TEMP_TYRE_FRONT_R));
//    Temps[4]=getTempZTP135SR(readADC(TEMP_TYRE_BACK_L));
//    Temps[5]=getTempZTP135SR(readADC(TEMP_TYRE_BACK_R));
//    Temps[6]=leftFanSpeed;
//    Temps[7]=rightFanSpeed;
}


void checkStatus()
{
    //STATUS
    //bit       | 7  |    6    |    5     |  4  |     3     |    2    |    1     | 0  |
    //meaning   | RF | imp_b_t | brk_disc | r2d | PRECHARGE | TEMP_OK | LV_ALARM | HV |

    Uint16 mstatus = 0b00000000;
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
    update_log_values();
    update_shared_mem();
}
void update_log_values()
{
//    uint16_t index;
//
//    //FOR TESTING
//    status_log.throttle_shared = increment;
//    status_log.actualVelocityKMH_shared = increment;
//    status_log.brake_shared = increment;
//    status_log.status_shared = increment;
//    status_log.brakePress_shared = increment;
//    status_log.steering_shared = increment;
//
//    gpio_log.Sdc1_shared = 1;
//
//    for(index = 0; index < 8; index++)
//    {
//        Temps_shared[index] = increment;
//    }
//
//    for(index = 0; index < 4; index++)
//    {
//        motorSetP_shared[index].AMK_TargetVelocity = increment;
//    }
//
//    EALLOW;
//    GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
//    EDIS;
//
//
//    increment++;

    //PARTE DA AGGIUNGERE PER I TEST. COMMENTARE PER FARE TEST FITTIZI

    int i;
    //Temps
    for(i = 0; i < 8; i++)
    {
        Temps_shared[i] = Temps[i];
    }

    for(i = 0; i < 8; i++)
    {
        bms_lv_shared[i] = bms_lv_cell[i];
    }

    //MotorValues
    for(i = 0; i < 4; i++)
    {
        motorVal1_shared[i].AMK_ActualVelocity = motorVal1[i].AMK_ActualVelocity;
        motorVal1_shared[i].AMK_Current = motorVal1[i].AMK_Current;
        motorVal1_shared[i].AMK_MagnetizingCurrent  = motorVal1[i].AMK_MagnetizingCurrent;
        motorVal1_shared[i].AMK_TorqueCurrent = motorVal1[i].AMK_TorqueCurrent;
        motorVal1_shared[i].AMK_bDcOn = motorVal1[i].AMK_bDcOn;
        motorVal1_shared[i].AMK_bDerating = motorVal1[i].AMK_bDerating;
        motorVal1_shared[i].AMK_bError = motorVal1[i].AMK_bError;
        motorVal1_shared[i].AMK_bInverterOn = motorVal1[i].AMK_bInverterOn;
        motorVal1_shared[i].AMK_bQuitDcOn = motorVal1[i].AMK_bQuitDcOn;
        motorVal1_shared[i].AMK_bQuitInverterOn = motorVal1[i].AMK_bQuitInverterOn;
        motorVal1_shared[i].AMK_bSystemReady = motorVal1[i].AMK_bSystemReady;
        motorVal1_shared[i].AMK_bWarn = motorVal1[i].AMK_bWarn;

        motorVal2_shared[i].AMK_ErrorInfo = motorVal2[i].AMK_ErrorInfo;
        motorVal2_shared[i].AMK_TempIGBT = motorVal2[i].AMK_TempIGBT;
        motorVal2_shared[i].AMK_TempInverter = motorVal2[i].AMK_TempInverter;
        motorVal2_shared[i].AMK_TempMotor = motorVal2[i].AMK_TempMotor;
    }

    //MotorSetPoints

    for(i = 0; i < 4; i++)
    {
        motorSetP_shared[i].AMK_TargetVelocity = motorSetP[i].AMK_TargetVelocity;
        motorSetP_shared[i].AMK_TorqueLimitNegative = motorSetP[i].AMK_TorqueLimitNegative;
        motorSetP_shared[i].AMK_TorqueLimitPositive = motorSetP[i].AMK_TorqueLimitPositive;
        motorSetP_shared[i].AMK_bDcOn = motorSetP[i].AMK_bDcOn;
        motorSetP_shared[i].AMK_bEnable = motorSetP[i].AMK_bEnable;
        motorSetP_shared[i].AMK_bErrorReset = motorSetP[i].AMK_bErrorReset;
        motorSetP_shared[i].AMK_bInverterOn = motorSetP[i].AMK_bInverterOn;
    }

    //Status
    status_log.throttle_shared = throttle;
    status_log.actualVelocityKMH_shared = actualVelocityKMH;
    status_log.brake_shared = brake;
    status_log.status_shared = status;
    status_log.brakePress_shared = (int)getPressAvSP100(BrakePress_temp);
    status_log.steering_shared = steering;

    //Bms
    bms_log.max_bms_temp_shared = max_bms_temp;
    bms_log.mean_bms_temp_shared = mean_bms_temp;
    bms_log.min_bms_temp_shared = min_bms_temp;
    bms_log.max_bms_voltage_shared = max_bms_voltage;
    bms_log.mean_bms_voltage_shared = mean_bms_voltage;
    bms_log.min_bms_voltage_shared = min_bms_voltage;



    //Sendyne
    sendyne_log.sendyne_voltage_shared = sendyne_voltage;
    sendyne_log.sendyne_current_shared = sendyne_current;
    sendyne_log.curr_sens_shared = 0; //nuovo da aggiungere
    sendyne_log.total_power_shared = total_power;

    //FanSpeed
    fanspeed_log.leftFanSpeed_shared = leftFanSpeed;
    fanspeed_log.rightFanSpeed_shared = rightFanSpeed;

    //Imu
    for(i = 0; i < 3; i++)
    {
        imu_log.accelerations_shared[i] = accelerations[i];
        imu_log.omegas_shared[i] = omegas[i];
    }
    for(i = 0; i < 4; i++){
        imu_log.suspensions_shared[i] = suspensions[i];
        imu_log.temperatures_shared[i] = temperatures[i];
    }

    imu_log.temperatures_shared[4] = temperatures[4];

}

void update_shared_mem()
{
    int index;
    for(index = 0; index < 4; index++)
    {
        sh.motorVal1[index] = motorVal1_shared[index];
        sh.motorVal2[index] = motorVal2_shared[index];
        sh.motorSetP[index] = motorSetP_shared[index];
    }
    memcpy(sh.Temps, Temps_shared, 8);
    memcpy(sh.bms_lv_cell, bms_lv_shared, 8);
    sh.imu = imu_log;
    sh.fanSpeed = fanspeed_log;
    sh.sendyne = sendyne_log;
    sh.bms = bms_log;
    sh.status = status_log;
    sh.gpio = gpio_log;
}

void sendStatusToLogger()
{
//    Uint16 tmp[7];
//
//    tmp[0] = throttle;
//    tmp[1] = steering;
//    tmp[2] = steering >>8;
//    tmp[3] = brake;
//    tmp[4] = getPressAvSP100(readADC(BRAKE_PRS_BACK)); //brake_pressure;
//    tmp[5] = status;
//    tmp[6] = (Uint16) ((int)actualVelocityKMH);
//
//    CAN_sendMessage(CANA_BASE, OBJ_ID_CAR_STATUS, 7, tmp);
}

void sendTempsToLogger()
{
//    CAN_sendMessage(CANA_BASE, OBJ_ID_TEMPS, 8, Temps);
}

void sendSetpointsToLogger(){

//    Uint16 setpoints[8];
//    setpoints[0]=(Uint16)(posTorquesNM[0]*10);
//    setpoints[1]=(Uint16)(posTorquesNM[1]*10);
//    setpoints[2]=(Uint16)(posTorquesNM[2]*10);
//    setpoints[3]=(Uint16)(posTorquesNM[3]*10);
//    setpoints[4]=(Uint16)(negTorquesNM[0]*-10);
//    setpoints[5]=(Uint16)(negTorquesNM[1]*-10);
//    setpoints[6]=(Uint16)(negTorquesNM[2]*-10);
//    setpoints[7]=(Uint16)(negTorquesNM[3]*-10);
//
//    CAN_sendMessage(CANA_BASE, OBJ_ID_AMK_SETPOINTS, 8, setpoints);

}

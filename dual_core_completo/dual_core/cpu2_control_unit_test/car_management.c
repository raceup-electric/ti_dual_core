#include "car_management.h"

int calibration_status = 0;
int NUM_SMU_TEMP = 5;
int NUM_SMU_SUSP = 4;
int fan_flag = 0;


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
    last_imu_message_time = time_elapsed;
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
        accelerations[X] = accelerations[X] - 0.5*(accelerations[X] - (uint32_to_float(aux_1)));
        accelerations[Y] = accelerations[Y] - 0.5*(accelerations[Y] - (-uint32_to_float(aux_2)));
    }
    else if (id == MSG_ID_IMU_2)
    {
        accelerations[Z] = accelerations[Z] - 0.5*(accelerations[Z] - (uint32_to_float(aux_1)));
        apply_calibration();
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
        Uint16 tmp = 0;
        for(i = 0; i < 8; i += 2)
        {
            tmp= (smu_values[i] | (smu_values[i+1]<<8));
            temperatures[i/2] = ConvertTempToKelvin(tmp);
        }
    }
    else if (id == MSG_ID_SMU_TEMPERATURES + 1){
        Uint16 tmp = 0;
        for(i = 0; i < 8; i += 2)
        {
            tmp= (smu_values[i] | (smu_values[i+1]<<8));
            temperatures[i/2 + 4] = ConvertTempToKelvin(tmp);
        }
    }
    else if (id == MSG_ID_SMU_SUSPENSIONS){
        for(i = 0; i < NUM_SMU_SUSP; i++)
        {
            suspensions[i] = (Uint32) (-(0x3FF & aux) + SUSP_ANG_C)/SUSP_ANG_M;
            aux>>=10;
        }
    }

}

void read_BMSLV_message(Uint16 bmslv_values[], int id){
    //TODO implement reading of the BMSLV packets
    int i = 0;
    if (id == MSG_ID_BMS_LV_1)
    {
        for (i = 0; i < 8; i=i+2){
            bms_lv_cell[i/2] = (bmslv_values[i] & 0xff) | ((bmslv_values[i+1] & 0xff) << 8);
            bms_lv_cell[i/2] *= 0.0001;
        }
    } else if (id == MSG_ID_BMS_LV_2) {
        for (i = 0; i < 8; i=i+2){
            bms_lv_cell[(i+8)/2] = (bmslv_values[i] & 0xff) | ((bmslv_values[i+1] & 0xff) << 8);
            bms_lv_cell[(i+8)/2] *= 0.0001;
        }
        bms_lv_cell[6] = convert_temp_lv(bms_lv_cell[6]);
        bms_lv_cell[7] = convert_temp_lv(bms_lv_cell[7]);
    }

    /*int i = 0;
    if (id == MSG_ID_BMS_LV_1)
    {
        for (i = 0; i < 4; i++){
            bms_lv_cell[i] = bmslv_values[i]*0.0001;
        }
    } else if (id == MSG_ID_BMS_LV_2) {
        for (i = 0; i < 2; i++){
            bms_lv_cell[i+4] = bmslv_values[i]*0.0001;
        }
        bms_lv_cell[6] = convert_temp_lv(bms_lv_cell[6]*0.0001);
        bms_lv_cell[7] = convert_temp_lv(bms_lv_cell[7]*0.0001);
    }*/
}

void read_BMS_VOLTAGE_message(Uint16 bms_values[]){
    Uint16 tmp = 0;
    tmp=(bms_values[0] | (bms_values[1]<<8));
    max_bms_voltage = convertBMSvoltage(tmp);
    tmp=(bms_values[2] | (bms_values[3]<<8));
    min_bms_voltage = convertBMSvoltage(tmp);
    tmp=(bms_values[4] | (bms_values[5]<<8));
    mean_bms_voltage = convertBMSvoltage(tmp);
    tmp=(bms_values[6] | (bms_values[7]<<8));
    bms_bitmap = tmp;

}

void read_BMS_TEMP_message(Uint16 bms_values[]){
    Uint16 tmp = 0;
      tmp=(bms_values[0] | (bms_values[1]<<8));
      max_bms_temp = tmp;
      tmp=(bms_values[2] | (bms_values[3]<<8));
      min_bms_temp = tmp;
      tmp=(bms_values[4] | (bms_values[5]<<8));
      mean_bms_temp = tmp;
      max_temp_nslave = bms_values[6];

}

void read_steering_wheel_message(Uint16 val[], int id){

    /*
     * PAGE INCREASE/DECREASE
     */
    int currentPage = display.page;
    static int driving_page_index = 0;
    static Uint16 old_val = 99;
    static int over_macro = 0;
    static int over_setup = 0;
    static int over_pedal = 0;
    if (id == MSG_ID_STEERING_WHEEL_BASE){
        if(val[0] == NEXT_PAGE){

            if(screen_mode == SCREEN_DEBUG){
                currentPage++;
                currentPage = currentPage % MAX_PAGE_NUMBER;
                display.page = currentPage;
            } else if(screen_mode == SCREEN_DRIVING){
                driving_page_index++;
                driving_page_index = driving_page_index % MAX_DRIVING_PAGE;
                currentPage = driving_page_num[driving_page_index];
                display.page = currentPage;
            }

        }
        else if(val[0] == PREVIOUS_PAGE){
            currentPage = currentPage - 1 + MAX_PAGE_NUMBER;
            currentPage = currentPage % MAX_PAGE_NUMBER;
            if(screen_mode == SCREEN_DEBUG){
                display.page = currentPage;
            } else if(screen_mode == SCREEN_DRIVING){
                driving_page_index = (driving_page_index - 1 + MAX_DRIVING_PAGE)  % MAX_DRIVING_PAGE;
                currentPage = driving_page_num[driving_page_index];
                display.page = currentPage;
            }
        }else if(val[0] == START_LAUNCH){
            /*
             * To activate launch you must be: R2d and not moving
             */
            if(R2D_state && actualVelocityKMH < 1.f){
                is_launch_inserted = true;
            }
        }
        /*
         * Selects between SCREEN_DEBUG and SCREEN_DRIVING mode
         */
        else if(val[0] == CHANGE_SCREEN_MODE){
            screen_mode++;
            screen_mode %= 2;
            if (screen_mode == SCREEN_DRIVING){
                driving_page_index = 0;
                display.page = driving_page_num[driving_page_index];
            }
            else if (screen_mode == SCREEN_DEBUG)
                display.page = 0;
        }

    }

    /*
     * SELECTOR 1 UPDATE
     */
    if(id == MSG_ID_STEERING_WHEEL_CHANGE_SETUP && currentPage == SETUP_PAGE){
        if(old_val == 8 && val[0] == 0x00)
           over_setup++;
       else if(old_val == 0 && val[0] == 0x08)
           over_setup--;

       display.selector_setup = (val[0] + 9*over_setup) % 7;

       old_val = val[0];
    }
    else if(id == MSG_ID_STEERING_WHEEL_CHANGE_SETUP && currentPage == PEDAL_SETUP_PAGE){
        if(old_val == 8 && val[0] == 0x00)
           over_pedal++;
       else if(old_val == 0 && val[0] == 0x08)
           over_pedal--;

       display.selector_pedal_setup = (val[0] + 9*over_pedal) % 4;

       old_val = val[0];
    }
    else if(id == MSG_ID_STEERING_WHEEL_CHANGE_SETUP && currentPage == MACROS_PAGE){


        if(old_val == 8 && val[0] == 0x00)
            over_macro++;
        else if(old_val == 0 && val[0] == 0x08)
            over_macro--;

        display.selector_macros = (val[0] + 9*over_macro) % 6;

        old_val = val[0];

    }
    else if(id == MSG_ID_STEERING_WHEEL_CHANGE_SETUP && currentPage == FANSPEED_PAGE){

       // if(!(val[0] % 2 == 1 && !display.manual_speed_selector))
            if(old_val == 8 && val[0] == 0x00)
                display.selector_fan = (val[0]+1) % 2;
            else
                display.selector_fan = val[0] % 2;

            old_val = val[0];
    }

    /*
     * SELECTOR 2 UPDATE
     */
    if(id == MSG_ID_STEERING_WHEEL_CHANGE_SETUP_2 && currentPage == SETUP_PAGE){

        if (val[0] < 6){
            if (display.selector_setup == 0)
                display.selector_regen = val[0] % 6;
            else if (display.selector_setup == 1)
                display.selector_maxpos = val[0] % 5;
            else if (display.selector_setup == 2)
                display.selector_maxneg = val[0] % 5;
            else if (display.selector_setup == 3)
                display.selector_power = val[0] % 8;
            else if (display.selector_setup == 4)
                display.selector_speed = val[0] % 6;
            else if (display.selector_setup == 5)
                display.selector_trqr = val[0] % 6;
            else if (display.selector_setup == 6)
                display.selector_trqf = val[0] % 6;
        }
    }

    if(id == MSG_ID_STEERING_WHEEL_CHANGE_SETUP_2 && currentPage == FANSPEED_PAGE){
        if (display.selector_fan == 1)
            if (val[0] == 0)
                display.selector_speed_fan = 0;
            else
                display.selector_speed_fan = (val[0] % 9)*10 + 20;
    }

    /*
     * ACKNOLEDGE UPDATE
     */
    if(id == MSG_ID_STEERING_WHEEL_BASE && val[0] == CONFIRMATION){
        if(display.page == SETUP_PAGE && !R2D_state){
            display.ack_setup = display.selector_setup;

            if (display.ack_setup == 0)
                car_settings.max_regen_current= car_settings.presets_regen[display.selector_regen];
            else if (display.ack_setup == 1)
                car_settings.max_pos_torque = car_settings.presets_max_pos[display.selector_maxpos];
            else if (display.ack_setup == 2)
                car_settings.max_neg_torque = car_settings.presets_max_neg[display.selector_maxneg];
            else if (display.ack_setup == 3)
                car_settings.power_limit = car_settings.presets_power[display.selector_power];
            else if (display.ack_setup == 4)
                car_settings.max_speed = car_settings.presets_speed[display.selector_speed];

            /*
             *  Torques can be modified only if torque vectoring is disabled
             */
            if (!macros_settings.torque_vectoring){
                if (display.ack_setup == 5)
                    car_settings.rear_motor_scale = car_settings.presets_coppie_rear[display.selector_trqr];
                if (display.ack_setup == 6)
                    car_settings.front_motor_scale = car_settings.presets_coppie_front[display.selector_trqf];
            }
        }
        else if(display.page == PEDAL_SETUP_PAGE && !R2D_state){
            display.ack_pedal_setup = display.selector_pedal_setup;

            switch(display.ack_pedal_setup){

            case(0):
                pedals_log.acc1_high_calibration = pedals_log.acc_pot1_shared-30;
                pedals_log.acc2_high_calibration = pedals_log.acc_pot2_shared-30;
            break;

            case(1):
                pedals_log.acc1_low_calibration = pedals_log.acc_pot1_shared+40;
                pedals_log.acc2_low_calibration = pedals_log.acc_pot2_shared+40;
            break;

            case(2):
                pedals_log.brk_high_calibration = pedals_log.brk_pot_shared-30;
            break;

            case(3):
                pedals_log.brk_low_calibration = pedals_log.brk_pot_shared+40;
            break;

            }
       }
       else if(display.page == MACROS_PAGE && !R2D_state){
            display.ack_macros = display.selector_macros;

            if (display.ack_macros == 0){
                macros_settings.torque_vectoring = !macros_settings.torque_vectoring;
                /*
                 * After disabling TV, rear_motor_scale and front_motor_scale go back to default values
                 */
                if(macros_settings.torque_vectoring){
                    car_settings.rear_motor_scale = 1.0f;
                    car_settings.front_motor_scale = 1.0f;
                    repFz[0] = 0.6;
                    repFz[1] = 0.6;
                    repFz[2] = 0.4;
                    repFz[3] = 0.4;
                } else {
                    car_settings.rear_motor_scale = REAR_MOTOR_SCALE;
                    car_settings.front_motor_scale = FRONT_MOTOR_SCALE;
                }
            }
            else if (display.ack_macros == 1)
                macros_settings.traction_ctrl = !macros_settings.traction_ctrl;
            else if (display.ack_macros == 2)
                macros_settings.one_pedal = !macros_settings.one_pedal;
            else if (display.ack_macros == 3)
                macros_settings.thermal_power_ctrl = !macros_settings.thermal_power_ctrl;
            else if (display.ack_macros == 4)
                macros_settings.reg_brake = !macros_settings.reg_brake;
            else if (display.ack_macros == 5) {
                // unused
                }
      }
       else if (display.page == FANSPEED_PAGE && !R2D_state){

           if(!(display.selector_fan == 1 && !display.manual_speed_selector)){ //ack speed fan, only if manual_selector is true
               display.ack_fan = display.selector_fan;

               if(display.ack_fan == 0){
                   display.manual_speed_selector = !display.manual_speed_selector;
               }
               else if(display.ack_fan == 1){
                   leftFanSpeed = display.selector_speed_fan;
                   rightFanSpeed = display.selector_speed_fan;
               }
           }
       }

    }
}

/*
 * 2023 - logica invertita
 */
void brakeLight()
{
    if (brake > BRAKE_LIGHT_MIN || brakeReq > BRAKE_LIGHT_MIN ) {
        GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_OFF);  // ON
    } else {
        GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_ON);  // OFF
    }

}

//da cambiare
void playRTDS()
{
    GPIO_WritePin(RTDS, 1U);  // sound
    CpuTimer2.InterruptCount = 0;
    CpuTimer2Regs.TCR.bit.TSS = 0;      //Start timer 2
}

void R2D_On()
{
    playRTDS();
    GPIO_WritePin(R2D, R2D_LED_ON);  // led


    //GPIO_WritePin(ENABLE_PUMPS, 1U);  // pompa on - ok cooling
    //GPIO_WritePin(VENTOLA_Abil, 1U);  // ventole on

    fan_enable = 1;
    pump_enable = 1;
}

void R2D_Off()
{
    GPIO_WritePin(RTDS, 0U);  // sound
    GPIO_WritePin(R2D, R2D_LED_OFF);  // led

    //GPIO_WritePin(ENABLE_PUMPS, 1U);  // pompa on - ok cooling
    //GPIO_WritePin(VENTOLA_Abil, 0U);  // ventole off

    fan_enable = 0;
    pump_enable = 1;
}

/*
 * R2D initialization steps:
 *  1 - Precharge completed -> HV is ON
 *  2 - RF activation
 *  3 - Brake
 *  4 - press r2d button
 */
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


    /*
     * if we exit r2d and rf are turn off
     * we can repeat initialization
     */
    if(!R2D_state && !readRF()){
       R2D_first_state = 1;
    }
    else{
        R2D_first_state = 0;
    }

    /*
     * r2d will stay off until Hv is on and Rf are activated
     */
    if(!isHVOn() || !readRF()){
        R2D_state = 0;
        R2D_Off();
    }
}

/*
 * Battery pack tension is given indipendently by every motor.
 * The function seems complex because takes in consideration the case
 * that one or more motor are inactive.
 */
void computeBatteryPackTension()
{
    int j = 0, active_motors = 0;
    Uint16 tensions[4];
    Uint16 active[4];
    Uint16 mean, mean_of_squared, max = 0;

    for (j=0; j < 4; j++)
    {
        active[j] = 1;
        tensions[j] = motorVal1[j].AMK_Voltage;
        if ( tensions[j] > max)
        {
            max = tensions[j];
        }
    }

    for (j = 0; j < 4; j++)
    {
        if(tensions[j] < max - 40)
        {
            active[j] = 0;
        }
    }

    for (j=0; j < 4; j++)
    {
        if(active[j] > 0)
            active_motors++;
        mean += tensions[j]*active[j];
        mean_of_squared += tensions[j]*tensions[j]*active[j];
    }

    if(active_motors != 0)
    {
        mean /= active_motors;
        mean_of_squared /= active_motors;
    }else{
        mean = 0;
        mean_of_squared = 0;
    }

    batteryPackTension = mean;
    total_power = batteryPackTension*lem_current;

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

/*
 * Tramaccio: we wait 500ms before stating that an inverter has no Hv
 */
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

/*
 * Tramaccio: we wait 500ms before stating that an Rf is not active
 */
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

/*
 * Check if High Voltage is On. inverterHV[i] is updated in checkHv function
 */
bool isHVOn()
{
    bool hv = false;

    int i;
    for (i = 0; i < NUM_OF_MOTORS; i++)
    {

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

/*
 * Check if rf are active
 */
bool readRF()
{
    bool rf = false;

    int i;
    for (i = 0; i < NUM_OF_MOTORS; i++) {
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

/*
 * Managing brake and throttle implausibilities
 */
void checkImplausibility()
{
    /*
     * First implausibility
     */
    if (implBrakeAndThrottle)
    {
        /*
         * if implausiblity occurred and throttle is over 5%, implausibility reamins
         */
        implBrakeAndThrottle = (throttle > 5);  // regardless of brake
    }
    else
    {
        implBrakeAndThrottle = ((brake > BRAKE_IMPL_THRESHOLD) && (throttle > THROTTLE_IMPL_THRESHOLD));
    }

    /*
     * Second implausibility
     */
    brakeWhenSlow = brake > 10 && actualVelocityKMH <= 5.f;
}

/*
 * Important: fans should be active after R2d
 */
void fanControl()
{
    if (fan_enable){
        /*
         * fan activation threshold is based on max temp among all inverters
         */
        int leftTemp = fmax(motorVal2[0].AMK_TempInverter, motorVal2[2].AMK_TempInverter);
        int rightTemp = fmax(motorVal2[1].AMK_TempInverter, motorVal2[3].AMK_TempInverter);
        int maxTemp = fmax(leftTemp, rightTemp);

        if(!display.manual_speed_selector){

            leftFanSpeed = fanSpeedFunction(maxTemp);
            rightFanSpeed = leftFanSpeed;
        }

    }
    else {
        setFanSpeed(100);
    }


    setFanSpeed(100 - leftFanSpeed);
}

/*
 * Always active at 20% then linearly increases from 60% to 80% when temperature is above between 60° and 80°
 */

Uint16 fanSpeedFunction(int temp){
//#ifndef CONST_FAN_SPEED
//    if(fan_flag && temp > 45 && temp < FAN_MIN_TEMP){
//        return 10;
//    }
//    if (temp < FAN_MIN_TEMP){
//        fan_flag = 0;
//        return 0;
//
//    }
//    else if (temp >  FAN_MAX_TEMP){
//        fan_flag = 1;
//        return 100;
//    }else {
//        fan_flag = 1;
//        return (9*temp) - 440;
//    }

    /*
     * Reminder: fans actually work with pwm greater or equal than 40%
     */
    if(temp <= 60){
        return 40;
    } else if (temp >= 80) {
        return 80;
    } else {
        return (2*temp) - 80;
    }

//#endif
/*
#ifdef CONST_FAN_SPEED
    return 50;
#endif
*/

}

/*
 * Only for test bench. DO NOT USE IN RUN
 */
Uint16 fanSpeedFunctionDebug(int temp){
#ifndef CONST_FAN_SPEED
    if(fan_flag && temp > 15 && temp < 20){
        return 10;
    }
    if (temp < 20){
        fan_flag = 0;
        return 0;

    }
    else if (temp >  30){
        return 100;
    }else {
        fan_flag = 1;
        return (9*temp) - 170;
    }
#endif

#ifdef CONST_FAN_SPEED
    return 50;
#endif
}

/*
 * Status represent an easy debug variable, visible on first display page
 */
void checkStatus()
{
    //STATUS
    //bit       | 7  |    6    |    5     |  4  |     3     |    2        |    1     | 0  |
    //meaning   | RF | imp_b_t | brk_disc | r2d | PRECHARGE | Fault check | LV_ALARM | HV |

    Uint32 mstatus = 0x0000000F;
    if (isHVOn())
        mstatus |= 0x000000F0;
    if (R2D_state)
        mstatus |= 0x00000F00;
    if (Air1_State)
        mstatus |= 0x0000F000;
    if (Air2_State)
        mstatus |= 0x000F0000;
    if (readRF())
        mstatus |= 0x00F00000;
    if (implBrakeAndThrottle)
        mstatus |= 0x0F000000;
    if (brk_disconnected)
        mstatus |= 0xF0000000;

    status = mstatus;
}

/*
 * Emergency screen triggers when speed is more than 10km/h, Hv is on and AIR1 is closed
 */
void emergencyScreen()
{
    if (!Air1_State && actualVelocityKMH > 10 && batteryPackTension > 60){
        display.emergencyBrk_active = 1;
    }else{
        display.emergencyBrk_active = 0;
    }
        //display.page = BRAKE_PAGE;
}

/*
 * Data are updated locally and than copied in shared memory
 */
void sendDataToLogger()
{
    update_log_values();
    update_shared_mem();
}
void update_log_values()
{
    int i;

    for(i = 0; i < 8; i++)
    {
        bms_lv_shared[i] = bms_lv_cell[i];
    }

    //MotorValues
    for(i = 0; i < 4; i++)
    {
        motorVal1_shared[i].AMK_ActualVelocity = motorVal1[i].AMK_ActualVelocity;
        motorVal1_shared[i].AMK_Current = motorVal1[i].AMK_Current;
        motorVal1_shared[i].AMK_Voltage  = motorVal1[i].AMK_Voltage;
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
    bms_log.max_bms_temp_nslave_shared = max_temp_nslave;
    bms_log.bms_bitmap_shared = bms_bitmap;


    power_log.batteryPack_voltage_shared = batteryPackTension;
    power_log.lem_current_shared = lem_current;
    power_log.curr_sens_shared = 0;
    power_log.total_power_shared = total_power;

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
    }

    for(i = 0; i < 8; i++){
        imu_log.temperatures_shared[i] = temperatures[i];
    }



    //Pedals update
    pedals_log.acc_pot1_shared = AccPot1;
    pedals_log.acc_pot2_shared = AccPot2;
    pedals_log.brk_pot_shared = BrkPot;
    pedals_log.throttle_req_shared = throttleReq;
    pedals_log.brk_req_shared = brakeReq;

    //Power setup update
    power_setup_log.max_speed_shared = car_settings.max_speed;
    //power_setup_log.rear_motor_scale_shared = rear_motor_scale;
    //power_setup_log.front_motor_scale_shared = front_motor_scale;
    power_setup_log.power_limit_shared = car_settings.power_limit;
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
    //memcpy(sh.Temps, Temps_shared, 8);
    int i;
    for(i = 0; i < 8; i++){
        sh.bms_lv[i] = bms_lv_shared[i];
    }
    sh.imu = imu_log;
    sh.fanSpeed = fanspeed_log;
    sh.power = power_log;
    sh.bms = bms_log;
    sh.status = status_log;
    sh.gpio = gpio_log;
    sh.pedals = pedals_log;
    sh.power_setup = power_setup_log;
}


#include "car_management.h"
#include "adc_management.h"
#include "global_definitions.h"
#include "sys/_stdint.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>

#define MAX_GPS_LEN 81

int calibration_status = 0;
int NUM_SMU_SUSP = 2;
int fan_flag = 0;

#ifdef DEBUG_HV
bool hvDebugging = false; // debug
bool hvGoneWrong[4] = {1, 1, 1, 1};

bool rfDebugging = false; // debug
bool rfGoneWrong[4] = {1, 1, 1, 1};

#endif

#if defined(DEBUG_NO_HV) || defined(DEBUG_HV)
int leftFanDebug = 0;
int rightFanDebug = 0;
#endif



void read_map_sw_message(Uint16 val[])
{
    time_elapsed_map = time_elapsed;

    Uint16 power_index = val[0] & 0xF;
    Uint16 regen_index = (val[0] >> 4) & 0xF;
    Uint16 repartition_index = val[1] & 0xF;

    car_settings.power_limit = presets_power[power_index];
    rtP.Pmax = car_settings.power_limit;
    car_settings.regen_current_scale = presets_regen[regen_index];
    car_settings.max_regen_current = PEAK_REGEN_CURRENT * car_settings.regen_current_scale;

    car_settings.rear_motor_repartition = presets_repartition[(repartition_index)*2];
    car_settings.front_motor_repartition = presets_repartition[(repartition_index)*2 +1];

    if (!repartition_index)
        car_settings.torque_vectoring = true;
    else 
        car_settings.torque_vectoring = false;

}

void read_paddle_sw_message(Uint16 val)
{
    time_elapsed_paddle = time_elapsed;
    paddle = val;
}


void read_LEM_message(unsigned char lem_values[])
{
    uint32_t reassembled_data = 0;
    uint16_t tmp = lem_values[0];
    tmp ^= 1 << 7;
    reassembled_data |= ((uint32_t)(tmp) << 24);
    reassembled_data |= ((uint32_t)(lem_values[1]) << 16);
    reassembled_data |= ((uint32_t)(lem_values[2]) << 8);
    reassembled_data |= ((uint32_t)(lem_values[3]) << 0);
    lem_current = -(int32_t)(reassembled_data) / 1000.0;
}

void read_IMU_message(Uint16 imu_values[], int id)
{
    last_imu_message_time = time_elapsed;
    uint32_t aux_1 = 0;
    uint32_t aux_2 = 0;

    aux_1 |= ((int32_t)(imu_values[3]) << 24);
    aux_1 |= ((int32_t)(imu_values[2]) << 16);
    aux_1 |= ((int32_t)(imu_values[1]) << 8);
    aux_1 |= ((int32_t)(imu_values[0]) << 0);

    aux_2 |= ((int32_t)(imu_values[7]) << 24);
    aux_2 |= ((int32_t)(imu_values[6]) << 16);
    aux_2 |= ((int32_t)(imu_values[5]) << 8);
    aux_2 |= ((int32_t)(imu_values[4]) << 0);

    switch (id)
    {
    case MSG_ID_IMU_1:
        accelerations[X] = accelerations[X] - 0.5 * (accelerations[X] - (uint32_to_float(aux_1)));
        accelerations[Y] = accelerations[Y] - 0.5 * (accelerations[Y] - (-uint32_to_float(aux_2)));
        break;
    case MSG_ID_IMU_2:
        accelerations[Z] = accelerations[Z] - 0.5 * (accelerations[Z] - (uint32_to_float(aux_1)));
        apply_calibration();
        omegas[X] = uint32_to_float(aux_2);
        break;
    case MSG_ID_IMU_3:
        omegas[Y] = uint32_to_float(aux_1);
        omegas[Z] = uint32_to_float(aux_2);
        break;
    }
}

void read_SMU_Message(Uint16 smu_values[], int id)
{

    uint64_t aux = 0;
    int i;

    for (i = 7; i >= 0; i--)
    {
        // Insert smu_values in a auxiliary variable to extract it later
        // Taking the 8 last bits of each Uint16 represeting a char(1byte) and shifting by 8*i position
        // aux |= ((0x00FF & smu_values[i]) << (8*i));
        aux = aux << 8;
        aux |= (0x00FF & smu_values[i]);
    }

    switch (id)
    {
    case MSG_ID_SMU_TEMPERATURES:
        for (i = 0; i < 8; i += 2)
        {
            temperatures[i / 2] = (smu_values[i] | (smu_values[i + 1] << 8));
        }
        break;
    case (MSG_ID_SMU_TEMPERATURES + 1):
        for (i = 0; i < 8; i += 2)
        {
            temperatures[i / 2 + 4] = (smu_values[i] | (smu_values[i + 1] << 8));
        }
        break;
    case MSG_ID_SMU_SUSPENSIONS:
        for (i = 0; i < NUM_SMU_SUSP; i++)
        {
            suspensions[2+i] = (0xFFF & aux) / 10;
            aux >>= 12;
        }
        break;
    }
}

void read_BMSLV_message(Uint16 bmslv_values[], int id)
{
    // TODO implement reading of the BMSLV packets
    int i = 0;
    if (id == MSG_ID_BMS_LV_1)
    {
        for (i = 0; i < 8; i = i + 2)
        {
            bms_lv_cell[i / 2] = (bmslv_values[i] & 0xff) | ((bmslv_values[i + 1] & 0xff) << 8);
            bms_lv_cell[i / 2] *= 0.0001;
        }
    }
    else if (id == MSG_ID_BMS_LV_2)
    {
        for (i = 0; i < 8; i = i + 2)
        {
            bms_lv_cell[(i + 8) / 2] = (bmslv_values[i] & 0xff) | ((bmslv_values[i + 1] & 0xff) << 8);
            bms_lv_cell[(i + 8) / 2] *= 0.0001;
        }
        bms_lv_cell[6] = convert_temp_lv(bms_lv_cell[6]);
        bms_lv_cell[7] = convert_temp_lv(bms_lv_cell[7]);
    }
}

void read_BMS_VOLTAGE_message(Uint16 bms_values[])
{
    Uint16 tmp = 0;
    tmp = (bms_values[0] | (bms_values[1] << 8));
    max_bms_voltage = convertBMSvoltage(tmp);
    tmp = (bms_values[2] | (bms_values[3] << 8));
    min_bms_voltage = convertBMSvoltage(tmp);
    tmp = (bms_values[4] | (bms_values[5] << 8));
    mean_bms_voltage = convertBMSvoltage(tmp);
    tmp = (bms_values[6] | (bms_values[7] << 8));
    bms_bitmap = tmp;
}

void read_BMS_TEMP_message(Uint16 bms_values[])
{
    Uint16 tmp = 0;
    tmp = (bms_values[0] | (bms_values[1] << 8));
    max_bms_temp = tmp;
    tmp = (bms_values[2] | (bms_values[3] << 8));
    min_bms_temp = tmp;
    tmp = (bms_values[4] | (bms_values[5] << 8));
    mean_bms_temp = tmp;
    max_temp_nslave = bms_values[6];
}


void read_ATC_TBS(Uint16 data[]) {
    atc_update(data, TBS);
}

void read_ATC_SUSPS(Uint16 data[]) {
    atc_update(data, SUSPS);
}

void read_ATC_TEMPS(Uint16 data[]) {
    atc_update(data, TEMPS);
}

void updateStart() {
    setStart = true;
}



/*
 * 2024
 */
void brakeLight()
{   
    // NON PIU' A LOGICA INVERTITA
    if (brake > BRAKE_LIGHT_MIN || paddle > BRAKE_LIGHT_MIN)
    {
        GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_ON); // ON
    }
    else
    {
        GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_OFF); // OFF
    }

}

void R2D_On()
{
    // playRTDS
    GPIO_WritePin(RTDS, 1U); // sound
    CpuTimer2.InterruptCount = 0;
    CpuTimer2Regs.TCR.bit.TSS = 0; // Start timer 2

    GPIO_WritePin(R2D, R2D_LED_ON); // led

}

void R2D_Off()
{
    GPIO_WritePin(RTDS, 0U);         // sound
    GPIO_WritePin(R2D, R2D_LED_OFF); // led

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
    if (R2D_first_state)
    {
        while (brake > R2D_BRAKE_TRESHOLD)
        {
            if (readRF() && isHVOn())
            {
                R2D_state = 1;
                R2D_first_state = 0;
                R2D_On();
                break;
            }
            else
            {
                R2D_state = 0;
                break;
            }
        }
    }

    /*
     * if we exit r2d and rf are turn off
     * we can repeat initialization
     */
    if (!R2D_state && !readRF())
    {
        R2D_first_state = 1;
    }
    else
    {
        R2D_first_state = 0;
    }

    /*
     * r2d will stay off until Hv is on and Rf are activated
     */
    if (!isHVOn() || !readRF())
    {
        R2D_state = 0;
        R2D_Off();
    }
}

/*
 * Battery pack tension is given indipendently by every motor.
 * The function seems complex because takes in consideration the case
 * that one or more motor are inactive.
 *
 * BMS precharge needs a message with the tot voltage
 */
void computeBatteryPackTension()
{
    int active_motors = 0;
    float sum = 0.0f;
    int max = 0;

    // find max voltage
    int i;
    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        if (motorVal1[i].AMK_Voltage > max)
        {
            max = motorVal1[i].AMK_Voltage;
        }
    }

    // Compute sum of voltages, exclude if it is below 50 V than the maximum reading
    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        if (motorVal1[i].AMK_Voltage > (max - 50))
        {
            active_motors++;
            sum += motorVal1[i].AMK_Voltage;
        }
    }

    if (active_motors == 0) {
        batteryPackTension = 0;
        total_power = 0.0f;
    }
    else {
        batteryPackTension = (Uint16)(sum / active_motors);
        total_power = batteryPackTension * lem_current;
    }
}

/*
 * Tramaccio: we wait 500ms before stating that an inverter has no Hv
 */
void checkHV() // HV COUNTER ON-->OFF
{
    int i;

    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        if ((motorVal1[i].AMK_bQuitDcOn == false) && (hvCounter[i] < HV_TRAP))
            hvCounter[i]++;

        else if ((motorVal1[i].AMK_bQuitDcOn == false) && (hvCounter[i] >= HV_TRAP))
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

/*
 * Tramaccio: we wait 500ms before stating that an Rf is not active
 */
void checkRF() // RF COUNTER ON-->OFF
{
    int i;

    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        if ((motorVal1[i].AMK_bQuitInverterOn == false) && (rfCounter[i] < RF_TRAP))
            rfCounter[i]++;

        else if ((motorVal1[i].AMK_bQuitInverterOn == false) && (rfCounter[i] >= RF_TRAP))
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
        if ((motorVal1[i].AMK_bQuitDcOn == 0) && hvDebugging)
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
    for (i = 0; i < NUM_OF_MOTORS; i++)
    {
        rf |= inverterRF[i];

#ifdef DEBUG_HV
        if ((motorVal1[i].AMK_bQuitInverterOn == 0) && rfDebugging)
            rfGoneWrong[i] = motorVal1[i].AMK_bQuitInverterOn;
#endif
    }

#ifdef DEBUG_NO_HV
    return true;
#endif
    return rf;
}


void pumpFanControl() {

    int steps[5] = {1000, 2000, 3000, 4000, 5000};
    int duty[5] = {20, 40, 60, 70, 100};

    static int steps_index = 0;
    static Uint32 RTD_timestamp = 0;

    pump_enable = 0;
    fan_enable = 0;

    if (R2D_state) {

        if (RTD_timestamp == 0) {
            RTD_timestamp = time_elapsed;
            return;
        }

        if(steps_index < sizeof(steps)/sizeof(steps[0]) - 2 && time_elapsed - RTD_timestamp >= steps[steps_index] MS && time_elapsed - RTD_timestamp < steps[steps_index + 1] MS) {

                pump_enable = 1;
                setPumpSpeed(duty[steps_index]);
                steps_index ++;

        }

        if(time_elapsed - RTD_timestamp > steps[sizeof(steps)/sizeof(steps[0]) - 1] MS) {

                 pump_enable = 1;
                 setPumpSpeed(duty[sizeof(steps)/sizeof(steps[0]) - 1]);

        }

        if(time_elapsed - RTD_timestamp > steps[sizeof(steps)/sizeof(steps[0]) - 1] MS + 1000 MS) {

                fan_enable = 1;
                setFanSpeed(100);

        }

        send_pwm_to_pcu();

    }


}





#define TIME_STEP 200   // 2s
#define CONTINOUS_CURR_LIMIT 65  // 65 A

void paddleControl(Uint32 time_elapsed) {

    bool is_breaking = paddle > 0;
    static Uint32 start_breaking = 0;

    if (is_breaking) {

        if(start_breaking == 0) {   // just start breaking
            start_breaking = time_elapsed;
        }
        
        car_settings.max_regen_current = car_settings.regen_current_scale * ((time_elapsed - start_breaking) > TIME_STEP ? CONTINOUS_CURR_LIMIT : PEAK_REGEN_CURRENT);

    } else {
        start_breaking = 0;    // no longer breaking
        car_settings.max_regen_current = car_settings.regen_current_scale * PEAK_REGEN_CURRENT;
    }
}




/*
 * Status represent an easy debug variable, visible on first display page
 */
void checkStatus()
{

    if (isHVOn())
        status |= 0x01;
    if (R2D_state)
        status |= 0x02;
    if (Air1_State)
        status |= 0x04;
    if(readRF())
        status |= 0x08;
    if (Air2_State)
        status |= 0x10;
    if (Air2_State && Air1_State)   // precharge
        status |= 0x20;

    TXCANA_CarStatus_Data[0] = status;
    status_log.status_shared = status;
    TXCANA_CarStatus_Data[1] = status_log.actualVelocityKMH_shared;  // velocity

}


void carSettingsMessage()
{

    TXCANA_CarSettings_Data[0] = (unsigned char)car_settings.max_regen_current;
    TXCANA_CarSettings_Data[1] = (unsigned char)(car_settings.power_limit / 1000);
    TXCANA_CarSettings_Data[2] = (unsigned char)(car_settings.max_speed / 1000) && 0xFF; // krpm
    TXCANA_CarSettings_Data[3] = (unsigned char)car_settings.max_pos_torque;
    TXCANA_CarSettings_Data[4] = (char)car_settings.max_neg_torque;
    TXCANA_CarSettings_Data[5] = (unsigned char)(car_settings.front_motor_repartition * 100);
    TXCANA_CarSettings_Data[6] = (unsigned char)(car_settings.rear_motor_repartition * 100);
    TXCANA_CarSettings_Data[7] = (unsigned char)(car_settings.torque_vectoring) & 1;

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

    for (i = 0; i < 8; i++)
    {
        bms_lv_shared[i] = bms_lv_cell[i];
    }

    // MotorValues
    for (i = 0; i < 4; i++)
    {
        motorVal1_shared[i].AMK_ActualVelocity = motorVal1[i].AMK_ActualVelocity;
        motorVal1_shared[i].AMK_Current = motorVal1[i].AMK_Current;
        motorVal1_shared[i].AMK_Voltage = motorVal1[i].AMK_Voltage;
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

    // MotorSetPoints

    for (i = 0; i < 4; i++)
    {
        motorSetP_shared[i].AMK_TargetVelocity = motorSetP[i].AMK_TargetVelocity;
        motorSetP_shared[i].AMK_TorqueLimitNegative = motorSetP[i].AMK_TorqueLimitNegative;
        motorSetP_shared[i].AMK_TorqueLimitPositive = motorSetP[i].AMK_TorqueLimitPositive;
        motorSetP_shared[i].AMK_bDcOn = motorSetP[i].AMK_bDcOn;
        motorSetP_shared[i].AMK_bEnable = motorSetP[i].AMK_bEnable;
        motorSetP_shared[i].AMK_bErrorReset = motorSetP[i].AMK_bErrorReset;
        motorSetP_shared[i].AMK_bInverterOn = motorSetP[i].AMK_bInverterOn;
    }

    // Status
    status_log.throttle_shared = throttle;
    status_log.actualVelocityKMH_shared = actualVelocityKMH;
    status_log.brake_shared = brake;
    status_log.status_shared = status;
    status_log.brakePress_shared1 = brakePress1;
    status_log.brakePress_shared2 = brakePress2;

    status_log.steering_shared = steering;

    // Bms
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

    // FanSpeed
    fanspeed_log.fanSpeed_shared = fanSpeed;

    // Imu
    for (i = 0; i < 3; i++)
    {
        imu_log.accelerations_shared[i] = accelerations[i];
        imu_log.omegas_shared[i] = omegas[i];
    }

    for (i = 0; i < 4; i++)
    {
        imu_log.suspensions_shared[i] = suspensions[i];
    }

    for (i = 0; i < 10; i++)
    {
        imu_log.temperatures_shared[i] = temperatures[i];
    }

    // Pedals update
    pedals_log.acc_shared = throttle;
    pedals_log.brk_shared = brake;
    pedals_log.throttle_req_shared = throttleReq;
    pedals_log.brk_req_shared = brakeReq;

    // Power setup update
    power_setup_log.max_speed_shared = car_settings.max_speed;
    // power_setup_log.rear_motor_scale_shared = rear_motor_scale;
    // power_setup_log.front_motor_scale_shared = front_motor_scale;
    power_setup_log.power_limit_shared = car_settings.power_limit;
}

void update_shared_mem()
{
    int index;
    for (index = 0; index < 4; index++)
    {
        sh.motorVal1[index] = motorVal1_shared[index];
        sh.motorVal2[index] = motorVal2_shared[index];
        sh.motorSetP[index] = motorSetP_shared[index];
    }

    int i;
    for (i = 0; i < 8; i++)
    {
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

// Returns Pa brake line pressure (read SP100 Aviorace datasheet)
int getSP100BrakePress(int adc_reading) {
    float g_adc = 3.3f / pow(2, 12);
    float v = adc_reading * g_adc * 2;
    float max_press = 100.0; // Bar
    float min_volt = 0.5; // V
    float max_volt = 4.5; // V
    float m = max_press / (max_volt - min_volt);
    
    if (v <= min_volt) {
        return 0;
    }
    
    if (v > min_volt && v < max_volt) {
        return 1e5 * m * (v - min_volt);
    }
        
    return 1e5 * max_press;
    
}

int getSP150BrakePress(int adc_reading) {
    float g_adc = 3.3f / pow(2, 12);
    float v = adc_reading * g_adc * 2;
    float max_press = 150.0; // Bar
    float min_volt = 0.5; // V
    float max_volt = 4.5; // V
    float m = max_press / (max_volt - min_volt);

    if (v <= min_volt) {
        return 0;
    }

    if (v > min_volt && v < max_volt) {
        return 1e5 * m * (v - min_volt);
    }

    return 1e5 * max_press;

}

void updateTVstruct() {

    rtU.ax = accelerations[0]; // m/s^2
    rtU.ay = accelerations[1]; // m/s^2

    rtU.yaw_r = omegas[2]; // rad/s

    rtU.throttle = throttle / 100.0; // 0 to 1
    rtU.brakepressurefront = brakePress1;
    rtU.brakepressurerear = brakePress2;
    rtU.regenpaddle = paddle / 100.0;
    rtU.steering = steering;

    rtU.rpm[0] = motorVal1[0].AMK_ActualVelocity; // rpm
    rtU.rpm[1] = motorVal1[1].AMK_ActualVelocity; // rpm
    rtU.rpm[2] = motorVal1[2].AMK_ActualVelocity; // rpm
    rtU.rpm[3] = motorVal1[3].AMK_ActualVelocity; // rpm

    rtU.voltage = batteryPackTension; // V

}







#include "car_management.h"

int calibration_status = 0;
int NUM_SMU_TEMP = 5;
// alberto patch
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



void read_map_sw_message(Uint16 val)
{

    Uint16 power_index = val & 0xF;
    Uint16 regen_index = (val >> 4) & 0xF;

    car_settings.power_limit = presets_power[power_index % 8];
    car_settings.max_regen_current = presets_regen[regen_index % 5];
}

void read_LEM_message(unsigned char lem_values[])
{
    reassembled_data = 0;
    Uint16 tmp = lem_values[0];
    tmp ^= 1 << 7;
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
        // alberto
        for (i = 0; i < 8; i += 2)
        {
            temperatures[i / 2] = (smu_values[i] | (smu_values[i + 1] << 8));
        }
        break;
    case (MSG_ID_SMU_TEMPERATURES + 1):
        for (i = 0; i < 4; i += 2)
        {
            temperatures[i / 2 + 4] = (smu_values[i] | (smu_values[i + 1] << 8));
        }
        break;
    case MSG_ID_SMU_SUSPENSIONS:
        for (i = 0; i < NUM_SMU_SUSP; i++)
        {
            suspensions[i] = (0x3FF & aux);
            aux >>= 10;
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

void read_ATC_SENSORS(Uint16 data[]) {
    atc_update(data, SENSORS);
}


/*
 * 2023 - logica invertita
 */
void brakeLight()
{
    if (brake > BRAKE_LIGHT_MIN || brakeReq > BRAKE_LIGHT_MIN)
    {
        GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_OFF); // ON
    }
    else
    {
        GPIO_WritePin(BRAKE_LIGHT_Abil, BRAKE_LIGHT_ON); // OFF
    }
}

void R2D_On()
{
    // playRTDS
    GPIO_WritePin(RTDS, 1U); // sound
    CpuTimer2.InterruptCount = 0;
    CpuTimer2Regs.TCR.bit.TSS = 0; // Start timer 2

    GPIO_WritePin(R2D, R2D_LED_ON); // led

    fan_enable = 1;
    pump_enable = 1;
}

void R2D_Off()
{
    GPIO_WritePin(RTDS, 0U);         // sound
    GPIO_WritePin(R2D, R2D_LED_OFF); // led

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
 */
void computeBatteryPackTension()
{
    int j = 0, active_motors = 0;
    Uint16 tensions[4];
    Uint16 active[4];
    Uint16 mean, mean_of_squared, max = 0;

    for (j = 0; j < 4; j++)
    {
        active[j] = 1;
        tensions[j] = motorVal1[j].AMK_Voltage;
        if (tensions[j] > max)
        {
            max = tensions[j];
        }
    }

    for (j = 0; j < 4; j++)
    {
        if (tensions[j] < max - 40)
        {
            active[j] = 0;
        }
    }

    for (j = 0; j < 4; j++)
    {
        if (active[j] > 0)
            active_motors++;
        mean += tensions[j] * active[j];
        mean_of_squared += tensions[j] * tensions[j] * active[j];
    }

    if (active_motors != 0)
    {
        mean /= active_motors;
        mean_of_squared /= active_motors;
    }
    else
    {
        mean = 0;
        mean_of_squared = 0;
    }

    batteryPackTension = mean;
    total_power = batteryPackTension * lem_current;
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

/*
 * Important: fans should be active after R2d
 */
void fanControl()
{
    if (fan_enable)
    {
        /*
         * fan activation threshold is based on max temp among all inverters
         */
        int leftTemp = fmax(motorVal2[0].AMK_TempInverter, motorVal2[2].AMK_TempInverter);
        int rightTemp = fmax(motorVal2[1].AMK_TempInverter, motorVal2[3].AMK_TempInverter);
        int maxTemp = fmax(leftTemp, rightTemp);

        fanSpeed = fanSpeedFunction(maxTemp);
        setFanSpeed(fanSpeed);
    }
    else
    {
        setFanSpeed(0);
    }

}

/*
 * Always active at 20% then linearly increases from 60% to 80% when temperature is above between 60  and 80
 */

Uint16 fanSpeedFunction(int temp)
{

    /*
     * Reminder: fans actually work with pwm greater or equal than 40%
     */
    if (temp <= 60)
    {
        return 40;
    }
    else if (temp >= 80)
    {
        return 80;
    }
    else
    {
        return (2 * temp) - 80;
    }
}

/*
 * Status represent an easy debug variable, visible on first display page
 */
void checkStatus()
{
    // STATUS
    // bit       | 7  |    6    |    5     |  4  |     3     |    2        |    1     | 0  |
    // meaning   | RF | imp_b_t | brk_disc | r2d | PRECHARGE | Fault check | LV_ALARM | HV |

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
    /* if (implBrakeAndThrottle)
         mstatus |= 0x0F000000;
     if (brk_disconnected)
         mstatus |= 0xF0000000; */

    status = mstatus;
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
    status_log.brakePress_shared = 0; // not implemented
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

    for (i = 0; i < 8; i++)
    {
        imu_log.temperatures_shared[i] = temperatures[i];
    }

    // Pedals update
    pedals_log.acc_shared = atc_acceleration_pedal();
    pedals_log.brk_shared = atc_brake_pedal();
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

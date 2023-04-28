#include "utils.h"

extern float corrected_accelerations[3];

void setup_car_settings(){

    memcpy(car_settings.presets_power, presets_power, sizeof(presets_power));
    memcpy(car_settings.presets_max_pos, presets_max_pos, sizeof(presets_max_pos));
    memcpy(car_settings.presets_max_neg, presets_max_neg, sizeof(presets_max_neg));
    memcpy(car_settings.presets_regen, presets_regen, sizeof(presets_regen));
    memcpy(car_settings.presets_speed, presets_speed, sizeof(presets_speed));
    memcpy(car_settings.presets_coppie_front, presets_coppie_front, sizeof(presets_coppie_front));
    memcpy(car_settings.presets_coppie_rear, presets_coppie_rear, sizeof(presets_coppie_rear));

    car_settings.max_regen_current=MAX_REGEN_CURRENT;
    car_settings.max_speed = SPEED_LIMIT;
    car_settings.rear_motor_scale = REAR_MOTOR_SCALE;
    car_settings.front_motor_scale = FRONT_MOTOR_SCALE;
    car_settings.max_pos_torque = MAX_POS_TORQUE;
    car_settings.max_neg_torque = MAX_NEG_TORQUE;
    car_settings.power_limit = POWER_LIMIT;
}

float convertBMSvoltage(Uint16 voltage){
  return (3000 + (1.2 * voltage));
}

float convertBMStemp(Uint16 temp){
  return 27*(-1) + 0.2*temp;
}

float changeRange(float val, float currentMin, float currentMax, float newMin, float newMax) {
    float ratioX = (val - currentMin) / (currentMax - currentMin);  // 0 .. 1
    float newRange = ratioX * (newMax - newMin);  // new range between new min and new max
    return newMin + newRange;  // new min .. new max
}

Uint16 saturateUnsigned(Uint16 signal, Uint16 upperBound, Uint16 lowerBound)
{
    if (lowerBound >= upperBound)
        return 0;

    if (signal > upperBound)
        return upperBound;
    else if (signal < lowerBound)
        return lowerBound;
    else
        return signal;
}

float saturateFloat(float signal, float upperBound, float lowerBound)
{
    if (lowerBound >= upperBound)
        return 0;

    if (signal > upperBound)
        return upperBound;
    else if (signal < lowerBound)
        return lowerBound;
    else
        return signal;
}

float saturateInt(int signal, int upperBound, int lowerBound)
{
    if (lowerBound >= upperBound)
        return 0;

    if (signal > upperBound)
        return upperBound;
    else if (signal < lowerBound)
        return lowerBound;
    else
        return signal;
}

//turn on/off LED1 (blue led) every period*10 ms
void debugLight(int period)
{
//    if (cpuTimer0IntCount % period == 0)
//        GPIO_togglePin(RED_BLINK);
}

float uint32_to_float(Uint32 u)
{
    union
    {
        Uint32 u;
        float f;
    } temp;
    temp.u=u;

    return temp.f;
}
int16_t unsigned_to_signed(Uint16 value){
    union{
        Uint16 u;
        int16_t s;
    }temp;
    temp.u = value;
    return temp.s;
}

float convert_temp_lv(float cell_volt)
{
  float x = ((log((5 - cell_volt)/cell_volt))/3435);
  x = 1/((1/298.15) - x);
  return x - 273.15;
}

float ConvertTempToKelvin(int adc_read)
{
  float div = (float)((float)adc_read / 1023);
  return (3977 * 298.15) / (3977 - (298.25 * log((1 - div) / div)));
}

float torqueSetpointToNM(int setpoint)
{
    return (setpoint/1000.0)*M_N;
}

int NMtoTorqueSetpoint(float torqueNM)
{
    return (torqueNM/M_N)*1000;
}

void imu_calibration_1(float accelerations[3]){
    float norma = sqrt(pow(accelerations[0],2) + pow(accelerations[1],2)+pow(accelerations[2],2));
    int i;
        for (i = 0; i<3; i++){
            versz[i]=accelerations[i]/norma;
        }
}

void imu_calibration_2(float accelerations[3]){
    int i, j;
    float gi_z;
    for(i=0; i<3;i++){
        gi_z = gi_z + accelerations[i]*versz[i];
    }
    float gi_x[3];
    for(i=0; i<3; i++){
        gi_x[i] = accelerations[i] - gi_z * versz[i];
    }
    float norma = sqrt(pow(gi_x[0],2) + pow(gi_x[1],2)+pow(gi_x[2],2));
    for(i=0; i<3; i++){
            versx[i] = gi_x[i]/norma;
        }
    //prodotto vettoriale hard coded
    versy[0]=versz[1]*versx[2] - versz[2]*versx[1];
    versy[1]=versz[2]*versx[0] - versz[0]*versx[2];
    versy[2]=versz[0]*versx[1] - versz[1]*versx[0];

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
                if(i == 0){
                    V[i][j] = versx[j];
                }else if(i == 1){
                    V[i][j] = versy[j];
                }else if(i == 2){
                    V[i][j] = versz[j];
                }
        }
    }
}
void send_calibration(float V[3][3]){
    //Loads floats of the correction matrix in the packets arrays
    //with the following logic:
    //Value with a pair sum of indices must be placed in position 0 of the i-esim array
    //Value with a odd sum must be in position 1
    //Every time a pair of value is loaded the the number of row 'c' is increased by +1
    int i, j,c;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if((i+j)%2 == 0){
                TXA_Smu_Calibration[c][0] = V[i][j];
            }else{
                TXA_Smu_Calibration[c][1] = V[i][j];
                c++;
            }
        }
    }

    for(c = 0; c < 5; c++){
        CANMessageSet(CANA_BASE, TX_OBJ_ID, &TXCANA_Smu_Message[c], MSG_OBJ_TYPE_TX);
    }
}

void apply_calibration(){
    accelerations[X] = accelerations[X] * V[0][0] + accelerations[Y] * V[0][1] + accelerations[Z] * V[0][2];
    accelerations[Y] = accelerations[X] * V[1][0] + accelerations[Y] * V[1][1] + accelerations[Z] * V[1][2];
    accelerations[Z] = accelerations[X] * V[2][0] + accelerations[Y] * V[2][1] + accelerations[Z] * V[2][2];
}

void float2Bytes(unsigned char* bytes_temp, float float_variable)
{
    memcpy(bytes_temp, &float_variable, sizeof(float_variable));
}

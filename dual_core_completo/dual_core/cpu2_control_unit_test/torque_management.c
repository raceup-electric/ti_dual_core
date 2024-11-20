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

//torque_reg_IPM in uscita � POSITIVO
void regBrake()
{
    if(REGEN_ALG){
        negTorquesNM[0] = rigen_fun_simulink22_Y.TorqueFL;
        negTorquesNM[1] = rigen_fun_simulink22_Y.TorqueFR;
        negTorquesNM[2] = rigen_fun_simulink22_Y.TorqueRL;
        negTorquesNM[3] = rigen_fun_simulink22_Y.TorqueRR;

        return;
    }
    // Calculate OCV of battery accounting for RBATT and current
    float v_zero = batteryPackTension + RBATT * lem_current;
    // Calculate actual current limit in battery to reduce current when battery is charged
    float current_limit = fminf((BATTERY_FULL_VOLTAGE - v_zero) / (RBATT + 0.1f), car_settings.max_regen_current);
    // Calculate maximum regen power upstream of the inverter from motors given current_limit computed before and accounting for inverter efficiency
    float pe_max = (v_zero + RBATT * current_limit) * current_limit / ETA_INV;

    float p_mot = 0;
    float p_loss = 0;
    float p_wheel = 0;
    float rads = 0;
    float rade = 0;
    float a = 0;
    float b = 0;
    float c = 0;
    float iq = 0, id = 0;

    int mot;
    for (mot = 0; mot < NUM_OF_MOTORS; mot++)
    {
        // compute per-motor power accounting for torque repartition ( / 2 because there are 2 motors per axle)
        if (mot == MOTOR_FL || mot == MOTOR_FR)
        {
            p_mot = pe_max * FRONT_MOTOR_BRAKE_REP / 2;
        }
        else
        {
            p_mot = pe_max * REAR_MOTOR_BRAKE_REP / 2;
        }
        rads = motorVal1[mot].AMK_ActualVelocity * PI / 30;
        rade = rads * POLES;

        a = 3 / 2 * (R * (1 + 1 / pow(TALPHA, 2)) + rade * (LD - LQ) / TALPHA);
        b = 3 / 2 * rade * FLUX_MG;
        c = -p_mot;
        iq = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
        id = iq / TALPHA;

        p_loss = 3 / 2 * R * (pow(id, 2) + pow(iq, 2));
        p_wheel = (p_mot + p_loss) / ETA_MECH;

        float analytic_max_torque = rads == 0 ? 0 : p_wheel / rads;

        // check AMK motors datasheet pg.1 rmp torque curve
        float torque_limit = saturateFloat(MAX_MOTOR_TORQUE - 0.000857 * (fabsf(motorVal1[mot].AMK_ActualVelocity) - 13000.0f), -car_settings.max_neg_torque, 0.0f);
        negTorquesNM[mot] = -((brakeReq / 100.0) * fminf(torque_limit, analytic_max_torque));
    }
}

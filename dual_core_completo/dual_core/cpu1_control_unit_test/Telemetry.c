/*
 * Telemetry.c
 *
 *  Created on: 12 mar 2022
 *      Author: Davide Frasson
 */

#include "Telemetry.h"
#include "stdio.h"
#include "string.h"
#include "display.h"



//-------------------------
//Test Data
//------------------------

extern struct Share_struct local_sh;
float posTorquesNM[4];
float negTorquesNM[4];

//--------------------

char toSendData[255];
char tempData[255];

int send_Motors(){
    memset(toSendData, 0, 255 * sizeof *toSendData);
    toSendData[0] = '1';
    toSendData[1] = ';';
    int counter = 2;
    int i;
    for(i = 0; i < 4; i++){
        counter += usprintf(tempData, "%f;%.1f;%.1f;%.1f;%.1f;%04d;",
                local_sh.motorVal1[i].AMK_ActualVelocity,
                posTorquesNM[i], negTorquesNM[i],
                local_sh.motorVal2[i].AMK_TempMotor,
                local_sh.motorVal2[i].AMK_TempIGBT,
                local_sh.motorVal2[i].AMK_ErrorInfo);
        strcat(toSendData, tempData);
    }
    toSendData[counter++] = '\n';
    beginPacket(0);
    LoRa_writeBuffer(toSendData, counter);
    endPacket(true);

    return 1;
}


int send_Status_Imu_BMS_Sendyne(){
    memset(toSendData, 0, 255 * sizeof *toSendData);
    toSendData[0] = '2';
    toSendData[1] = ';';
    int counter = usprintf(tempData, "%d;%d;%d;%d;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.1f;%.1f;%.1f;%.1f\n",
            local_sh.status.steering_shared,
            local_sh.status.actualVelocityKMH_shared,
            local_sh.status.throttle_shared,
            local_sh.status.brake_shared,
            local_sh.imu.accelerations_shared[0],
            local_sh.imu.accelerations_shared[1],
            local_sh.imu.accelerations_shared[2],
            local_sh.imu.omegas_shared[0],
            local_sh.imu.omegas_shared[1],
            local_sh.imu.omegas_shared[2],
            local_sh.power.batteryPack_voltage_shared,
            local_sh.power.lem_current_shared,
            local_sh.bms.max_bms_temp_shared,
            local_sh.bms.min_bms_temp_shared,
            local_sh.bms.max_bms_voltage_shared,
            local_sh.bms.min_bms_voltage_shared);
    strcat(toSendData, tempData);
    counter += 2; //Aggiungo i due caratteri iniziali

    beginPacket(0);
    LoRa_writeBuffer(toSendData, counter);
    endPacket(true);

    return 1;
}

void debugSet(){
     local_sh.status.steering_shared = 270;
     local_sh.status.actualVelocityKMH_shared = 120;
     local_sh.status.throttle_shared = 78;
     local_sh.status.brake_shared = 22;

     local_sh.imu.accelerations_shared[0] = 56.27;
     local_sh.imu.accelerations_shared[1] = 24.32;
     local_sh.imu.accelerations_shared[2] = 25.67;
     local_sh.imu.omegas_shared[0] = 56.278;
     local_sh.imu.omegas_shared[1] = 23.456;
     local_sh.imu.omegas_shared[2] = 67.987;

     local_sh.power.batteryPack_voltage_shared = 458.67;
     local_sh.power.lem_current_shared = 20.89;
     local_sh.bms.max_bms_temp_shared = 71.2;
     local_sh.bms.min_bms_temp_shared  =52.4;
     local_sh.bms.max_bms_voltage_shared = 3.76;
     local_sh.bms.min_bms_voltage_shared  =3.24f;

     //Add motor debug set
     int i;
     for(i = 0; i < 4; i++){
         local_sh.motorVal1[i].AMK_ActualVelocity = 2600;
         posTorquesNM[i] = 21.8f;
         negTorquesNM[i] = -15.6f;
         local_sh.motorVal2[i].AMK_TempMotor = 15.768f,
         local_sh.motorVal2[i].AMK_TempIGBT = 24.653f;
         local_sh.motorVal2[i].AMK_ErrorInfo = 0;
     }
}


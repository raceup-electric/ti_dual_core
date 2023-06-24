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
        counter += sprintf(tempData, "%f;%.1f;%.1f;%.1f;%.1f;%04d;",
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
    int counter = sprintf(tempData, "%d;%d;%d;%d;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.1f;%.1f;%.1f;%.1f\n",
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

int send_Single_Data(int counter){
    float sum = 0.0f;
    int j = 0;
    uint8_t toSendBuffer[LORA_IMPLICIT_SIZE];
    toSendBuffer[0] = counter;
    uint32_t toSendBytes = 0;
    switch(counter){
        //CASE TO SEND THE MOTORS TEMPERATURES
        case 1:
            toSendBytes = float_to_uint32(local_sh.motorVal2[0].AMK_TempMotor);
        break;
        case 2:
            toSendBytes = float_to_uint32(local_sh.motorVal2[0].AMK_TempIGBT);
        break;
        case 3:
            toSendBytes = float_to_uint32(local_sh.motorVal2[0].AMK_TempInverter);
        break;
        case 4:
           toSendBytes = float_to_uint32(local_sh.motorVal2[1].AMK_TempMotor);
        break;
        case 5:
           toSendBytes = float_to_uint32(local_sh.motorVal2[1].AMK_TempIGBT);
        break;
        case 6:
           toSendBytes = float_to_uint32(local_sh.motorVal2[1].AMK_TempInverter);
        break;
        case 7:
            toSendBytes = float_to_uint32(local_sh.motorVal2[2].AMK_TempMotor);
        break;
        case 8:
            toSendBytes = float_to_uint32(local_sh.motorVal2[2].AMK_TempIGBT);
        break;
        case 9:
            toSendBytes = float_to_uint32(local_sh.motorVal2[2].AMK_TempInverter);
        break;
        case 10:
           toSendBytes = float_to_uint32(local_sh.motorVal2[3].AMK_TempMotor);
        break;
        case 11:
           toSendBytes = float_to_uint32(local_sh.motorVal2[3].AMK_TempIGBT);
        break;
        case 12:
           toSendBytes = float_to_uint32(local_sh.motorVal2[3].AMK_TempInverter);
        break;
        //Send status of the motors
        case 13:
           toSendBytes = ((uint32_t)AmkStatus[0] << 24 ) | ((uint32_t)AmkStatus[1] << 16 ) | ((uint32_t)AmkStatus[2] << 8 ) | ((uint32_t)AmkStatus[3] << 0 );
        break;

        case 14:
            toSendBytes = local_sh.status.status_shared;
        break;
        case 15:
            toSendBytes = float_to_uint32(local_sh.bms.max_bms_voltage_shared);
        break;
        case 16:
            toSendBytes = float_to_uint32(local_sh.bms.min_bms_voltage_shared);
        break;
        case 17:
            toSendBytes = float_to_uint32(local_sh.bms.mean_bms_voltage_shared);
        break;
        case 18:
           toSendBytes = float_to_uint32(local_sh.bms.max_bms_temp_shared);
       break;
       case 19:
           toSendBytes = float_to_uint32(local_sh.bms.min_bms_temp_shared);
       break;
       case 20:
           toSendBytes = float_to_uint32(local_sh.bms.mean_bms_temp_shared);
       break;
       case 21:
           toSendBytes = float_to_uint32(getLowestLvVoltage());
       break;
       case 22:

           for(; j < 6; j++){
               sum += local_sh.bms_lv[j];
           }
           toSendBytes = float_to_uint32(sum);
       break;
       case 23:
           toSendBytes = float_to_uint32((local_sh.bms_lv[6] + local_sh.bms_lv[7])/2);
       break;

       case 24:
           toSendBytes = float_to_uint32(local_sh.imu.temperatures_shared[0] - 273.15);
       break;
       case 25:
          toSendBytes = float_to_uint32(local_sh.imu.temperatures_shared[1] - 273.15);
      break;
       case 26:
          toSendBytes = float_to_uint32(local_sh.imu.temperatures_shared[2] - 273.15);
      break;
       case 27:
          toSendBytes = float_to_uint32(local_sh.imu.temperatures_shared[3] - 273.15);
      break;
       case 28:
          toSendBytes = float_to_uint32(local_sh.imu.temperatures_shared[4] - 273.15);
      break;
      case 29:
          toSendBytes = float_to_uint32(local_sh.imu.temperatures_shared[5] - 273.15);
      break;
      case 30:
           toSendBytes = float_to_uint32(local_sh.imu.temperatures_shared[6] - 273.15);
      break;
       case 31:
          toSendBytes = float_to_uint32(local_sh.imu.temperatures_shared[7] - 273.15);
          counter = 0;
          break;

    }

    counter++;



    int i;
    for(i = 1; i < LORA_IMPLICIT_SIZE;i++){
        toSendBuffer[i] = (0x00FF & (toSendBytes >> ((i-1)*8)));
    }

    beginPacket(LORA_IMPLICIT_HEADER);
    LoRa_writeBuffer(toSendBuffer,LORA_IMPLICIT_SIZE);
    endPacket(true);
    return counter;
}

uint32_t float_to_uint32(float value){
    union{
        uint32_t u;
        float f;
    }temp;
    temp.f = value;
    return temp.u;
}

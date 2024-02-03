/*
 * Telemetry.h
 *
 *  Created on: 12 mar 2022
 *      Author: Davide Frasson
 */

#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#include "LoRa.h"

extern char AmkStatus[4];
//-------------------------------------------------------------
//
// Functions to send and formats packets
//
//-------------------------------------------------------------

int send_Motors();
int send_Status_Imu_BMS_Sendyne();

int send_Single_Data(int counter);
void debugSet();
float getLowestLvVoltage();

uint32_t float_to_uint32(float value);

#endif /* TELEMETRY_H_ */

/*
 * Telemetry.h
 *
 *  Created on: 12 mar 2022
 *      Author: Davide Frasson
 */

#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#include "LoRa.h"


//-------------------------------------------------------------
//
//Functions to send and formats packets
//
//-------------------------------------------------------------

int send_Motors();
int send_Status_Imu_BMS_Sendyne();

void debugSet();



#endif /* TELEMETRY_H_ */

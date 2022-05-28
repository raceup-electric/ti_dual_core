#ifndef CAN_MANAGEMENT_H_
#define CAN_MANAGEMENT_H_

//
// includes
//

#include "F28x_Project.h"
#include "global_definitions.h"
#include "timer_management.h"
#include "motor_management.h"
#include "adc_management.h"
#include "car_management.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"

//
//  GPIO5 -  CANRXA - PIN35
//  GPIO4 - CANTXA - PIN36
//
//  GPIO17 -  CANRXB - Modulo can j12
//  GPIO12 - CANTXB - Modulo can j12
//


//
// variables
//
extern volatile Uint32 errorFlag;
extern volatile Uint32 rxAMsgCount;
extern volatile Uint32 rxBMsgCount;

extern int errorFrameCounterB;
extern int errorFrameCounterA;

extern Uint16 RX_A_temp[8];
extern bool temp_warning;

extern int driving_configuration;
extern bool powerOK;
extern Uint16 powersetup[8];


extern tCANMsgObject RXCANA_Imu_Message;
extern tCANMsgObject RXCANA_Smu_Message;
extern tCANMsgObject RXCANA_Sendyne_Message;
extern tCANMsgObject RXCANA_BmsVol_Message;
extern tCANMsgObject RXCANA_BmsTemp_Message;
extern tCANMsgObject RXCANA_BmsLV_Message;
extern tCANMsgObject RXCANA_PwCtrl_Message;
extern tCANMsgObject RXCANA_Wheel_Message;
extern unsigned char RXA_Imu_Data[8];
extern unsigned char RXA_Smu_Data[8];
extern unsigned char RXA_Sendyne_Data[8];
extern unsigned char RXA_BmsVol_Data[6];
extern unsigned char RXA_BmsTemp_Data[6];
extern unsigned char RXA_PwCtrl_Data[1];
extern unsigned char RXA_Wheel_Data[1];

extern tCANMsgObject TXCANB_Setpoints_Message[4];
extern unsigned char TXB_Setpoints_Data[4][8];

extern tCANMsgObject RXCANB_AmkVal1_Message[4];
extern tCANMsgObject RXCANB_AmkVal2_Message[4];
extern unsigned char RXB_AmkVal_Data[8];



//
// prototypes
//
void canSetup_phase1();
void canSetup_phase2();

__interrupt void canISR_B(void);

__interrupt void canISR_A(void);

Uint32 getMessageID(Uint32 base, Uint32 objID);

#endif

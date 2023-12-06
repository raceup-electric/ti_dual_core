#include "can_management.h"
#include "global_definitions.h"
#include "main.h"

unsigned long gg;


//alberto patch
void setting_package_param(tCANMsgObject *Object, unsigned int ID,
                            unsigned int mask, unsigned int other_settings,
                            unsigned int data_len, void * XA_DATA)
{
    Object->ui32MsgID = ID;
    Object->ui32MsgIDMask = mask;
    Object->ui32Flags = other_settings;
    Object->ui32MsgLen = data_len;
    Object->pucMsgData = XA_DATA;

}

void canSetup_phase1()
{

    EALLOW;
    CpuSysRegs.PCLKCR10.bit.CAN_A = 1;
    CpuSysRegs.PCLKCR10.bit.CAN_B = 1;
    EDIS;

//    CANInit(CANA_BASE);
//    CANInit(CANB_BASE);


    CANClkSourceSelect(CANA_BASE, 0);
    CANClkSourceSelect(CANB_BASE, 0);

//    CANBitRateSet(CANA_BASE, 200000000, 1000000);   //Manca un parametro rispetto al vecchio metodo
    //Prova con CAN linea A a 500kbps
    CANBitRateSet(CANA_BASE, 200000000, 500000);
    CANBitRateSet(CANB_BASE, 200000000, 1000000);

    CANIntEnable(CANA_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    CANIntEnable(CANB_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
}

void canSetup_phase2()
{
    EALLOW;
    PieVectTable.CANA0_INT = canISR_A;
    PieVectTable.CANB0_INT = canISR_B;
    EDIS;

    PieCtrlRegs.PIEIER9.bit.INTx5 = 1;  //Can A
    PieCtrlRegs.PIEIER9.bit.INTx7 = 1;  //Can B
    IER |= M_INT9;

    CANGlobalIntEnable(CANA_BASE, CAN_GLB_INT_CANINT0);
    CANGlobalIntEnable(CANB_BASE, CAN_GLB_INT_CANINT0);

    int i;

    for (i = 0; i<4; i++)
    {
        setting_package_param(&RXCANB_AmkVal1_Message[i],AMK_VAL_1_IDS[i],0x1FFFFFF0,
                MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER,MSG_DATA_LENGTH,RXB_AmkVal_Data);
        CANMessageSet(CANB_BASE, OBJ_ID_FROM_AMK, &RXCANB_AmkVal1_Message[i], MSG_OBJ_TYPE_RX);


        setting_package_param(&RXCANB_AmkVal2_Message[i],AMK_VAL_2_IDS[i],0x1FFFFFF0,
                MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER,MSG_DATA_LENGTH,RXB_AmkVal_Data);
        CANMessageSet(CANB_BASE, OBJ_ID_FROM_AMK, &RXCANB_AmkVal2_Message[i], MSG_OBJ_TYPE_RX);


        // TXCANB_Setpoints_Message[i].ui32MsgID = AMK_SETPOINTS_IDS[i];                      // CAN message ID - use 1
        // TXCANB_Setpoints_Message[i].ui32MsgIDMask = 0;                  // no mask needed for TX
        // TXCANB_Setpoints_Message[i].ui32Flags = MSG_OBJ_NO_FLAGS;  // enable interrupt on TX
        // TXCANB_Setpoints_Message[i].ui32MsgLen = sizeof(CAN_AMK_SET_POINT[i]);   // size of message is 8
        // TXCANB_Setpoints_Message[i].pucMsgData = TXB_Setpoints_Data[i];           // ptr to message content
        setting_package_param(&TXCANB_Setpoints_Message[i],AMK_SETPOINTS_IDS[i],0, MSG_OBJ_NO_FLAGS,sizeof(CAN_AMK_SET_POINT[i],TXB_Setpoints_Data[i]);

        }

        //Pacchetto accelerazioni IMU
        setting_package_param(&RXCANA_Imu_Message,MSG_ID_IMU_BASE,0x1FFFFFFC,
                MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER,MSG_DATA_LENGTH,RXA_Imu_Data);
        CANMessageSet(CANA_BASE, OBJ_ID_FROM_IMU, &RXCANA_Imu_Message, MSG_OBJ_TYPE_RX);

        //Pacchetto generico SMU
        setting_package_param(&RXCANA_Smu_Message,MSG_ID_SMU_BASE,0x1FFFFFFC,
                MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER,MSG_DATA_LENGTH,RXA_Smu_Data);

        CANMessageSet(CANA_BASE, OBJ_ID_FROM_SMU, &RXCANA_Smu_Message, MSG_OBJ_TYPE_RX);

        /*RXCANA_Smu_Message.ui32MsgID = MSG_ID_SMU_BASE;
        RXCANA_Smu_Message.ui32MsgIDMask = 0x0;
        RXCANA_Smu_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
        RXCANA_Smu_Message.ui32MsgLen = MSG_DATA_LENGTH;
        RXCANA_Smu_Message.pucMsgData = RXA_Smu_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_FROM_SMU, &RXCANA_Smu_Message, MSG_OBJ_TYPE_RX);*/

        for(i = 0; i < 5; i++){
            setting_package_param(&TXCANA_Smu_Message[i],MSG_ID_CALIBRATION_TO_SMU,0x0,
                    MSG_OBJ_NO_FLAGS,MSG_DATA_LENGTH,(unsigned char*)TXA_Smu_Calibration[i]);
        }

        //Pacchetto BMS VOLTAGE
        setting_package_param(&RXCANA_BmsVol_Message,MSG_ID_BMS_VOLTAGE,0x0,
                MSG_OBJ_RX_INT_ENABLE,8,RXA_BmsVol_Data);
        CANMessageSet(CANA_BASE, OBJ_ID_BMS_VOLTAGE, &RXCANA_BmsVol_Message, MSG_OBJ_TYPE_RX);

        //PACCHETTO BMS TEMPERATURE
        setting_package_param(&RXCANA_BmsTemp_Message,MSG_ID_BMS_TEMP,0x0,
                MSG_OBJ_RX_INT_ENABLE,7,RXA_BmsTemp_Data);
        CANMessageSet(CANA_BASE, OBJ_ID_BMS_TEMP, &RXCANA_BmsTemp_Message, MSG_OBJ_TYPE_RX);

        setting_package_param(&TXCANA_BmsHost_Message,MSG_ID_HOST_SEND,0,
                MSG_OBJ_NO_FLAGS,4,TXA_Host_Data);

        //PACCHETTO BMS LV
        setting_package_param(&RXCANA_BmsLV_Message,MSG_ID_BMS_BASE,0x1FFFFFFC,
                MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER,8,RXA_BmsLV_Data);
        CANMessageSet(CANA_BASE, OBJ_ID_FROM_BMS_LV, &RXCANA_BmsLV_Message, MSG_OBJ_TYPE_RX);

        //PACCHETTO POWER CONTROL DAL VOLANTE
        setting_package_param(&RXCANA_PwCtrl_Message,MSG_ID_POWER_CONTROL,0x0,
                MSG_OBJ_RX_INT_ENABLE,1,RXA_PwCtrl_Data);
        CANMessageSet(CANA_BASE, OBJ_ID_POWER_CONTROL, &RXCANA_PwCtrl_Message, MSG_OBJ_TYPE_RX);

        //PACCHETTO DA VOLANTE SCHERMO
        setting_package_param(&RXCANA_Wheel_Message,MSG_ID_STEERING_WHEEL_BASE,0x1FFFFFFC,
                MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER,1,RXA_Wheel_Data);
        CANMessageSet(CANA_BASE, OBJ_ID_STEERING_WHEEL, &RXCANA_Wheel_Message, MSG_OBJ_TYPE_RX);

        //PACCHETTO DA LEM
        setting_package_param(&RXCANA_Lem_Message,MSG_ID_LEM,0x0,MSG_OBJ_RX_INT_ENABLE,
                MSG_DATA_LENGTH,RXA_Lem_Data);
        CANMessageSet(CANA_BASE, OBJ_ID_FROM_LEM, &RXCANA_Lem_Message, MSG_OBJ_TYPE_RX);

        //Alberto Patch

        //PACCHETTO DA ATC

        // MSG_OBJ_RX_INT_ENABLE; //to change ??
        // MSG_DATA_LENGTH; //to change
        // RXA_Lem_Data;   //to change

        setting_package_param(&TXCANA_ATC_Message,MSG_ID_ATC,0x0,MSG_OBJ_RX_INT_ENABLE,
                MSG_DATA_LENGTH,RXA_ATC_DATA);
        CANMessageSet(CANA_BASE, OBJ_ID_FROM_ATC, &TXCANA_ATC_Message, MSG_OBJ_TYPE_RX);

        //end Alberto Patch


        TXCANA_Throttle_Message.ui32MsgID = MSG_ID_TO_ATMEGA;
        TXCANA_Throttle_Message.ui32MsgIDMask = 0;
        TXCANA_Throttle_Message.ui32Flags = MSG_OBJ_NO_FLAGS;
        TXCANA_Throttle_Message.ui32MsgLen = 2;
        TXCANA_Throttle_Message.pucMsgData = TXCANA_ATMega_Data;



        CANEnable(CANA_BASE);
        CANEnable(CANB_BASE);
}

__interrupt void canISR_B(void)
{
    uint32_t status;

    status = CANIntStatus(CANB_BASE, CAN_INT_STS_CAUSE);


    switch (status) {
        case CAN_INT_INT0ID_STATUS:
            status = CANStatusGet(CANB_BASE, CAN_STS_CONTROL);

            if(((status  & ~(CAN_ES_TXOK | CAN_ES_RXOK)) != 7) &&
                    ((status  & ~(CAN_ES_TXOK | CAN_ES_RXOK)) != 0))
            {
                errorFlag = 1;
                errorFrameCounterB++;
            }


            CANIntClear(CANB_BASE, CAN_INT_INT0ID_STATUS);
            break;
        //
        // Check if the cause is the receive message object 2
        //
        case OBJ_ID_FROM_AMK:
            //Uint16 amk_temp[8];

            CANMessageGet(CANB_BASE, OBJ_ID_FROM_AMK, &RXCANB_AmkVal1_Message[0], true); //FORSE TRUE NON � GIUSTO


            int id = getMessageID(CANB_BASE,OBJ_ID_FROM_AMK);

            if (getAMKValNumber(id) == 1)
            {
                rxBMsgCount++;
                read_AMK_Values1((Uint16*)RXB_AmkVal_Data, getMotorIndex(id));
            }
            else if (getAMKValNumber(id) == 2)
            {
                rxBMsgCount++;
                read_AMK_Values2((Uint16*)RXB_AmkVal_Data, getMotorIndex(id));
            }

            CANIntClear(CANB_BASE, OBJ_ID_FROM_AMK);

            errorFlag = 0;
            break;
        default:
    }

    CANGlobalIntClear(CANB_BASE, CAN_GLB_INT_CANINT0);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

__interrupt void canISR_A(void)
{
    uint32_t status;

    status = CANIntStatus(CANA_BASE, CAN_INT_STS_CAUSE);
    gg =status; // for debug
    
    //alberto patch
    switch (status) {

        case CAN_INT_INT0ID_STATUS:
            status = CANStatusGet(CANA_BASE, CAN_STS_CONTROL);



            if(((status  & ~(CAN_ES_TXOK | CAN_ES_RXOK)) != 7) &&
                    ((status  & ~(CAN_ES_TXOK | CAN_ES_RXOK)) != 0))
            {

                errorFlag = 1;
                errorFrameCounterA++;
            }

            CANIntClear(CANA_BASE, CAN_INT_INT0ID_STATUS);
            break;
        case OBJ_ID_FROM_IMU:
            //Uint16 imu_msg_temp[8];
            CANMessageGet(CANA_BASE, OBJ_ID_FROM_IMU, &RXCANA_Imu_Message, true);

            int id = getMessageID(CANA_BASE, OBJ_ID_FROM_IMU);

            read_IMU_message((Uint16 *)RXA_Imu_Data, id);

            rxAMsgCount++;

            CANIntClear(CANA_BASE, OBJ_ID_FROM_IMU);
            break;
        case OBJ_ID_FROM_SMU:
            //Ricevuto pacchetto da mailbox dello SMU
            CANMessageGet(CANA_BASE, OBJ_ID_FROM_SMU, &RXCANA_Smu_Message, true);

            int id = getMessageID(CANA_BASE, OBJ_ID_FROM_SMU);

            read_SMU_Message((Uint16 *)RXA_Smu_Data, id);

            rxAMsgCount++;

            CANIntClear(CANA_BASE, OBJ_ID_FROM_SMU);
            break;
        case OBJ_ID_BMS_VOLTAGE:
            //Uint16 bms_msg_temp[6];

            CANMessageGet(CANA_BASE, OBJ_ID_BMS_VOLTAGE, &RXCANA_BmsVol_Message, true);

            int id = getMessageID(CANA_BASE, OBJ_ID_BMS_VOLTAGE);

            read_BMS_VOLTAGE_message((Uint16 *)RXA_BmsVol_Data);

            rxAMsgCount++;

            CANIntClear(CANA_BASE, OBJ_ID_BMS_VOLTAGE);
            break;
        case OBJ_ID_BMS_TEMP:
            //Uint16 bms_msg_temp[6];

            CANMessageGet(CANA_BASE, OBJ_ID_BMS_TEMP, &RXCANA_BmsTemp_Message, true);

            int id = getMessageID(CANA_BASE, OBJ_ID_BMS_TEMP);


            read_BMS_TEMP_message((Uint16 *)RXA_BmsTemp_Data);

            rxAMsgCount++;

            CANIntClear(CANA_BASE, OBJ_ID_BMS_TEMP);
            break;
        case OBJ_ID_FROM_BMS_LV:
            CANMessageGet(CANA_BASE, OBJ_ID_FROM_BMS_LV, &RXCANA_BmsLV_Message, true);

            int id = getMessageID(CANA_BASE, OBJ_ID_FROM_BMS_LV);

            read_BMSLV_message((Uint16 *)RXA_BmsLV_Data, id);

            rxAMsgCount++;

            CANIntClear(CANA_BASE, OBJ_ID_FROM_BMS_LV);
            break;
        // case OBJ_ID_POWER_CONTROL:
        //      powerOK=true;
        //      //Uint16 value[1];
        //
        //      CANMessageGet(CANA_BASE, OBJ_ID_POWER_CONTROL, &RXCANA_PwCtrl_Message, true);
        //
        //      //powersetup[0]=value[0]; -----> spostato in car management
        //
        //      int id = getMessageID(CANA_BASE, OBJ_ID_POWER_CONTROL);
        //
        //      read_power_control_message((Uint16 *)RXA_PwCtrl_Data);
        //
        //      rxAMsgCount++;
        //
        //      CANIntClear(CANA_BASE, OBJ_ID_POWER_CONTROL);
        //      break;
        case OBJ_ID_STEERING_WHEEL:
            CANMessageGet(CANA_BASE, OBJ_ID_STEERING_WHEEL, &RXCANA_Wheel_Message, true);

            int id = getMessageID(CANA_BASE, OBJ_ID_STEERING_WHEEL);

            read_steering_wheel_message((Uint16 *)RXA_Wheel_Data, id);

            rxAMsgCount++;

            CANIntClear(CANA_BASE, OBJ_ID_STEERING_WHEEL);
            break;
        case OBJ_ID_FROM_LEM: //aggiunto  lem message
            CANMessageGet(CANA_BASE, OBJ_ID_FROM_LEM, &RXCANA_Lem_Message, true);

            read_LEM_message(RXA_Lem_Data);

            rxAMsgCount++;

            CANIntClear(CANA_BASE, OBJ_ID_FROM_LEM);
           break;
           //alberto patch
        case OBJ_ID_FROM_ATC:
            CANMessageGet(CANA_BASE, OBJ_ID_FROM_ATC, &TXCANA_ATC_Message, true);

            read_ATC_message(RXA_ATC_DATA);

            rxAMsgCount++;

            CANIntClear(CANA_BASE,OBJ_ID_FROM_ATC);
           break;
           //alberto patch

    }
    CANGlobalIntClear(CANA_BASE, CAN_GLB_INT_CANINT0);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

}

Uint32 getMessageID(Uint32 base, Uint32 objID)
{
    Uint32 msgID = 0;

    //CAN_transferMessage(base, 2, objID, false);

    msgID = HWREG(base + CAN_O_IF2ARB);
    msgID &= CAN_IF2ARB_STD_ID_M;
    msgID = msgID >> CAN_IF2ARB_STD_ID_S;

    return msgID;
}


void send_pwm_to_pcu(){

    CANMessageSet(CANA_BASE, OBJ_ID_TO_ATMEGA, &TXCANA_ATMega_Message, MSG_OBJ_TYPE_TX);

}


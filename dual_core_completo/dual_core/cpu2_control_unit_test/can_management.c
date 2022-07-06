#include "can_management.h"

unsigned long gg;

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

        RXCANB_AmkVal1_Message[i].ui32MsgID = AMK_VAL_1_IDS[i];
        RXCANB_AmkVal1_Message[i].ui32MsgIDMask = 0x1FFFFFF0;
        RXCANB_AmkVal1_Message[i].ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
        RXCANB_AmkVal1_Message[i].ui32MsgLen = MSG_DATA_LENGTH;
        RXCANB_AmkVal1_Message[i].pucMsgData = RXB_AmkVal_Data;

        CANMessageSet(CANB_BASE, OBJ_ID_FROM_AMK, &RXCANB_AmkVal1_Message[i], MSG_OBJ_TYPE_RX);


        RXCANB_AmkVal2_Message[i].ui32MsgID = AMK_VAL_2_IDS[i];
        RXCANB_AmkVal2_Message[i].ui32MsgIDMask = 0x1FFFFFF0;
        RXCANB_AmkVal2_Message[i].ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
        RXCANB_AmkVal2_Message[i].ui32MsgLen = MSG_DATA_LENGTH;
        RXCANB_AmkVal2_Message[i].pucMsgData = RXB_AmkVal_Data;

        CANMessageSet(CANB_BASE, OBJ_ID_FROM_AMK, &RXCANB_AmkVal2_Message[i], MSG_OBJ_TYPE_RX);


        TXCANB_Setpoints_Message[i].ui32MsgID = AMK_SETPOINTS_IDS[i];                      // CAN message ID - use 1
        TXCANB_Setpoints_Message[i].ui32MsgIDMask = 0;                  // no mask needed for TX
        TXCANB_Setpoints_Message[i].ui32Flags = MSG_OBJ_NO_FLAGS;  // enable interrupt on TX
        TXCANB_Setpoints_Message[i].ui32MsgLen = sizeof(CAN_AMK_SET_POINT[i]);   // size of message is 8
        TXCANB_Setpoints_Message[i].pucMsgData = TXB_Setpoints_Data[i];           // ptr to message content

        }

        //Pacchetto accelerazioni IMU
        RXCANA_Imu_Message.ui32MsgID = MSG_ID_IMU_BASE;
        RXCANA_Imu_Message.ui32MsgIDMask = 0x1FFFFFFC;
        RXCANA_Imu_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
        RXCANA_Imu_Message.ui32MsgLen = MSG_DATA_LENGTH;
        RXCANA_Imu_Message.pucMsgData = RXA_Imu_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_FROM_IMU, &RXCANA_Imu_Message, MSG_OBJ_TYPE_RX);

        //Pacchetto generico SMU
        RXCANA_Smu_Message.ui32MsgID = MSG_ID_SMU_BASE;
        RXCANA_Smu_Message.ui32MsgIDMask = 0x1FFFFFF8;
        RXCANA_Smu_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
        RXCANA_Smu_Message.ui32MsgLen = MSG_DATA_LENGTH;
        RXCANA_Smu_Message.pucMsgData = RXA_Smu_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_FROM_SMU, &RXCANA_Smu_Message, MSG_OBJ_TYPE_RX);

        /*RXCANA_Smu_Message.ui32MsgID = MSG_ID_SMU_BASE;
        RXCANA_Smu_Message.ui32MsgIDMask = 0x0;
        RXCANA_Smu_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
        RXCANA_Smu_Message.ui32MsgLen = MSG_DATA_LENGTH;
        RXCANA_Smu_Message.pucMsgData = RXA_Smu_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_FROM_SMU, &RXCANA_Smu_Message, MSG_OBJ_TYPE_RX);*/

        for(i = 0; i < 5; i++){
            TXCANA_Smu_Message[i].ui32MsgID = MSG_ID_CALIBRATION_TO_SMU;
            TXCANA_Smu_Message[i].ui32MsgIDMask = 0;                  // no mask needed for TX
            TXCANA_Smu_Message[i].ui32Flags = MSG_OBJ_NO_FLAGS;
            TXCANA_Smu_Message[i].ui32MsgLen = MSG_DATA_LENGTH;
            TXCANA_Smu_Message[i].pucMsgData = TXA_Smu_Calibration[i];
        }

        //Pacchetto BMS VOLTAGE
        RXCANA_BmsVol_Message.ui32MsgID = MSG_ID_BMS_VOLTAGE;
        RXCANA_BmsVol_Message.ui32MsgIDMask = 0x0;
        RXCANA_BmsVol_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
        RXCANA_BmsVol_Message.ui32MsgLen = 6;
        RXCANA_BmsVol_Message.pucMsgData = RXA_BmsVol_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_BMS_VOLTAGE, &RXCANA_BmsVol_Message, MSG_OBJ_TYPE_RX);

        //PACCHETTO BMS TEMPERATURE
        RXCANA_BmsTemp_Message.ui32MsgID = MSG_ID_BMS_TEMP;
        RXCANA_BmsTemp_Message.ui32MsgIDMask = 0x0;
        RXCANA_BmsTemp_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
        RXCANA_BmsTemp_Message.ui32MsgLen = 6;
        RXCANA_BmsTemp_Message.pucMsgData = RXA_BmsTemp_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_BMS_TEMP, &RXCANA_BmsTemp_Message, MSG_OBJ_TYPE_RX);

        //PACCHETTO BMS LV
        RXCANA_BmsLV_Message.ui32MsgID = MSG_ID_BMS_BASE;
        RXCANA_BmsLV_Message.ui32MsgIDMask = 0x1FFFFFFC;
        RXCANA_BmsLV_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
        RXCANA_BmsLV_Message.ui32MsgLen = 8;
        RXCANA_BmsLV_Message.pucMsgData = RXA_BmsLV_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_FROM_BMS_LV, &RXCANA_BmsLV_Message, MSG_OBJ_TYPE_RX);

        //PACCHETTO POWER CONTROL DAL VOLANTE
        RXCANA_PwCtrl_Message.ui32MsgID = MSG_ID_POWER_CONTROL;
        RXCANA_PwCtrl_Message.ui32MsgIDMask = 0x0;
        RXCANA_PwCtrl_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
        RXCANA_PwCtrl_Message.ui32MsgLen = 1;
        RXCANA_PwCtrl_Message.pucMsgData = RXA_PwCtrl_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_POWER_CONTROL, &RXCANA_PwCtrl_Message, MSG_OBJ_TYPE_RX);

        //PACCHETTO DA VOLANTE
        RXCANA_Wheel_Message.ui32MsgID = MSG_ID_STEERING_WHEEL_BASE;
        RXCANA_Wheel_Message.ui32MsgIDMask = 0x1FFFFFF8;
        RXCANA_Wheel_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
        RXCANA_Wheel_Message.ui32MsgLen = 1;
        RXCANA_Wheel_Message.pucMsgData = RXA_Wheel_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_STEERING_WHEEL, &RXCANA_Wheel_Message, MSG_OBJ_TYPE_RX);

        //PACCHETTO DA LEM
        RXCANA_Lem_Message.ui32MsgID = MSG_ID_LEM;
        RXCANA_Lem_Message.ui32MsgIDMask = 0x0;
        RXCANA_Lem_Message.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
        RXCANA_Lem_Message.ui32MsgLen = MSG_DATA_LENGTH;
        RXCANA_Lem_Message.pucMsgData = RXA_Lem_Data;

        CANMessageSet(CANA_BASE, OBJ_ID_FROM_LEM, &RXCANA_Lem_Message, MSG_OBJ_TYPE_RX);


        CANEnable(CANA_BASE);
        CANEnable(CANB_BASE);
}

__interrupt void canISR_B(void)
{
    uint32_t status;

    status = CANIntStatus(CANB_BASE, CAN_INT_STS_CAUSE);


    if(status == CAN_INT_INT0ID_STATUS)
    {

        status = CANStatusGet(CANB_BASE, CAN_STS_CONTROL);

        if(((status  & ~(CAN_ES_TXOK | CAN_ES_RXOK)) != 7) &&
           ((status  & ~(CAN_ES_TXOK | CAN_ES_RXOK)) != 0))
        {
            errorFlag = 1;
            errorFrameCounterB++;
        }


        CANIntClear(CANB_BASE, CAN_INT_INT0ID_STATUS);


    }

    //
    // Check if the cause is the receive message object 2
    //
    else if(status == OBJ_ID_FROM_AMK)
    {
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
    }
    else
    {

    }

    CANGlobalIntClear(CANB_BASE, CAN_GLB_INT_CANINT0);
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

__interrupt void canISR_A(void)
{
    uint32_t status;

    status = CANIntStatus(CANA_BASE, CAN_INT_STS_CAUSE);
    gg =status; // for debug


    if(status == CAN_INT_INT0ID_STATUS)
    {

        status = CANStatusGet(CANA_BASE, CAN_STS_CONTROL);



        if(((status  & ~(CAN_ES_TXOK | CAN_ES_RXOK)) != 7) &&
           ((status  & ~(CAN_ES_TXOK | CAN_ES_RXOK)) != 0))
        {

            errorFlag = 1;
            errorFrameCounterA++;
        }

        CANIntClear(CANA_BASE, CAN_INT_INT0ID_STATUS);

    }/* else if (status == OBJ_ID_FROM_SENDYNE) // sendyne DEPRECATED. IL SENDYNE NON VIENE PIU USATO

    {

        CANMessageGet(CANA_BASE, OBJ_ID_FROM_SENDYNE, &RXCANA_Sendyne_Message, true);
//        CAN_readMessage(CANA_BASE, OBJ_ID_FROM_SENDYNE, (uint16_t *) CAN_SENDYNE_ACT_VALUES);

        read_SENDYNE_message(RXA_Sendyne_Data);

        rxAMsgCount++;

        CANIntClear(CANA_BASE, OBJ_ID_FROM_SENDYNE);

    }*/
    else if (status == OBJ_ID_FROM_IMU){
        //Uint16 imu_msg_temp[8];
        CANMessageGet(CANA_BASE, OBJ_ID_FROM_IMU, &RXCANA_Imu_Message, true);

        int id = getMessageID(CANA_BASE, OBJ_ID_FROM_IMU);

        read_IMU_message((Uint16 *)RXA_Imu_Data, id);

        rxAMsgCount++;

        CANIntClear(CANA_BASE, OBJ_ID_FROM_IMU);
    }
    else if(status == OBJ_ID_FROM_SMU){
        //Ricevuto pacchetto da mailbox dello SMU
        CANMessageGet(CANA_BASE, OBJ_ID_FROM_SMU, &RXCANA_Smu_Message, true);

        int id = getMessageID(CANA_BASE, OBJ_ID_FROM_SMU);

        read_SMU_Message((Uint16 *)RXA_Smu_Data, id);

        rxAMsgCount++;

        CANIntClear(CANA_BASE, OBJ_ID_FROM_SMU);
    }
    /*else if(status == OBJ_ID_FROM_SMU){
            //Ricevuto pacchetto da mailbox dello SMU
            CANMessageGet(CANA_BASE, OBJ_ID_FROM_SMU, &RXCANA_Smu_Message, true);

            int id = getMessageID(CANA_BASE, OBJ_ID_FROM_SMU);

            read_SMU_Message_temp((Uint16 *)RXA_Smu_Data, id);

            rxAMsgCount++;

            CANIntClear(CANA_BASE, OBJ_ID_FROM_SMU);
    }*/
    else if (status == OBJ_ID_BMS_VOLTAGE){
       //Uint16 bms_msg_temp[6];

       CANMessageGet(CANA_BASE, OBJ_ID_BMS_VOLTAGE, &RXCANA_Imu_Message, true);

       int id = getMessageID(CANA_BASE, OBJ_ID_BMS_VOLTAGE);

       read_BMS_VOLTAGE_message((Uint16 *)RXA_BmsVol_Data);

       rxAMsgCount++;

       CANIntClear(CANA_BASE, OBJ_ID_BMS_VOLTAGE);

   }
   else if (status == OBJ_ID_BMS_TEMP){
       //Uint16 bms_msg_temp[6];

       CANMessageGet(CANA_BASE, OBJ_ID_BMS_TEMP, &RXCANA_BmsTemp_Message, true);

       int id = getMessageID(CANA_BASE, OBJ_ID_BMS_TEMP);


       read_BMS_TEMP_message((Uint16 *)RXA_BmsTemp_Data);

       rxAMsgCount++;

       CANIntClear(CANA_BASE, OBJ_ID_BMS_TEMP);

   }else if(status == OBJ_ID_FROM_BMS_LV){

       CANMessageGet(CANA_BASE, OBJ_ID_FROM_BMS_LV, &RXCANA_BmsTemp_Message, true);

       int id = getMessageID(CANA_BASE, OBJ_ID_FROM_BMS_LV);

       read_BMSLV_message((Uint16 *)RXA_BmsLV_Data, id);

       rxAMsgCount++;

       CANIntClear(CANA_BASE, OBJ_ID_FROM_BMS_LV);
   }
   else if (status == OBJ_ID_POWER_CONTROL)
   {
       powerOK=true;
       //Uint16 value[1];

       CANMessageGet(CANA_BASE, OBJ_ID_POWER_CONTROL, &RXCANA_PwCtrl_Message, true);

       //powersetup[0]=value[0]; -----> spostato in car management

       int id = getMessageID(CANA_BASE, OBJ_ID_POWER_CONTROL);

       read_power_control_message((Uint16 *)RXA_PwCtrl_Data);

       rxAMsgCount++;

       CANIntClear(CANA_BASE, OBJ_ID_POWER_CONTROL);
   }
   else if (status == OBJ_ID_STEERING_WHEEL)
   {
       CANMessageGet(CANA_BASE, OBJ_ID_STEERING_WHEEL, &RXCANA_Wheel_Message, true);

       int id = getMessageID(CANA_BASE, OBJ_ID_STEERING_WHEEL);

       read_steering_wheel_message((Uint16 *)RXA_Wheel_Data, id);

       rxAMsgCount++;

       CANIntClear(CANA_BASE, OBJ_ID_STEERING_WHEEL);

    } else if (status == OBJ_ID_FROM_LEM)   //aggiunto  lem message
    {

        CANMessageGet(CANA_BASE, OBJ_ID_FROM_LEM, &RXCANA_Lem_Message, true);

        read_LEM_message(RXA_Lem_Data);

        rxAMsgCount++;

        CANIntClear(CANA_BASE, OBJ_ID_FROM_LEM);

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


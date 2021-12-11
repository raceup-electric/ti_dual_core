#include "can_management.h"

#define OBJ_ID_RX_A     1
#define OBJ_ID_TX_A     2
#define MSG_ID_RX_A     0x121
#define MSG_ID_TX_A     0x100


void canSetup()
{
    //
    // Configure GPIO pins for CANTX/CANRX
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXB);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXB);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXA);
    //
    // Initialize the CAN controller
    //
    CAN_initModule(CANB_BASE);
    CAN_initModule(CANA_BASE);

    //
    // Set up the CAN bus bit rate to 500kHz for each module
    // Refer to the Driver Library User Guide for information on how to set
    // tighter timing control. Additionally, consult the device data sheet
    // for more information about the CAN module clocking.
    //

    CAN_setBitRate(CANB_BASE, DEVICE_SYSCLK_FREQ, 1000000, 10);
    CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 1000000, 10);


    //
    //FROM can_ex2_loopback_interrupts.c example ---------------------------------------------
    //
    //

    //
    // Enable interrupts on the CAN peripheral.
    // Enables Interrupt line 0, Error & Status Change interrupts in CAN_CTL
    // register.
    //
    CAN_enableInterrupt(CANB_BASE, CAN_INT_IE0 | CAN_INT_ERROR |
                        CAN_INT_STATUS);

    CAN_enableInterrupt(CANA_BASE, CAN_INT_IE0 | CAN_INT_ERROR |
                        CAN_INT_STATUS);

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    // This registers the interrupt handler in PIE vector table.
    //
    Interrupt_register(INT_CANB0, &canISR_B);
    Interrupt_register(INT_CANA0, &canISR_A);


    //
    // Enable the CAN interrupt signal
    //
    Interrupt_enable(INT_CANB0);
    CAN_enableGlobalInterrupt(CANB_BASE, CAN_GLOBAL_INT_CANINT0);

    Interrupt_enable(INT_CANA0);
    CAN_enableGlobalInterrupt(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

    //
    // Initialize the receive message object used for receiving CAN messages.

    int i;
    for (i = 0; i<4; i++)
    {
        CAN_setupMessageObject(CANB_BASE, OBJ_ID_FROM_AMK, AMK_VAL_1_IDS[i],        //AMK actual values 1
                               CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0x1FFFFFF0,
                               CAN_MSG_OBJ_RX_INT_ENABLE | CAN_MSG_OBJ_USE_ID_FILTER, MSG_DATA_LENGTH);

        CAN_setupMessageObject(CANB_BASE, OBJ_ID_FROM_AMK, AMK_VAL_2_IDS[i],        //AMK actual values 2
                               CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0x1FFFFFF0,
                               CAN_MSG_OBJ_RX_INT_ENABLE | CAN_MSG_OBJ_USE_ID_FILTER, MSG_DATA_LENGTH);

        CAN_setupMessageObject(CANB_BASE, (14 + i), AMK_SETPOINTS_IDS[i],           //AMK setpoints
                               CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                               CAN_MSG_OBJ_NO_FLAGS, sizeof(CAN_AMK_SET_POINT[i]));

    }

    CAN_setupMessageObject(CANA_BASE, OBJ_ID_FROM_IMU, MSG_ID_IMU_BASE,                  //IMU
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0x1FFFFFFC,
                           CAN_MSG_OBJ_RX_INT_ENABLE | CAN_MSG_OBJ_USE_ID_FILTER, MSG_DATA_LENGTH);

    CAN_setupMessageObject(CANA_BASE, OBJ_ID_FROM_SENDYNE, MSG_ID_SENDYNE,            //SENDYNE
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0x0,
                           CAN_MSG_OBJ_RX_INT_ENABLE, MSG_DATA_LENGTH);

    CAN_setupMessageObject(CANA_BASE, OBJ_ID_BMS_VOLTAGE, MSG_ID_BMS_VOLTAGE,            //BMS VOLTAGE
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0x0,
                           CAN_MSG_OBJ_RX_INT_ENABLE, 6);

    CAN_setupMessageObject(CANA_BASE, OBJ_ID_BMS_TEMP, MSG_ID_BMS_TEMP,            //BMS TEMP
                              CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0x0,
                              CAN_MSG_OBJ_RX_INT_ENABLE, 6);

    CAN_setupMessageObject(CANA_BASE, OBJ_ID_POWER_CONTROL, MSG_ID_POWER_CONTROL,            //POWER CONTROL
                                  CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0x0,
                                  CAN_MSG_OBJ_RX_INT_ENABLE, 1);

//    CAN_setupMessageObject(CANA_BASE, OBJ_ID_RX_A, MSG_ID_RX_A,
//                            CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0x0,
//                            CAN_MSG_OBJ_RX_INT_ENABLE, MSG_DATA_LENGTH);
//
//    CAN_setupMessageObject(CANA_BASE, OBJ_ID_TX_A, MSG_ID_TX_A,
//                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
//                           CAN_MSG_OBJ_NO_FLAGS, 8);

    CAN_setupMessageObject(CANA_BASE, OBJ_ID_TEMPS, MSG_ID_TEMPS,                   //temps
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, 8);

    CAN_setupMessageObject(CANA_BASE, OBJ_ID_SENDYNE_FORWARD, MSG_ID_SENDYNE_FORWARD,                   //inoltro sendyne
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, 8);

    CAN_setupMessageObject(CANA_BASE, OBJ_ID_CAR_STATUS, MSG_ID_CAR_STATUS,         //car status
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, 7);

    CAN_setupMessageObject(CANA_BASE, OBJ_ID_AMK_SETPOINTS, MSG_ID_AMK_SETPOINTS,         //setpoints alla teensy
                               CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                               CAN_MSG_OBJ_NO_FLAGS, 8);

    for (i = 0; i < 4; i++)
    {
        CAN_setupMessageObject(CANA_BASE, OBJ_ID_AMK1_DATA_BASE + i, MSG_ID_AMK1_DATA_BASE + i,
                               CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                               CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);

        CAN_setupMessageObject(CANA_BASE, OBJ_ID_AMK2_DATA_BASE + i, MSG_ID_AMK2_DATA_BASE + i,
                                       CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_TX, 0,
                                       CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);
    }

    //
    // Start CAN module operations
    //
    CAN_startModule(CANB_BASE);
    CAN_startModule(CANA_BASE);


}

//
// CAN ISR - The interrupt service routine called when a CAN interrupt is
//           triggered.  It checks for the cause of the interrupt, and
//           maintains a count of all messages that have been transmitted.
//
__interrupt void
canISR_B(void)
{
    uint32_t status;

    //
    // Read the CAN interrupt status to find the cause of the interrupt
    //
    status = CAN_getInterruptCause(CANB_BASE);

    //
    // If the cause is a controller status interrupt, then get the status
    //
    if(status == CAN_INT_INT0ID_STATUS)
    {
        //
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for simplicity.  Refer to the
        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.
        //
        status = CAN_getStatus(CANB_BASE);

        //
        // Check to see if an error occurred.
        //
        if(((status  & ~(CAN_STATUS_TXOK | CAN_STATUS_RXOK)) != 7) &&
           ((status  & ~(CAN_STATUS_TXOK | CAN_STATUS_RXOK)) != 0))
        {
            //
            // Set a flag to indicate some errors may have occurred.
            //
            errorFlag = 1;
            errorFrameCounterB++;
        }

        CAN_clearInterruptStatus(CANB_BASE, CAN_INT_INT0ID_STATUS);

    }

    //
    // Check if the cause is the receive message object 2
    //
    else if(status == OBJ_ID_FROM_AMK)
    {
        uint8_t amk_temp[8];
        //
        // Get the received message
        //
        CAN_readMessage(CANB_BASE, OBJ_ID_FROM_AMK, amk_temp);

        int id = getMessageID(CANB_BASE,OBJ_ID_FROM_AMK);

        if (getAMKValNumber(id) == 1)
        {
            rxBMsgCount++;
            read_AMK_Values1(amk_temp, getMotorIndex(id));
        }
        else if (getAMKValNumber(id) == 2)
        {
            rxBMsgCount++;
            read_AMK_Values2(amk_temp, getMotorIndex(id));
        }

        //
        // Getting to this point means that the RX interrupt occurred on
        // message object 2, and the message RX is complete.  Clear the
        // message object interrupt.
        //
        CAN_clearInterruptStatus(CANB_BASE, OBJ_ID_FROM_AMK);

        //
        // Increment a counter to keep track of how many messages have been
        // received. In a real application this could be used to set flags to
        // indicate when a message is received.
        //


        //
        // Since the message was received, clear any error flags.
        //
        errorFlag = 0;
    }

    //
    // If something unexpected caused the interrupt, this would handle it.
    //
    else
    {
        //
        // Spurious interrupt handling can go here.
        //
    }

    //
    // Clear the global interrupt flag for the CAN interrupt line
    //
    CAN_clearGlobalInterruptStatus(CANB_BASE, CAN_GLOBAL_INT_CANINT0);

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

__interrupt void
canISR_A(void)
{
    uint32_t status;

    //
    // Read the CAN interrupt status to find the cause of the interrupt
    //
    status = CAN_getInterruptCause(CANA_BASE);

    //
    // If the cause is a controller status interrupt, then get the status
    //
    if(status == CAN_INT_INT0ID_STATUS)
    {
        //
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for s

        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.
        //
        status = CAN_getStatus(CANA_BASE);

        //
        // Check to see if an error occurred.
        //
        if(((status  & ~(CAN_STATUS_TXOK | CAN_STATUS_RXOK)) != 7) &&
           ((status  & ~(CAN_STATUS_TXOK | CAN_STATUS_RXOK)) != 0))
        {
            //
            // Set a flag to indicate some errors may have occurred.
            //
            errorFlag = 1;
            errorFrameCounterA++;

        }

        CAN_clearInterruptStatus(CANA_BASE, CAN_INT_INT0ID_STATUS);

    } else if (status == OBJ_ID_FROM_SENDYNE)
    {
        //
        // Get the received message
        //
        CAN_readMessage(CANA_BASE, OBJ_ID_FROM_SENDYNE, (uint16_t *) CAN_SENDYNE_ACT_VALUES);

        read_SENDYNE_message(CAN_SENDYNE_ACT_VALUES);

        rxAMsgCount++;

        CAN_clearInterruptStatus(CANA_BASE, OBJ_ID_FROM_SENDYNE);

    }
    else if (status == OBJ_ID_FROM_IMU){
        uint8_t imu_msg_temp[8];
        //
        // Get the received message
        //
        CAN_readMessage(CANA_BASE, OBJ_ID_FROM_IMU, imu_msg_temp);

        int id = getMessageID(CANA_BASE, OBJ_ID_FROM_IMU);

        read_IMU_message(imu_msg_temp, id);

        rxAMsgCount++;

        CAN_clearInterruptStatus(CANA_BASE, OBJ_ID_FROM_IMU);

    }
    else if (status == OBJ_ID_BMS_VOLTAGE){
       uint8_t bms_msg_temp[6];
       //
       // Get the received message
       //
       CAN_readMessage(CANA_BASE, OBJ_ID_BMS_VOLTAGE, bms_msg_temp);

       int id = getMessageID(CANA_BASE, OBJ_ID_BMS_VOLTAGE);

       read_BMS_VOLTAGE_message(bms_msg_temp);

       rxAMsgCount++;

       CAN_clearInterruptStatus(CANA_BASE, OBJ_ID_BMS_VOLTAGE);
   }
   else if (status == OBJ_ID_BMS_TEMP){
       uint8_t bms_msg_temp[6];
       //
       // Get the received message
       //
       CAN_readMessage(CANA_BASE, OBJ_ID_BMS_TEMP, bms_msg_temp);

       int id = getMessageID(CANA_BASE, OBJ_ID_BMS_TEMP);

       read_BMS_TEMP_message(bms_msg_temp);

       rxAMsgCount++;

       CAN_clearInterruptStatus(CANA_BASE, OBJ_ID_BMS_TEMP);

   }
   else if (status == OBJ_ID_POWER_CONTROL)
   {
       powerOK=true;
       uint8_t value[1];
       //
       // Get the received message
       //
       CAN_readMessage(CANA_BASE, OBJ_ID_POWER_CONTROL, value);
       powersetup[0]=value[0];

       int id = getMessageID(CANA_BASE, OBJ_ID_POWER_CONTROL);

       read_power_control_message(value);

       rxAMsgCount++;

       CAN_clearInterruptStatus(CANA_BASE, OBJ_ID_POWER_CONTROL);

   }

    //
    // Check if the cause is the receive message object 2
    //
    else if(status == OBJ_ID_RX_A)
    {
        //
        // Get the received message
        //

        CAN_readMessage(CANA_BASE, OBJ_ID_RX_A, RX_A_temp);

        //
        // Getting to this point means that the RX interrupt occurred on
        // message object 2, and the message RX is complete.  Clear the
        // message object interrupt.
        //
        CAN_clearInterruptStatus(CANA_BASE, OBJ_ID_RX_A);

        //
        // Increment a counter to keep track of how many messages have been
        // received. In a real application this could be used to set flags to
        // indicate when a message is received.
        //
        GPIO_togglePin(DEVICE_GPIO_PIN_LED2);

        rxAMsgCount++;

        //
        // Since the message was received, clear any error flags.
        //
        errorFlag = 0;
    }


    //
    // Clear the global interrupt flag for the CAN interrupt line
    //
    CAN_clearGlobalInterruptStatus(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}


uint32_t getMessageID(uint32_t base, uint32_t objID)
{
    uint32_t msgID = 0;

    CAN_transferMessage(base, 2, objID, false);

    msgID = HWREG(base + CAN_O_IF2ARB);
    msgID &= CAN_IF2ARB_STD_ID_M;
    msgID = msgID >> CAN_IF2ARB_STD_ID_S;

    return msgID;
}


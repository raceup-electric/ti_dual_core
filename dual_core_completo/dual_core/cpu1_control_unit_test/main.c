#include "main.h"
#include "F2837xD_device.h"
#include "sys/_stdint.h"
#include <stdint.h>

void main(void)
{

    InitSysCtrl();

    // if standalone is active cpu1 will try to start cpu2
    #ifdef _STANDALONE
        #ifdef _FLASH
            IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
        #else
            IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
        #endif
    #endif

    InitGpio();

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    cpu1_timer_setup();

    // stop both timers
    CpuTimer1Regs.TCR.bit.TSS = 1;
    CpuTimer2Regs.TCR.bit.TSS = 1;

    GPIOSetup();

    uart_esp_setup();

    // Write auth of some banks of Global Shared (GS) RAM is
    // given to CPU2
    while (!(
        MemCfgRegs.GSxMSEL.bit.MSEL_GS15 &
        MemCfgRegs.GSxMSEL.bit.MSEL_GS14 &
        MemCfgRegs.GSxMSEL.bit.MSEL_GS13 &
        MemCfgRegs.GSxMSEL.bit.MSEL_GS12 &
        MemCfgRegs.GSxMSEL.bit.MSEL_GS11))
    {
        EALLOW;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS15 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS14 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS13 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS12 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS11 = 1;
        EDIS;
    }

    EINT;
    ERTM;

    InitEPwm4Gpio();
    InitEPwm5Gpio();
    InitEPwm6Gpio();

    // Muxing epwm e adc to CPU2
    EALLOW;
    DevCfgRegs.CPUSEL0.bit.EPWM4 = 1;
    DevCfgRegs.CPUSEL0.bit.EPWM5 = 1;
    DevCfgRegs.CPUSEL0.bit.EPWM6 = 1;
    DevCfgRegs.CPUSEL11.bit.ADC_A = 1;
    DevCfgRegs.CPUSEL11.bit.ADC_B = 1;
    DevCfgRegs.CPUSEL11.bit.ADC_C = 1;
    EDIS;

    // CAN muxed to CPU2
    send_can_to_cpu2();

    // shared struct copied in local variable
    local_sh = sh;

    CpuTimer1Regs.TCR.bit.TSS = 0; // Start SD timer
    // stop timer2 - it's not used for the moment
    CpuTimer2Regs.TCR.bit.TSS = 1;

    Uint16 receivedChar;
    char* buffer;
    int count_char = 0;

    for(;;)
    {
        while(ScibRegs.SCIFFRX.bit.RXFFST == 0) { } // wait for empty state

        receivedChar = ScibRegs.SCIRXBUF.all;
        buffer[count_char] = receivedChar;

        if(buffer[0] != '$') {
            memset(buffer, 0, count_char);
            count_char = 0;
            continue;
        }

        if(receivedChar == '\n' && count_char > 0){
            buffer[count_char] = '\0';

            char decode_complete = parse_NMEA_buffer(buffer, &gps_data);
            memset(buffer, 0, count_char);
            count_char = 0;

            if(setStart && degreeToFloat(&gps_data.lat0) == 0 && degreeToFloat(&gps_data.lon0) == 0){
                gps_data.lat0 = gps_data.latitude;
                gps_data.lon0 = gps_data.longitude;
                // chatGPT
                double lat1 = degreeToFloat(&gps_data.lat0) * M_PI / 180.0;
                double lon1 = degreeToFloat(&gps_data.lon0) * M_PI / 180.0;
                double lat2 = local_sh.gps_shared.lati * M_PI / 180.0;
                double lon2 = local_sh.gps_shared.longi * M_PI / 180.0;

                double dlat = lat2 - lat1;
                double dlon = lon2 - lon1;

                double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
                double c = 2 * atan2(sqrt(a), sqrt(1 - a));

                // Earth radius
                if((6371000 * c) < 1.5) local_sh.gps_shared.lap++;
            }
        }

        count_char++;
    }
}

void cpu1_timer_setup(void)
{
    EALLOW;
    PieVectTable.TIMER1_INT = &cpu_timer1_isr;
    PieVectTable.TIMER2_INT = &cpu_timer2_isr;
    EDIS;

    InitCpuTimers();

    ConfigCpuTimer(&CpuTimer1, 200, 20000); //20 ms timer1
    ConfigCpuTimer(&CpuTimer2, 200, 8000);

    CpuTimer1Regs.TCR.all = 0x4000;
    CpuTimer2Regs.TCR.all = 0x4000;

    IER |= M_INT13; // timer1
    IER |= M_INT14; // timer2

    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
}

void send_can_to_cpu2(void)
{
    EALLOW;
    CpuSysRegs.PCLKCR10.bit.CAN_A = 0;
    CpuSysRegs.PCLKCR10.bit.CAN_B = 0;
    EDIS;

    EALLOW;
    DevCfgRegs.CPUSEL8.bit.CAN_A = 1;
    DevCfgRegs.CPUSEL8.bit.CAN_B = 1;
    EDIS;

    CANInit(CANA_BASE);
    CANInit(CANB_BASE);
}

/*
 * every cycle of timer1 shared data are copied into
 * local variables to avoid concurrent access of cpu2 while
 * cpu1 is logging
 */
void Shared_Ram_dataRead_c1(void)
{
    int lap = local_sh.gps_shared.lap;

    local_sh = sh;
    local_time_elapsed = time_elapsed;

    local_sh.gps_shared.lap = lap;
}

/*
 * Timer1 integrates all features: logging, display and LoRa
 *      - Logging is active every cycle.
 *      - Display updates every 5 cycles.
 *      - LoRa is active every cycle, but LoRa code is alternated to
 *        logging code, to give receiving buffer time to flush
 * if MORE_FILES function is active, a new log file will be
 * created periodically. This is a safer configuration if log files are
 * corrupted because of critical situations.
 */
__interrupt void cpu_timer1_isr(void)
{
    CpuTimer1.InterruptCount++;

    Shared_Ram_dataRead_c1();

    /*
     * Il gps viene usato solo in telemetria quindi
     * viene aggiornata la local_sh solo prima di inviare
     *
     * Per sviluppi futuri va aggiornata sh in modo che anche
     * CPU2 riesca ad accedere a quei dati
     */
    local_sh.gps_shared.velocity = gps_data.velocity;
    local_sh.gps_shared.lati = degreeToFloat(&gps_data.latitude);
    local_sh.gps_shared.longi = degreeToFloat(&gps_data.longitude);

    // send to esp32
    char data[sizeof(local_sh)];
    memcpy(data, &local_sh, sizeof(local_sh));

    char ptr[sizeof(local_sh)*2];

    int i;
    for(i=0; i<sizeof(local_sh); i++){
        ptr[i*2] = data[i] & 0x00FF;
        ptr[i*2+1] = data[i] >> 8;
    }

    char encoded[sizeof(ptr) + 2];
    cobs_encode(encoded, sizeof(encoded)-1, &ptr, sizeof(ptr));
    encoded[sizeof(ptr) + 1] = '\0';

    scic_msg(encoded);

    if (CpuTimer1.InterruptCount % 5 == 0)
    {
        EALLOW;
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        EDIS;
    }
}

// not necessary at the moment
__interrupt void cpu_timer2_isr(void)
{
}

/*
 * Function to compress amk status in one Byte, index is 0 FL 1 FR 2 RL 3 RR
 */
uint8_t compute_AMKStatus(uint8_t index)
{
    int status = 0;
    status |= (local_sh.motorVal1[index].AMK_bSystemReady);
    status |= (local_sh.motorVal1[index].AMK_bError << 1);
    status |= (local_sh.motorVal1[index].AMK_bWarn << 2);
    status |= (local_sh.motorVal1[index].AMK_bQuitDcOn << 3);
    status |= (local_sh.motorVal1[index].AMK_bDcOn << 4);
    status |= (local_sh.motorVal1[index].AMK_bQuitInverterOn << 5);
    status |= (local_sh.motorVal1[index].AMK_bInverterOn << 6);
    status |= (local_sh.motorVal1[index].AMK_bInverterOn << 7);

    return status;
}





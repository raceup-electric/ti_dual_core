#include "main.h"

volatile int setupOk = 0;
int loopCounter = 0;


void main(void)
{
    #ifdef _FLASH
        memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
    #endif
   setup();

   loop();
}

void loop()
{
#ifdef DEBUG_NO_HV
    enableMotor = true; //debug
#endif
    while(true) {
        if(isHVOn()) {
            if(!enableMotor) {
                enableMotor = true;
            }
        } else {
            enableMotor = false;
        }

    loopCounter++; //debug
    }
}


void setup()
{

       InitSysCtrl();

       while(!( MemCfgRegs.GSxMSEL.bit.MSEL_GS15 &
                MemCfgRegs.GSxMSEL.bit.MSEL_GS14 &
                MemCfgRegs.GSxMSEL.bit.MSEL_GS13 &
                MemCfgRegs.GSxMSEL.bit.MSEL_GS12 &
                MemCfgRegs.GSxMSEL.bit.MSEL_GS11  ))
       {
       }

       canSetup_phase1();

       DINT;

       InitPieCtrl();

       IER = 0x0000;
       IFR = 0x0000;

       InitPieVectTable();

       GPIOSetup();

       epwmSetup();
       adcSetup();

       timerSetup();


       EINT;
       ERTM;

       canSetup_phase2();

       GPIO_WritePin(BLUE_BLINK, 1U);



       int index;
       for(index = 0; index < 4; index++)
       {
           sh.motorVal1[index] = motorVal1_shared[index];
           sh.motorVal2[index] = motorVal2_shared[index];
           sh.motorSetP[index] = motorSetP_shared[index];
       }
       sh.imu = imu_log;
       sh.fanSpeed = fanspeed_log;
       sh.power = power_log;
       sh.bms = bms_log;
       sh.status = status_log;
       sh.gpio = gpio_log;
       sh.pedals = pedals_log;
       sh.power_setup = power_setup_log;


       display.ack_setup = 99;
       display.ack_pedal_setup = 99;
       display.ack_macros = 99;
       display.manual_speed_selector = false;
       display.ack_fan = 99;


       display.emergencyBrk_isNotSet = 1;

       setup_intialValue_pedals();

       setup_car_settings();

       setupOk = 1;    //debug

       time_elapsed = 0;

       CpuTimer1Regs.TCR.bit.TSS = 0;  //start timer1
}

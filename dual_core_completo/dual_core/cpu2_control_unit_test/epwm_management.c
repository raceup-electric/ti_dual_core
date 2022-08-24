/*
 * epwm_manager.c
 *
 *  Created on: Jan 29, 2022
 *      Author: Xhemali
 */
#include "epwm_management.h"

void epwmSetup()
{

    //
    //CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    //CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    //CpuSysRegs.PCLKCR2.bit.EPWM3=1;

    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM4=1;
    CpuSysRegs.PCLKCR2.bit.EPWM5=1;
    CpuSysRegs.PCLKCR2.bit.EPWM6=1;
    EDIS;


//    InitEPwm4Gpio();
//    InitEPwm5Gpio();
//    InitEPwm6Gpio();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    initEPWM4();
    initEPWM5();
    initEPWM6();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;


}

void initEPWM6()
{
    EPwm6Regs.TBPRD = EPWM_TIMER_TBPRD;
    EPwm6Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
    EPwm6Regs.TBCTR = 0x0000;                  // Clear counter

    //
    // Set Compare values
    //
    //commento riga 98 non ci serve epwmB
    EPwm6Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    //EPwm6Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    //
    // Setup counter mode
    //
    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
    EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    //
    // Setup shadowing
    //
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // Load on Zero
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Set actions
    //
    EPwm6Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up
                                                  // count
    EPwm6Regs.AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on event A,
                                                  // down count
    //Non ci serve la epwmB
    /*
    EPwm6Regs.AQCTLB.bit.CBU = AQ_SET;            // Set PWM1B on event B, up
                                                  // count
    EPwm6Regs.AQCTLB.bit.CBD = AQ_CLEAR;          // Clear PWM1B on event B,
    */                                              // down count

    // TO VERIFY
    // Interrupt where we will change the Compare Values
    //
    EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    EPwm6Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm6Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
}
void initEPWM5()
{

       EPwm5Regs.TBPRD = EPWM_TIMER_TBPRD;
       EPwm5Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
       EPwm5Regs.TBCTR = 0x0000;                  // Clear counter

       //
       // Set Compare values
       //
       EPwm5Regs.CMPA.bit.CMPA = 0;    // Set compare A value
       EPwm5Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

       //
       // Setup counter mode
       //
       EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
       EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
       EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
       EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

       //
       // Setup shadowing
       //
       EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
       EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
       EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // Load on Zero
       EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

       //
       // Set actions
       //
       EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up
                                                     // count
       EPwm5Regs.AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on event A,
                                                     // down count

       EPwm5Regs.AQCTLB.bit.CBU = AQ_SET;            // Set PWM1B on event B, up
                                                     // count
       EPwm5Regs.AQCTLB.bit.CBD = AQ_CLEAR;          // Clear PWM1B on event B,
                                                     // down count

       //
       // Interrupt where we will change the Compare Values
       //
       EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
       EPwm5Regs.ETSEL.bit.INTEN = 1;                // Enable INT
       EPwm5Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event


}
void initEPWM4()
{
    EPwm4Regs.TBPRD = EPWM_TIMER_TBPRD;
    EPwm4Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
    EPwm4Regs.TBCTR = 0x0000;                  // Clear counter

    //
    // Set Compare values
    //
    //COmmento riga 196 non usiamo epwmA
    //EPwm4Regs.CMPA.bit.CMPA = 0;    // Set compare A value
    EPwm4Regs.CMPB.bit.CMPB = 0;    // Set Compare B value

    //
    // Setup counter mode
    //
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
    EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    //
    // Setup shadowing
    //
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // Load on Zero
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Set actions
    //
    //Commento da riga 219 a riga 223 non usiamo epwmA
   /* EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up
                                                  // count
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on event A,
                                                  // down count
*/
    EPwm4Regs.AQCTLB.bit.CBU = AQ_SET;            // Set PWM1B on event B, up
                                                  // count
    EPwm4Regs.AQCTLB.bit.CBD = AQ_CLEAR;          // Clear PWM1B on event B,
                                                // down count

    // TO VERIFY
    // Interrupt where we will change the Compare Values
    //
    EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    EPwm4Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm4Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
}


Uint16 convertPercent(int perc)
{
    //perc = 100 - perc;  //LOGICA INVERTITA --- Commentare la linea se la logica non è invertita
    perc *= (EPWM_TIMER_TBPRD/100);
    if (perc == EPWM_TIMER_TBPRD)
        return 1;

    return EPWM_TIMER_TBPRD - perc;
}

/*
 * Logic is inverted so speed = 0 sets the fans to maximum
 */
void setFanSpeed(int fan, int speed){
    switch(fan){
    case VENTOLA_SX:
        EPwm5Regs.CMPA.bit.CMPA=convertPercent(speed);
    break;
    case VENTOLA_DX:
        EPwm4Regs.CMPB.bit.CMPB=convertPercent(speed);
    break;
    }
}

/*
 * Logic is inverted so speed = 0 sets the pumps to maximum
 */
void setPumpSpeed(int pump, int speed){
    switch(pump){
    case POMPA_SX:
        EPwm6Regs.CMPA.bit.CMPA=convertPercent(speed);
    break;
    case POMPA_DX:
        EPwm5Regs.CMPB.bit.CMPB=convertPercent(speed);
    break;
    }
}

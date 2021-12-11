

#include "main.h"

//
// Globals
//


uint16_t c2_r_array[8];
struct AllData local_buf;
uint16_t local_val;
struct AllData log_data;

#pragma DATA_SECTION(log_data,"ramgs2");

//extern uint16_t isrfuncLoadStart;
//extern uint16_t isrfuncLoadEnd;
//extern uint16_t isrfuncRunStart;
//extern uint16_t isrfuncLoadSize;

//
// Function Prototypes
//
void initCPUTimer(uint32_t);
void configCPUTimer(uint32_t, float, float);
__interrupt void cpu_timer0_isr(void);
//__interrupt void cpu_timer1_isr(void);
//#pragma CODE_SECTION(cpu_timer0_isr,"isrfunc")
void Shared_Ram_dataWrite_c2(void);

//
// Main
//
void main(void)
{
    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Wait until shared RAM is available.
    //
    while((HWREGH(MEMCFG_BASE + MEMCFG_O_GSXMSEL) &
           (MEMCFG_GSXMSEL_MSEL_GS14 | MEMCFG_GSXMSEL_MSEL_GS15)) == 0U)
    {
    }

    Interrupt_register(INT_TIMER0, &cpu_timer0_isr);

        //
        // Configure CPU Timer 0 to a 1 second period
        //
        initCPUTimer(CPUTIMER0_BASE);
        configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 10000);

        //
        // Start CPU Timer 0
        //
        CPUTimer_startTimer(CPUTIMER0_BASE);

        //
        // Enable CPU Timer 0 interrupt
        //
        Interrupt_enable(INT_TIMER0);

        //
        // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
        //
        EINT;
        ERTM;

        local_val = 0;

   int i;

   while(1)
   {
       for( i = 0; i < 600; i++)
       {

       }
   }
}

void
initCPUTimer(uint32_t cpuTimer)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(cpuTimer, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(cpuTimer);

    //
    // Reload all counter registers with period value
    //
    CPUTimer_reloadTimerCounter(cpuTimer);
}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in microseconds. The timer is held in the
// stopped state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)(freq / 1000000 * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);
}


void Shared_Ram_dataRead_c2(void)
{

    memcpy(&local_buf, &log_data, sizeof(local_buf));
}

__interrupt void cpu_timer0_isr(void)
{
        local_val++;
        Shared_Ram_dataRead_c2();

        Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

}

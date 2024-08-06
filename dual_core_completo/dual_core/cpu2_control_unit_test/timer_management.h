#ifndef TIMER_MANAGEMENT_H_
#define TIMER_MANAGEMENT_H_


#include "F28x_Project.h"
#include "global_definitions.h"
#include "can_management.h"
#include "GPIO_management.h"
#include "utils.h"
#include "TV/Torque_Vectoring_2024_forsecontiu.h"

extern Uint32 time_elapsed;
extern Uint32 time_elapsed_ATC;

void timerSetup(void);
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);

void Shared_Ram_dataWrite_c2(void);

void traction();


#endif

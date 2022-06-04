#ifndef TIMER_MANAGEMENT_H_
#define TIMER_MANAGEMENT_H_


#include "F28x_Project.h"
#include "global_definitions.h"
#include "can_management.h"
#include "GPIO_management.h"
#include "utils.h"

extern Uint16 c2_r_w_array[256];
extern Uint16 increment;

extern Uint32 time_elapsed;

extern bool brakeWhenSlow;
extern bool brakeReg;
extern bool brakeMec;
extern bool noBrake;
extern bool implausibility_occurred;
extern float max_regen_current;


void timerSetup(void);
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);

void Shared_Ram_dataWrite_c2(void);

#endif

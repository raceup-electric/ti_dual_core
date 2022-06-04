#ifndef MAIN_H_
#define MAIN_H_


#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"
#include "GPIO_management.h"
#include <stdint.h>
#include <stdbool.h>
//#include "math.h"
#include <stdio.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "sd_card.h"
#include "display.h"
#include "LoRa.h"
#include "Telemetry.h"



//
// Globals
//
Uint16 c1_r_w_array[256];
Uint16 increment;
Uint16 deb;
Uint16 var_v = 0;

Uint16 local_buf[256];
Uint16 local_val;

//timestamp
Uint32 time_elapsed;
Uint32 local_time_elapsed;

//Sd Card
int file_counter;
char filename[20];

//Schermo
Uint16 currentPage=99;
char tmp[50];
Uint16 n_setup;
Uint16 old_setup;
Uint16 ack = 0;
Uint16 old_ack = 0;
Uint16 sel; //for debug


struct Share_struct sh;
struct Share_struct local_sh;

Uint16 Temps_shared[8];
float bms_lv_shared[8];

struct Status_Log status_log;

struct motorValues1 motorVal1_shared[4];
struct motorValues2 motorVal2_shared[4];  //  0 --> FL, 1 --> FR, 2 --> RL, 3 --> RR
struct motorSetPoints motorSetP_shared[4];

struct BMS_Log bms_log;

struct Sendyne_Log sendyne_log;

struct FanSpeed_Log fanspeed_log;

struct Imu_Log imu_log;

struct Gpio_Log gpio_log;

struct Display_command display;

char AmkStatus[4];

//#pragma DATA_SECTION(c1_r_w_array,"SHARERAMGS1");
#pragma DATA_SECTION(sh,"SHARERAMGS1");
#pragma DATA_SECTION(time_elapsed,"SHARERAMGS2");
#pragma DATA_SECTION(display,"SHARERAMGS14");


uint16_t error;
uint16_t multiplier;

//
// Function Prototypes
//
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);
void Shared_Ram_dataRead_c1(void);
void send_can_to_cpu2(void);
void cpu1_timer_setup(void);
void compute_AMKStatus(void);

#endif

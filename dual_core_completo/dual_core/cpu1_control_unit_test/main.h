#ifndef MAIN_H_
#define MAIN_H_

#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"
#include "GPIO_management.h"
#include <stdbool.h>
#include <stdio.h>
#include <struct_definition_log.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_can.h"
#include "driverlib/can.h"
#include "sd_card.h"
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

// timestamp
Uint32 time_elapsed;
Uint32 local_time_elapsed;

// Sd Card
int file_counter;
char filename[20];

struct Share_struct sh;
struct Share_struct local_sh;

struct Car_settings car_settings;

struct Macros_settings macros_settings;

char AmkStatus[4];

#pragma DATA_SECTION(macros_settings, "SHARERAMGS15");
#pragma DATA_SECTION(car_settings, "SHARERAMGS14");
#pragma DATA_SECTION(sh, "SHARERAMGS11");
#pragma DATA_SECTION(time_elapsed, "SHARERAMGS12");

Uint16 error;
Uint16 multiplier;

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

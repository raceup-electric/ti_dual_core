#ifndef GLOBAL_DEFINITIONS_H_
#define GLOBAL_DEFINITIONS_H_

//
// GPIOs
//

#define IMD_STATE 14 // PIN74     //INPUT
#define BMS_STATE 15 // PIN73     //INPUT

#define ENABLE_PUMPS 94     // PIN45
#define VENTOLA_Abil 97     // PIN46
#define AIR_1_STATE 40      // PIN50     //INPUT
#define AIR_2_STATE 41      // PIN49     //INPUT
#define RTDS 27             // PIN52
#define R2D 6               // PIN80
#define BRAKE_LIGHT_Abil 25 // PIN51
#define DEBUG_LED1 105      // PIN9
#define DEBUG_LED2 104      // PIN10

#define UART_RX 139
#define UART_TX 56

#define R2D_LED_ON 0   // LED R2D ha la logica invertita!
#define R2D_LED_OFF 1U // GPIO ALTA -> LED SPENTO       GPIO BASSA -> LED ACCESO

#define BRAKE_LIGHT_ON 1U
#define BRAKE_LIGHT_OFF 0

#define RED_BLINK 34
#define BLUE_BLINK 31

#endif

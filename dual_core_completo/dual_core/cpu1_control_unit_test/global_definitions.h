#ifndef GLOBAL_DEFINITIONS_H_
#define GLOBAL_DEFINITIONS_H_

//
// Schermo
//
#define PAGE_1 0x00
#define PAGE_2 0x01
#define PAGE_3 0x02
#define PAGE_4 0x03
#define PAGE_5 0x04
#define PAGE_6 0x05
#define PAGE_7 0x06
#define PAGE_8 0x07
#define PAGE_9 0x08
#define PAGE_10 0x09
#define PAGE_11 0x0A
#define PAGE_12 0x0B


#define MAX_PAGE_NUMBER 12


//
// GPIOs
//

#define IMD_STATE           14      //PIN74     //INPUT
#define BMS_STATE           15      //PIN73     //INPUT

#define ENABLE_PUMPS        94      //PIN45
#define VENTOLA_Abil        97      //PIN46
#define AIR_1_STATE         40      //PIN50     //INPUT
#define AIR_2_STATE         41      //PIN49     //INPUT
#define RTDS                27      //PIN52
#define SCS_FAULT           11      //PIN75
#define R2D                 6       //PIN80
#define BRAKE_LIGHT_Abil    25      //PIN51
#define SDC1_STATE          26      //PIN53     //INPUT
#define SDC2_STATE          130     //PIN57     //INPUT
#define SDC3_STATE          64      //PIN54     //INPUT
#define SDC4_STATE          131     //PIN58     //INPUT
#define SDC5_STATE          63      //PIN55     //INPUT
#define SDC6_STATE          66      //PIN59     //INPUT
#define DEBUG_LED1          105     //PIN9
#define DEBUG_LED2          104     //PIN10

#define UART_RX             139
#define UART_TX             56

#define R2D_LED_ON          0       //LED R2D ha la logica invertita!
#define R2D_LED_OFF         1U      //GPIO ALTA -> LED SPENTO       GPIO BASSA -> LED ACCESO

#define BRAKE_LIGHT_ON      1U
#define BRAKE_LIGHT_OFF     0

#define RED_BLINK           34
#define BLUE_BLINK          31


#endif

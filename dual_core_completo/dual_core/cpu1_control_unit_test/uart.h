/*
 * uart.h
 *
 *  Created on: 18 feb 2022
 *      Author: ludon
 */

#ifndef UART_H_
#define UART_H_

#include "F28x_Project.h"
#include "global_definitions.h"

//
// Function Prototypes
//
void uart_esp_setup(void);
void uart_gps_setup(void);
void scic_init(void);
void scib_init(void);
void scic_fifo_init(void);
void scib_fifo_init(void);
// void scic_xmit(int a);
void scic_xmit();
void scic_msg(char *msg);

#endif /* UART_H_ */

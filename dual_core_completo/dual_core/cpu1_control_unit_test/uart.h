/*
 * uart.h
 *
 *  Created on: 18 feb 2022
 *      Author: ludon
 */

#ifndef UART_H_
#define UART_H_

#include "F28x_Project.h"

//
// Function Prototypes
//
void uart_setup(void);
void scic_init(void);
void scic_fifo_init(void);
//void scic_xmit(int a);
void scic_xmit();
void scic_msg(char *msg);

#endif /* UART_H_ */

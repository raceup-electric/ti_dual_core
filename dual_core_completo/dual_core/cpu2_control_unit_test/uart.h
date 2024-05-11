#ifndef UART_H_
#define UART_H_

#include "F28x_Project.h"
#include "global_definitions.h"

void uart_setup(void);
bool char_available();
char read_char();

#endif /* UART_H_ */

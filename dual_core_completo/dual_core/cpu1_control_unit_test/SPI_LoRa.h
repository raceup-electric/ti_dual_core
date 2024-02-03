/*
 * SPI_LoRa.h
 *
 *  Created on: 30 apr 2022
 *      Author: Davide Frasson
 */

#ifndef SPI_LORA_H_
#define SPI_LORA_H_

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#if CPU_FRQ_200MHZ
#define SPI_BRR ((200E6 / 4) / 8E6) - 1
#endif

#if CPU_FRQ_150MHZ
#define SPI_BRR ((150E6 / 4) / 8E6) - 1
#endif

#if CPU_FRQ_120MHZ
#define SPI_BRR ((120E6 / 4) / 8E6) - 1
#endif

#define SPI_FFRX_RXFIFORESET 0x2000U // RXFIFO Reset

void InitSpi(void);
void ResetRxFIFOSpia();
void spi_fifo_init();
Uint16 spi_receive();
void spi_xmit(Uint16 a);

#endif /* SPI_LORA_H_ */

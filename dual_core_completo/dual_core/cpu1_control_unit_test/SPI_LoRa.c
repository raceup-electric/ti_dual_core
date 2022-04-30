/*
 * SPI_LoRa.c
 *
 *  Created on: 30 apr 2022
 *      Author: Davide Frasson
 */

#include "SPI_LoRa.h"


//===============================================
//
// InitSPI - This function initializes the SPI to a known state
//
//===============================================
void InitSpi(void)
{
    // Initialize SPI-A

    // Set reset low before configuration changes
    // Clock polarity (0 == rising, 1 == falling)
    // 16-bit character
    // Disable loop-back
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;
    SpiaRegs.SPICCR.bit.SPICHAR = (16-1);
    SpiaRegs.SPICCR.bit.SPILBK = 0;

    // Enable master (0 == slave, 1 == master)
    // Enable transmission (Talk)
    // Clock phase (0 == normal, 1 == delayed)
    // SPI interrupts are disabled
    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;
    SpiaRegs.SPICTL.bit.TALK = 1;
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
    SpiaRegs.SPICTL.bit.SPIINTENA = 0;

    // Set the baud rate
    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = SPI_BRR;

    // Set FREE bit
    // Halting on a breakpoint will not halt the SPI
    SpiaRegs.SPIPRI.bit.FREE = 1;

    // Release the SPI from reset
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;
}

//===============================================
//
//Reset SPIA
//
//===============================================
void ResetRxFIFOSpia(){
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 0;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1;
}

//===============================================
//
//Initialize the SPIA FIFO
//
//===============================================
void spi_fifo_init()
{
    //
    // Initialize SPI FIFO registers
    //
    SpiaRegs.SPIFFTX.all = 0xE040;
    SpiaRegs.SPIFFRX.all = 0x2021;
    SpiaRegs.SPIFFCT.all = 0x0;

    //
    // Initialize core SPI registers
    //
    InitSpi();
}

//===============================================
//
// spi_receive - Read a value from the SPI
//
//===============================================
Uint16 spi_receive(){
    while(SpiaRegs.SPIFFRX.bit.RXFFST == 0){}
    return SpiaRegs.SPIRXBUF;
}

//===============================================
//
// spi_xmit - Transmit value via SPI
//
//===============================================
void spi_xmit(Uint16 a)
{
    SpiaRegs.SPITXBUF = a;

}




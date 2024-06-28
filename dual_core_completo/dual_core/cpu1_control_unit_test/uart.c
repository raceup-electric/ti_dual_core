/*
 * uart.c
 *
 *  Created on: 18 feb 2022
 *      Author: ludon
 */
#include "uart.h"

void uart_setup()
{
    GPIO_SetupPinMux(UART_RX, GPIO_MUX_CPU1, 6); // RX
    GPIO_SetupPinOptions(UART_RX, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(UART_TX, GPIO_MUX_CPU1, 6); // TX
    GPIO_SetupPinOptions(UART_TX, GPIO_OUTPUT, GPIO_ASYNC);

    GPIO_SetupPinMux(UART_RX_GPS, GPIO_MUX_CPU1, 2); // RX
    GPIO_SetupPinOptions(UART_RX_GPS, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(UART_TX_GPS, GPIO_MUX_CPU1, 2); // TX
    GPIO_SetupPinOptions(UART_TX_GPS, GPIO_OUTPUT, GPIO_ASYNC);

    scic_fifo_init(); // Initialize the SCI FIFO
    scib_fifo_init();
    scic_init();      // Initialize SCI for
    scib_init();
}

void scic_init()
{
    //
    // Note: Clocks were turned on to the SCIC peripheral
    // in the InitSysCtrl() function
    //

    ScicRegs.SCICCR.all = 0x0007;  // 1 stop bit,  No loopback, No parity,8 char bits, async mode, idle-line protocol
    ScicRegs.SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    ScicRegs.SCICTL2.all = 0x0003;
    ScicRegs.SCICTL2.bit.TXINTENA = 0;
    ScicRegs.SCICTL2.bit.RXBKINTENA = 0;

    //baudrate 460800
    ScicRegs.SCIHBAUD.all = 0x0000;
    ScicRegs.SCILBAUD.all = 0x00D;
    ScicRegs.SCICTL1.all = 0x0023;
}

void scib_init()
{
    ScibRegs.SCICCR.all = 0x0007;
    ScibRegs.SCICTL1.all = 0x0003;
    ScibRegs.SCICTL2.all = 0x0003;
    ScibRegs.SCICTL2.bit.TXINTENA = 0;
    ScibRegs.SCICTL2.bit.RXBKINTENA = 0;

    //
    // SCIc at 9600 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.
    //

    // baudrate 9600
    ScibRegs.SCIHBAUD.all = 0x0002;
    ScibRegs.SCILBAUD.all = 0x008b;
    ScibRegs.SCICTL1.all = 0x0023;
}
//
// scia_xmit - Transmit a character from the SCI
//
void scic_xmit(int a)
{
    while (ScicRegs.SCIFFTX.bit.TXFFST != 0)
    {
    }
    ScicRegs.SCITXBUF.bit.TXDT = a;
}

void scib_xmit(int a)
{
    while (ScibRegs.SCIFFTX.bit.TXFFST != 0)
    {
    }
    ScibRegs.SCITXBUF.bit.TXDT = a;
}

//
// scia_msg - Transmit message via SCIA
//
void scic_msg(char *msg)
{
    int i;
    i = 0;
    while (msg[i] != '\0')
    {
        scic_xmit(msg[i]);
        i++;
    }

    scic_xmit('\0');
}

void scib_msg(char *msg)
{
    int i;
    i = 0;
    while (msg[i] != '\0')
    {
        scib_xmit(msg[i]);
        i++;
    }

    scib_xmit('\0');
}

//
// scia_fifo_init - Initialize the SCI FIFO
//
void scic_fifo_init()
{
    ScicRegs.SCIFFTX.all = 0xE040;
    ScicRegs.SCIFFRX.all = 0x2044;
    ScicRegs.SCIFFCT.all = 0x0;
}

void scib_fifo_init()
{
    ScibRegs.SCIFFTX.all = 0xE040;
    ScibRegs.SCIFFRX.all = 0x2044;
    ScibRegs.SCIFFCT.all = 0x0;
}

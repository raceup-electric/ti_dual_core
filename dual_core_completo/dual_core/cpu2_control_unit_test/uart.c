#include "uart.h"


#define UART_TX 14
#define UART_RX 15


void uart_setup()
{
    GPIO_SetupPinMux(UART_RX, GPIO_MUX_CPU2, 2); // RX
    GPIO_SetupPinOptions(UART_RX, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(UART_TX, GPIO_MUX_CPU2, 2); // TX
    GPIO_SetupPinOptions(UART_TX, GPIO_OUTPUT, GPIO_ASYNC);

    scib_fifo_init(); // Initialize the SCI FIFO
    scib_init();      // Initialize SCI for
}

void scib_init()
{
    //
    // Note: Clocks were turned on to the SCIC peripheral
    // in the InitSysCtrl() function
    //

    ScibRegs.SCICCR.all = 0x0007;  // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    ScibRegs.SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    ScibRegs.SCICTL2.all = 0x0003;
    ScibRegs.SCICTL2.bit.TXINTENA = 0;
    ScibRegs.SCICTL2.bit.RXBKINTENA = 0;

    //
    // SCIc at 9600 baud
    // @LSPCLK = 50 MHz (200 MHz SYSCLK) HBAUD = 0x02 and LBAUD = 0x8B.
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x01 and LBAUD = 0x86.
    //

    /* baudrate 9600
     ScicRegs.SCIHBAUD.all = 0x0002;
    ScicRegs.SCILBAUD.all = 0x008a;
     */
    // baudrate 115200
    ScibRegs.SCIHBAUD.all = 0x0000;
    ScibRegs.SCILBAUD.all = 0x0035;
    ScibRegs.SCICTL1.all = 0x0023; // Relinquish SCI from Reset
}

//
// Initialize the SCI B FIFO
//
void scib_fifo_init()
{
    ScibRegs.SCIFFTX.all = 0xE040;
    ScibRegs.SCIFFRX.all = 0x2044;
    ScibRegs.SCIFFCT.all = 0x0;
}

bool char_available(){
    return ScibRegs.SCIFFRX.bit.RXFFST != 0;
}

char read_char(){
    return (char)ScibRegs.SCIRXBUF.all; 
}

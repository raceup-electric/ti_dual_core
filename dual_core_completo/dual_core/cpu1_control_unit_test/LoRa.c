/*
 * LoRa.c
 *
 *  Created on: 11 dic 2021
 *      Author: Davide Frasson
 */

#include "LoRa.h"
#include "F28x_Project.h"
#include "SPI_LoRa.h"

// registers
#define REG_FIFO 0x00
#define REG_OP_MODE 0x01
#define REG_FRF_MSB 0x06
#define REG_FRF_MID 0x07
#define REG_FRF_LSB 0x08
#define REG_PA_CONFIG 0x09
#define REG_OCP 0x0b
#define REG_LNA 0x0c
#define REG_FIFO_ADDR_PTR 0x0d
#define REG_FIFO_TX_BASE_ADDR 0x0e
#define REG_FIFO_RX_BASE_ADDR 0x0f
#define REG_FIFO_RX_CURRENT_ADDR 0x10
#define REG_IRQ_FLAGS 0x12
#define REG_RX_NB_BYTES 0x13
#define REG_PKT_SNR_VALUE 0x19
#define REG_PKT_RSSI_VALUE 0x1a
#define REG_RSSI_VALUE 0x1b
#define REG_MODEM_CONFIG_1 0x1d
#define REG_MODEM_CONFIG_2 0x1e
#define REG_PREAMBLE_MSB 0x20
#define REG_PREAMBLE_LSB 0x21
#define REG_PAYLOAD_LENGTH 0x22
#define REG_MODEM_CONFIG_3 0x26
#define REG_FREQ_ERROR_MSB 0x28
#define REG_FREQ_ERROR_MID 0x29
#define REG_FREQ_ERROR_LSB 0x2a
#define REG_RSSI_WIDEBAND 0x2c
#define REG_DETECTION_OPTIMIZE 0x31
#define REG_INVERTIQ 0x33
#define REG_DETECTION_THRESHOLD 0x37
#define REG_SYNC_WORD 0x39
#define REG_INVERTIQ2 0x3b
#define REG_DIO_MAPPING_1 0x40
#define REG_VERSION 0x42
#define REG_PA_DAC 0x4d

// modes
#define MODE_LONG_RANGE_MODE 0x80
#define MODE_SLEEP 0x00
#define MODE_STDBY 0x01
#define MODE_TX 0x03
#define MODE_RX_CONTINUOUS 0x05
#define MODE_RX_SINGLE 0x06

// PA config
#define PA_BOOST 0x80

// IRQ masks
#define IRQ_TX_DONE_MASK 0x08
#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
#define IRQ_RX_DONE_MASK 0x40

#define RF_MID_BAND_THRESHOLD 525E6
#define RSSI_OFFSET_HF_PORT 157
#define RSSI_OFFSET_LF_PORT 164

#define MAX_PKT_LENGTH 255

uint16_t version;
uint8_t implicitHeaderFlag = 0;
uint8_t onTxDone = 0x01;
uint8_t packetIndex = 0;

// Function definitions
extern void ResetRxFIFOSpia();
extern void GPIO_WritePin(uint16_t gpioNumber, uint16_t outVal);
extern void spi_xmit(uint16_t a);
extern uint16_t spi_receive();

#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

//-------------------------------------------------------------------
//
// Method to setup the GPIO of thecommunication with the LoRa module
//
//-------------------------------------------------------------------
void GPIO_LoRa_Setup()
{
  EALLOW;

  GPIO_SetupPinMux(58, GPIO_MUX_CPU1, 15); // MOSI
  GPIO_SetupPinMux(59, GPIO_MUX_CPU1, 15);
  GPIO_SetupPinMux(60, GPIO_MUX_CPU1, 15); // SCLK
  GPIO_SetupPinMux(61, GPIO_MUX_CPU1, 15); // CS

  GPIO_SetupPinOptions(58, GPIO_OUTPUT, GPIO_ASYNC); // MOSI
  // GPIO_SetupPinOptions(59, GPIO_INPUT, GPIO_PUSHPULL);    //MISO
  GPIO_SetupPinOptions(60, GPIO_OUTPUT, GPIO_ASYNC); // SCLK
  GPIO_SetupPinOptions(61, GPIO_OUTPUT, GPIO_ASYNC); // CS

  // Reset configuration
  GPIO_SetupPinMux(LORA_DEFAULT_RESET_PIN, GPIO_MUX_CPU1, 0);
  GPIO_SetupPinOptions(LORA_DEFAULT_RESET_PIN, GPIO_OUTPUT, GPIO_PUSHPULL);
  GPIO_WritePin(LORA_DEFAULT_RESET_PIN, 1);

  // DIO0 configuration
  GPIO_SetupPinMux(LORA_DEFAULT_DIO0_PIN, GPIO_MUX_CPU1, 0);
  GPIO_SetupPinOptions(LORA_DEFAULT_DIO0_PIN, GPIO_INPUT, GPIO_ASYNC);

  // Missing interrupt attachment to detect TxDone

  // Starting the FIFO
  spi_fifo_init();
}

//-------------------------------------------------------------------
//
// Method to start the LoRa communication and setting-up the
// SX1276 chip of the LoRa transmitter
//
//-------------------------------------------------------------------
int LoRa_begin(long frequency)
{

  //
  // Set direction mode of the chip select(SS) pin
  //
  // GPIO_setDirectionMode(LORA_DEFAULT_SS_PIN, GPIO_DIR_MODE_OUT);
  GPIO_WritePin(LORA_DEFAULT_SS_PIN, 1);

  //
  // Set direction mode of the Reset pin
  //
  if (LORA_DEFAULT_RESET_PIN != -1)
  {
    // GPIO_setDirectionMode(LORA_DEFAULT_RESET_PIN, GPIO_DIR_MODE_OUT);

    GPIO_WritePin(LORA_DEFAULT_RESET_PIN, 0);
    DELAY_US(10000);
    GPIO_WritePin(LORA_DEFAULT_RESET_PIN, 1);
    DELAY_US(10000);
  }

  //
  // Check version of the LoRa
  //
  version = readRegister(REG_VERSION);
  if ((version & 0x00FF) != 0x0012)
  {
    return 0;
  }

  //
  // Put the LoRa in sleep mode
  //
  sleep();

  // Set the frequency
  setFrequency(frequency);

  // write base address
  writeRegister(REG_FIFO_TX_BASE_ADDR, 0);
  writeRegister(REG_FIFO_RX_BASE_ADDR, 0);

  // set LNA boost
  writeRegister(REG_LNA, readRegister(REG_LNA) | 0x03);

  // set auto AGC
  writeRegister(REG_MODEM_CONFIG_3, 0x04);

  // set output power to 20 dBm
  setTxPower(LORA_TX_POWER, PA_OUTPUT_RFO_PIN);
  setSignalBandwidth(LORA_SIGNAL_BANDWIDTH);
  setSpreadingFactor(LORA_SF);
  setCodingRate(LORA_CODING_RATE);
  enableCrc();

  // put in standby mode
  idle();

  return 1;
}

//-------------------------------------------------------------------
//
// Function that actually end the LoRa communication, this is accomplished by
// putting the chip in sleep mode
//
//-------------------------------------------------------------------
void LoRa_end()
{
  //
  // Simply the SX1276 is put in sleep mode
  //
  sleep();
}

//-------------------------------------------------------------------
//
// Function to declare the start of a packet, expliciting the current header mode
// of the LoRa module
//
//-------------------------------------------------------------------
int beginPacket(int implicitHeader)
{
  // Check if the module is transmitting
  if (isTransmitting())
  {
    return 0;
  }
  // Put the module in idle mode
  idle();

  // Sets the current packet mode
  if (implicitHeader)
  {
    implicitHeaderMode();
  }
  else
  {
    explicitHeaderMode();
  }

  // reset FIFO and payload length
  writeRegister(REG_FIFO_ADDR_PTR, 0);
  writeRegister(REG_PAYLOAD_LENGTH, 0);

  return 1;
}

//-------------------------------------------------------------------
//
// Function to declare the end of a packet
//
//-------------------------------------------------------------------
int endPacket(bool async)
{
  if ((async) && (onTxDone))
  {
    writeRegister(REG_DIO_MAPPING_1, 0x40); // DIO0 => TXDONE
  }

  // Put in TX mode
  writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_TX);

  if (!async)
  {
    // wait for TX done
    while ((readRegister(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK) == 0)
    {
    }
    // clear IRQ's
    writeRegister(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);
  }

  return 1;
}
//-------------------------------------------------------------------
//
// Function to parse the length of a packet and it's availability
//
//-------------------------------------------------------------------
int parsePacket(int size)
{
  int packetLength = 0;
  int irqFlags = readRegister(REG_IRQ_FLAGS);

  if (size > 0)
  {
    implicitHeaderMode();

    writeRegister(REG_PAYLOAD_LENGTH, size & 0xff);
  }
  else
  {
    explicitHeaderMode();
  }

  // clear IRQ's
  writeRegister(REG_IRQ_FLAGS, irqFlags);

  if ((irqFlags & IRQ_RX_DONE_MASK) && (irqFlags & IRQ_PAYLOAD_CRC_ERROR_MASK) == 0)
  {
    // received a packet
    packetIndex = 0;

    // read packet length
    if (implicitHeaderFlag)
    {
      packetLength = readRegister(REG_PAYLOAD_LENGTH);
    }
    else
    {
      packetLength = readRegister(REG_RX_NB_BYTES);
    }

    // set FIFO address to current RX address
    writeRegister(REG_FIFO_ADDR_PTR, readRegister(REG_FIFO_RX_CURRENT_ADDR));

    // put in standby mode
    idle();
  }
  else if (readRegister(REG_OP_MODE) != (MODE_LONG_RANGE_MODE | MODE_RX_SINGLE))
  {
    // not currently in RX mode

    // reset FIFO address
    writeRegister(REG_FIFO_ADDR_PTR, 0);

    // put in single RX mode
    writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_SINGLE);
  }

  return packetLength;
}

//-------------------------------------------------------------------
//
// Function to checks if the module is currently transmitting
//
//-------------------------------------------------------------------
bool isTransmitting()
{
  if ((readRegister(REG_OP_MODE) & MODE_TX) == MODE_TX)
  {
    return true;
  }

  if (readRegister(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK)
  {
    // clear IRQ's
    writeRegister(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);
  }

  return false;
}

//-------------------------------------------------------------------
//
// Function to set to explicitHeaderMode
//
//-------------------------------------------------------------------
void explicitHeaderMode()
{
  implicitHeaderFlag = 0;

  writeRegister(REG_MODEM_CONFIG_1, readRegister(REG_MODEM_CONFIG_1) & 0xfe);
}

//-------------------------------------------------------------------
//
// Function to set to implicitHeaderMode
//
//-------------------------------------------------------------------
void implicitHeaderMode()
{
  implicitHeaderFlag = 1;

  writeRegister(REG_MODEM_CONFIG_1, readRegister(REG_MODEM_CONFIG_1) | 0x01);
}

//-------------------------------------------------------------------
//
// Function that put the LoRa in IDLE mode
//
//-------------------------------------------------------------------
void idle()
{
  //
  // Write the RegOpMode register (describes the operation mode of the LoRa)
  // and set it in LongRange mode (activating the seventh MSB, ae 0x80 = 1000 0000)
  // setting also the stand-by mode by setting the LSB to 001(0x80 | 0x01 = 1000 0001).
  // Mode bits are 2downto0
  //
  writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_STDBY);
}

//-------------------------------------------------------------------
//
// Function that put the LoRa in SLEEP mode
//
//-------------------------------------------------------------------
void sleep()
{
  //
  // Write the RegOpMode register (describes the operation mode of the LoRa)
  // and set it in LongRange mode (activating the seventh MSB, ae 0x80 = 1000 0000)
  // setting also the sleep mode by setting the LSB to 000(0x80 | 0x01 = 1000 0000)
  // Mode bits are 2downto0
  //
  writeRegister(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_SLEEP);
}

//-------------------------------------------------------------------
//
// Function to set the frequency of the LoRa
//
//-------------------------------------------------------------------
void setFrequency(long frequency)
{

  // Resolution frequency calculated by the formula provided in the datasheet,
  // will be uploaded in three different buffers.
  uint64_t frf = ((uint64_t)frequency << 19) / 32000000;

  writeRegister(REG_FRF_MSB, (uint8_t)(frf >> 16)); // first 8 bits
  writeRegister(REG_FRF_MID, (uint8_t)(frf >> 8));  // mid 8 bits
  writeRegister(REG_FRF_LSB, (uint8_t)(frf >> 0));  // last 8 bits
}

//-------------------------------------------------------------------
//
// Function that sets the trasmission power of the LoRa
//
//-------------------------------------------------------------------
void setTxPower(int level, int outputPin)
{
  if (PA_OUTPUT_RFO_PIN == outputPin)
  {
    // RFO
    if (level < 0)
    {
      level = 0;
    }
    else if (level > 14)
    {
      level = 14;
    }

    writeRegister(REG_PA_CONFIG, 0x70 | level);
  }
  else
  {
    // PA BOOST
    if (level > 17)
    {
      if (level > 20)
      {
        level = 20;
      }

      // subtract 3 from level, so 18 - 20 maps to 15 - 17
      level -= 3;

      // High Power +20 dBm Operation (Semtech SX1276/77/78/79 5.4.3.)
      writeRegister(REG_PA_DAC, 0x87);
      setOCP(140);
    }
    else
    {
      if (level < 2)
      {
        level = 2;
      }
      // Default value PA_HF/LF or +17dBm
      writeRegister(REG_PA_DAC, 0x84);
      setOCP(100);
    }

    writeRegister(REG_PA_CONFIG, PA_BOOST | (level - 2));
  }
}

//-------------------------------------------------------------------
//
// Function to set the spreading factor of the LoRa module
//
//-------------------------------------------------------------------
void setSpreadingFactor(int sf)
{
  if (sf < 6)
  {
    sf = 6;
  }
  else if (sf > 12)
  {
    sf = 12;
  }

  if (sf == 6)
  {
    writeRegister(REG_DETECTION_OPTIMIZE, 0xc5);
    writeRegister(REG_DETECTION_THRESHOLD, 0x0c);
  }
  else
  {
    writeRegister(REG_DETECTION_OPTIMIZE, 0xc3);
    writeRegister(REG_DETECTION_THRESHOLD, 0x0a);
  }

  writeRegister(REG_MODEM_CONFIG_2, (readRegister(REG_MODEM_CONFIG_2) & 0x0f) | ((sf << 4) & 0xf0));
  setLdoFlag();
}

//-------------------------------------------------------------------
//
// Function to set the spreading factor of the LoRa module
//
//-------------------------------------------------------------------
uint8_t getSpreadingFactor()
{
  return readRegister(REG_MODEM_CONFIG_2) >> 4;
}

//-------------------------------------------------------------------
//
// Function to set the bandwidth of the LoRa module
//
//-------------------------------------------------------------------
void setSignalBandwidth(long sbw)
{
  int bw;

  if (sbw <= 7.8E3)
  {
    bw = 0;
  }
  else if (sbw <= 10.4E3)
  {
    bw = 1;
  }
  else if (sbw <= 15.6E3)
  {
    bw = 2;
  }
  else if (sbw <= 20.8E3)
  {
    bw = 3;
  }
  else if (sbw <= 31.25E3)
  {
    bw = 4;
  }
  else if (sbw <= 41.7E3)
  {
    bw = 5;
  }
  else if (sbw <= 62.5E3)
  {
    bw = 6;
  }
  else if (sbw <= 125E3)
  {
    bw = 7;
  }
  else if (sbw <= 250E3)
  {
    bw = 8;
  }
  else /*if (sbw <= 250E3)*/
  {
    bw = 9;
  }

  writeRegister(REG_MODEM_CONFIG_1, (readRegister(REG_MODEM_CONFIG_1) & 0x0f) | (bw << 4));
  setLdoFlag();
}
//-------------------------------------------------------------------
//
// Function to get the bandwidth of the LoRa module
//
//-------------------------------------------------------------------
long getSignalBandwidth()
{
  uint8_t bw = 0x000f & (readRegister(REG_MODEM_CONFIG_1) >> 4);

  switch (bw)
  {
  case 0:
    return 7.8E3;
  case 1:
    return 10.4E3;
  case 2:
    return 15.6E3;
  case 3:
    return 20.8E3;
  case 4:
    return 31.25E3;
  case 5:
    return 41.7E3;
  case 6:
    return 62.5E3;
  case 7:
    return 125E3;
  case 8:
    return 250E3;
  case 9:
    return 500E3;
  }

  return -1;
}
//-------------------------------------------------------------------
//
// Function to set the coding rate of the LoRa module
//
//-------------------------------------------------------------------
void setCodingRate(int denominator)
{
  if (denominator < 5)
  {
    denominator = 5;
  }
  else if (denominator > 8)
  {
    denominator = 8;
  }

  int cr = denominator - 4;

  writeRegister(REG_MODEM_CONFIG_1, (readRegister(REG_MODEM_CONFIG_1) & 0xf1) | (cr << 1));
}

//-------------------------------------------------------------------
//
// Function to set the Low Datarate Optimization flag of the LoRa module
// in case that the symbol length exceeds 16ms. (Ts calculated in the MatLab script)
//
//-------------------------------------------------------------------
void setLdoFlag()
{
  // Section 4.1.1.5
  long symbolDuration = 1000 / (getSignalBandwidth() / (1L << getSpreadingFactor()));

  // Section 4.1.1.6
  bool ldoOn = symbolDuration > 16;

  uint8_t config3 = readRegister(REG_MODEM_CONFIG_3);
  bitWrite(config3, 3, ldoOn);
  writeRegister(REG_MODEM_CONFIG_3, config3);
}

//-------------------------------------------------------------------
//
// Function to set the preamble length  of the packet in explicit
// header mode
//
//-------------------------------------------------------------------
void setPreambleLength(long length)
{
  writeRegister(REG_PREAMBLE_MSB, (uint8_t)(length >> 8));
  writeRegister(REG_PREAMBLE_LSB, (uint8_t)(length >> 0));
}

//-------------------------------------------------------------------
//
// Checks LoRa availability to reception
//
//-------------------------------------------------------------------

int available()
{
  return (readRegister(REG_RX_NB_BYTES) - packetIndex);
}
//-------------------------------------------------------------------
//
// Read a byte from the LoRa FIFO
//
//-------------------------------------------------------------------
int read()
{
  if (!available())
  {
    return -1;
  }

  packetIndex++;

  return readRegister(REG_FIFO);
}

//-------------------------------------------------------------------
//
// Function to set the OverCurrent Protection
//
//-------------------------------------------------------------------
void setOCP(uint8_t mA)
{
  uint8_t ocpTrim = 27;

  if (mA <= 120)
  {
    ocpTrim = (mA - 45) / 5;
  }
  else if (mA <= 240)
  {
    ocpTrim = (mA + 30) / 10;
  }

  writeRegister(REG_OCP, 0x20 | (0x1F & ocpTrim));
}

//-------------------------------------------------------------------
//
// Function that reads a register of the LoRa
//
//-------------------------------------------------------------------
uint8_t readRegister(uint8_t address)
{

  //
  // MASKING for the address
  // First bit is wnr(write or read mode) where 0=read and 1=write
  // Then the next 7 bits are the actual address of the register (MSB first)
  //
  address &= 0x7f;

  ResetRxFIFOSpia();

  // Turn down the chip select to start the communication
  GPIO_WritePin(LORA_DEFAULT_SS_PIN, 0);

  // Should put the address in the SPIA transmitter buffer and send it to the LoRa
  uint16_t correct_address = (address << 8);
  spi_xmit(correct_address);

  // End the SPI transmission with the LoRa by highering the NSS pin

  // Should wait for the data to be in the receiver buffer and then read it
  uint16_t response = spi_receive();
  GPIO_WritePin(LORA_DEFAULT_SS_PIN, 1);
  return response;
}

//-------------------------------------------------------------------
//
// Function that writes a register of the LoRa
//
//-------------------------------------------------------------------
void writeRegister(uint8_t address, uint8_t value)
{

  //
  // MASKING for the address
  // First bit is wnr(write or read mode) where 0=read and 1=write
  // Then the next 7 bits are the actual address of the register (MSB first)
  //
  address |= 0x80;
  uint16_t addr_val = (address << 8) | (0x00FF & value);

  // Turn down the chip select to start the communication
  GPIO_WritePin(LORA_DEFAULT_SS_PIN, 0);

  // Puts the data in transmission buffer and sends it to the LoRa
  spi_xmit(addr_val);
  uint16_t response = spi_receive();
  // End the SPI transmission with the LoRa by highering the NSS pin
  GPIO_WritePin(LORA_DEFAULT_SS_PIN, 1);
}

uint16_t LoRa_write(char byte)
{
  return LoRa_writeBuffer(&byte, sizeof(byte));
}

uint16_t LoRa_writeBuffer(uint8_t *buffer, uint16_t size)
{
  uint8_t currentLength = (0x00FF) & readRegister(REG_PAYLOAD_LENGTH);

  // check size
  if ((currentLength + size) > MAX_PKT_LENGTH)
  {
    size = MAX_PKT_LENGTH - currentLength;
  }

  // write data
  int i;
  for (i = 0; i < size; i++)
  {
    writeRegister(REG_FIFO, buffer[i]);
  }

  // update length
  writeRegister(REG_PAYLOAD_LENGTH, currentLength + size);

  return size;
}

//-------------------------------------------------------------------
//
// Enable CRC on packet to count errors
//
//-------------------------------------------------------------------
void enableCrc()
{
  writeRegister(REG_MODEM_CONFIG_2, readRegister(REG_MODEM_CONFIG_2) | 0x04);
}

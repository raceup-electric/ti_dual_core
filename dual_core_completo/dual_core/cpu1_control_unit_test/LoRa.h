/*
 * LoRa.h
 *
 *  Created on: 11 dic 2021
 *      Author: Davide Frasson
 */

#ifndef LORA_H_
#define LORA_H_

#include "stdint.h"
#include "stdbool.h"

typedef uint16_t uint8_t;

//
// Pinout of the LoRa and the SPI that is used
#define LORA_DEFAULT_SPI SPIA_BASE
#define LORA_DEFAULT_SPI_FREQUENCY 868E6
#define LORA_DEFAULT_SS_PIN 61
#define LORA_DEFAULT_RESET_PIN 19
#define LORA_DEFAULT_DIO0_PIN 111
#define PA_OUTPUT_RFO_PIN 0
#define PA_OUTPUT_PA_BOOST_PIN 1

// LoRa parameters
#define LORA_SIGNAL_BANDWIDTH 500E3
#define LORA_CODING_RATE 5
#define LORA_SF 6
#define LORA_TX_POWER 14
#define LORA_IMPLICIT_HEADER 1
#define LORA_EXPLICIT_HEADER 0
#define LORA_IMPLICIT_SIZE 5

void GPIO_LoRa_Setup();

int LoRa_begin(long frequency);
void LoRa_end();

// Funzioni di inizializzazione dei pacchetti
int beginPacket(int implicitHeader);
int endPacket(bool async);

int parsePacket(int size);

void idle();
void sleep();

bool isTransmitting();

void explicitHeaderMode();
void implicitHeaderMode();

void setFrequency(long frequency);
void setTxPower(int level, int outputPin);

void setSpreadingFactor(int sf);
void setSignalBandwidth(long sbw);
void setCodingRate(int denominator);
void setPreambleLength(long length);
void setLdoFlag();

void enableCrc();

long getSignalBandwidth();
uint8_t getSpredingFactor();

int available();
int read();

void setOCP(uint8_t mA); // Over Current Protection control

uint8_t readRegister(uint8_t address);
void writeRegister(uint8_t address, uint8_t value);

uint16_t LoRa_write(char byte);
uint16_t LoRa_writeBuffer(uint8_t *buffer, uint16_t size);

#endif /* LORA_H_ */

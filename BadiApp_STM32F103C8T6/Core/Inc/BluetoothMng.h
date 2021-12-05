/*
 * BluetoothMng.h
 *
 *  Created on: October 17, 2021
 *      Author: BadiBoard
 */
 
#ifndef BLUETOOTH_MNG_H_
#define BLUETOOTH_MNG_H_

#define RPM_SYMBOL          "R"
#define LAP_SYMBOL          "L"
#define LAPFINISHED_SYMBOL  "F"
#define TEMP_SYMBOL         "T"
#define PROBEBROKE_SYMBOL   "B"
#define HIGHTEMP_SYMBOL     "H"
#define W_FIRMWARE_VERSION    "V"

#define RXSIZE              20

#define BOOTLOADER_WRITE    "BOOT"

#define R_FIRMWARE_VERSION  "FWV"

#define AT_CONNECTED        "OK+CONN"
#define AT_NOT_CONNECTED    "OK+LOST"

typedef enum
{
    Lost,
	Connect
} BluetoothStatus;

typedef enum
{
    None,
	LoadNewApp
} BluetoothAction;

#include "main.h"
BluetoothStatus bluetoothStatus;

//RX
uint8_t rxBuffer[RXSIZE];
//TX
char txBuffer[100];
uint16_t sizeTxBuffer;
char _writeFWVersion;

//Initialization of all variables
void initBluetoothCommunication(UART_HandleTypeDef *huart);

//Append new data
void appendData(char *options, uint32_t value);

//Print all pending data
HAL_StatusTypeDef printData(UART_HandleTypeDef *huart);

//Read the incoming data
BluetoothAction readData(UART_HandleTypeDef *huart, uint16_t Size);

#endif /* BLUETOOTH_MNG_H_ */

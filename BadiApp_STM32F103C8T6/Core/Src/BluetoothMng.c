/*
 * BluetoothMng.c
 *
 *  Created on: October 17, 2021
 *      Author: BadiBoard
 */

#include "BluetoothMng.h"

//Initialization of all variables
void initBluetoothCommunication(UART_HandleTypeDef *huart){
	//Initialization of DMA
	HAL_UARTEx_ReceiveToIdle_DMA (huart, rxBuffer, RXSIZE);
	bluetoothStatus = Connect;
	sizeTxBuffer = 0;

	_writeFWVersion = 0;
	//TODO: Increase boudrate and set name
}

//Append new data
void appendData(char *options, uint32_t value){
	if(bluetoothStatus==Connect){
		sizeTxBuffer += sprintf(txBuffer + sizeTxBuffer, options, value);
	} else {
		sizeTxBuffer  = 0;
		txBuffer[100] = 0;
	}
}

//Print all pending data
HAL_StatusTypeDef printData(UART_HandleTypeDef *huart) {
	HAL_StatusTypeDef trasmission = HAL_OK;
	//Add FW version to packet
	if(_writeFWVersion == 1){
		sizeTxBuffer += sprintf(txBuffer + sizeTxBuffer, VERISON W_FIRMWARE_VERSION); //UP to 10 Characters
		_writeFWVersion = 0;
	}
	if(sizeTxBuffer > 0 && bluetoothStatus==Connect){
		trasmission = HAL_UART_Transmit_DMA(huart, (uint8_t*)txBuffer, sizeTxBuffer);
		if(trasmission == HAL_OK){
			sizeTxBuffer  = 0;
			txBuffer[100] = 0;
		}
	}
	return(trasmission);
}

//Read the incoming data
BluetoothAction readData(UART_HandleTypeDef *huart, uint16_t Size) {
	if(huart->Instance==USART2) {
		//Jump to Bootloader
		if(Size == 4 &&
		   (char)rxBuffer[0] == BOOTLOADER_WRITE[0] &&
		   (char)rxBuffer[1] == BOOTLOADER_WRITE[1] &&
		   (char)rxBuffer[2] == BOOTLOADER_WRITE[2] &&
		   (char)rxBuffer[3] == BOOTLOADER_WRITE[3]) {
			HAL_UARTEx_ReceiveToIdle_DMA(huart, rxBuffer, RXSIZE);
			return(LoadNewApp);
		}
		//Get FW version
		if(Size == 3 &&
		   (char)rxBuffer[0] == R_FIRMWARE_VERSION[0] &&
		   (char)rxBuffer[1] == R_FIRMWARE_VERSION[1] &&
		   (char)rxBuffer[2] == R_FIRMWARE_VERSION[2]){
			HAL_UARTEx_ReceiveToIdle_DMA(huart, rxBuffer, RXSIZE);
			_writeFWVersion = 1;
			return(None);
		}
		//Stop communication
		if(Size == 9 && //Position 7 and 8 are /r and /n
		   (char)rxBuffer[0] == AT_NOT_CONNECTED[0] &&
		   (char)rxBuffer[1] == AT_NOT_CONNECTED[1] &&
		   (char)rxBuffer[2] == AT_NOT_CONNECTED[2] &&
		   (char)rxBuffer[3] == AT_NOT_CONNECTED[3] &&
		   (char)rxBuffer[4] == AT_NOT_CONNECTED[4] &&
		   (char)rxBuffer[5] == AT_NOT_CONNECTED[5] &&
		   (char)rxBuffer[6] == AT_NOT_CONNECTED[6]) {
			bluetoothStatus = Lost;
			HAL_UARTEx_ReceiveToIdle_DMA(huart, rxBuffer, RXSIZE);
			return(None);
		}
		//Start communication
		//WARNING: "AT_CONNECTED" must be at the and of searching procedure
		if(Size == 9 && //Position 7 and 8 are /r and /n
		   (char)rxBuffer[0] == AT_CONNECTED[0] &&
		   (char)rxBuffer[1] == AT_CONNECTED[1] &&
		   (char)rxBuffer[2] == AT_CONNECTED[2] &&
		   (char)rxBuffer[3] == AT_CONNECTED[3] &&
		   (char)rxBuffer[4] == AT_CONNECTED[4] &&
		   (char)rxBuffer[5] == AT_CONNECTED[5] &&
		   (char)rxBuffer[6] == AT_CONNECTED[6]) {
			bluetoothStatus = Connect;
			_writeFWVersion = 1;
		}
		HAL_UARTEx_ReceiveToIdle_DMA(huart, rxBuffer, RXSIZE);
		return(None);
	}
	return(None);
}

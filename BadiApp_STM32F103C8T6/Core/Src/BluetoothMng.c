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
	HAL_UART_Receive_DMA (huart, rxBuffer, RXSIZE);
	bluetoothStatus = Connect;
	sizeTxBuffer = 0;
	//TODO: Increase boudrate and set name
}

//Append new data
void appendData(char *options, uint32_t value){
	if(bluetoothStatus==Connect){
		sizeTxBuffer += sprintf(txBuffer + sizeTxBuffer, options, value);
	}
}

//Print all pending data
HAL_StatusTypeDef printData(UART_HandleTypeDef *huart) {
	HAL_StatusTypeDef trasmission = HAL_OK;
	if(sizeTxBuffer > 0 && bluetoothStatus==Connect){
		trasmission = HAL_UART_Transmit_DMA(huart, (uint8_t *)txBuffer, sizeTxBuffer);
		if(trasmission == HAL_OK){
			sizeTxBuffer  = 0;
			txBuffer[100] = 0;
		}
	}
	return(trasmission);
}

//Read the incoming data
BluetoothAction readData(UART_HandleTypeDef *huart){
	if(huart->Instance==USART2){
		if(strstr((char *)rxBuffer, BOOTLOADER_WRITE) != NULL){
			HAL_UART_Receive_DMA(huart, rxBuffer, RXSIZE);
			return(LoadNewApp);
			//TODO: reboot mode
		}
		//Stop communication
		if(strstr((char *)rxBuffer, AT_NOT_CONNECTED) != NULL){
			bluetoothStatus = Lost;
			HAL_UART_Receive_DMA(huart, rxBuffer, RXSIZE);
			return(None);
		}
		//Start communication
		if(strstr((char *)rxBuffer, AT_CONNECTED) != NULL){
			bluetoothStatus = Connect;
			HAL_UART_Receive_DMA(huart, rxBuffer, RXSIZE);
			return(None);
		}

		HAL_UART_Receive_DMA(huart, rxBuffer, RXSIZE);
		return(None);
	}
	return(None);
}

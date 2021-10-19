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
	HAL_UART_Receive_DMA (huart, UART2_rxBuffer, 4);
	bluetoothStatus = Connect;
	sizeBuffBT = 0;
	//TODO: Increase boudrate and set name
}

//Append new data
void appendData(char *options, uint32_t value){
	if(bluetoothStatus==Connect){
		sizeBuffBT += sprintf(txtBufBT + sizeBuffBT, options, value);
	}
}

//Print all pending data
HAL_StatusTypeDef printData(UART_HandleTypeDef *huart) {
	HAL_StatusTypeDef trasmission = HAL_OK;
	if(sizeBuffBT > 0 && bluetoothStatus==Connect){
		trasmission = HAL_UART_Transmit_DMA(huart, (uint8_t *)txtBufBT, sizeBuffBT);
		if(trasmission == HAL_OK){
			sizeBuffBT    = 0;
			txtBufBT[100] = 0;
		}
	}
	return(trasmission);
}

//Read the incoming data
BluetoothAction readData(UART_HandleTypeDef *huart){
	if(huart->Instance==USART2){
		if(UART2_rxBuffer[0]==BOOTLOADER_WRITE_B &&
		   UART2_rxBuffer[1]==BOOTLOADER_WRITE_O &&
		   UART2_rxBuffer[2]==BOOTLOADER_WRITE_O &&
		   UART2_rxBuffer[3]==BOOTLOADER_WRITE_T){

		}
		HAL_UART_Receive_DMA(huart, UART2_rxBuffer, 4);
	}
}

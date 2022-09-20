/*
 * MemoryMng.c
 *
 *  Created on: September 16, 2022
 *      Author: BadiBoard
 */

#include "MemoryMng.h"

char MemoryPage[PAGE_SIZE];
uint16_t actualSizeMemoryPage;

uint32_t previousMillis_LogUpdate;

//Initialization of all variables
void initMemory(){
	previousMillis_LogUpdate = HAL_GetTick();

	memset(MemoryPage, 0, PAGE_SIZE);
	actualSizeMemoryPage = 0;
}

void _writeMemory(UART_HandleTypeDef *huart){
	HAL_UART_Transmit_DMA(huart, (uint8_t*)MemoryPage, PAGE_SIZE);
}

//Print all pending data
HAL_StatusTypeDef updateLog(char *options, uint32_t value, uint8_t forceWrite) {
	char dataToWrite [strlen(options) + 10]; // 10 -> maximum number of characters in a uint32_t variable
	uint16_t lenData = sprintf(dataToWrite, options, value);
	uint16_t startingPoint = 0;
	uint16_t lenToWrite = 0;

	do {
		startingPoint += lenToWrite;
		if(PAGE_SIZE - actualSizeMemoryPage < lenData - startingPoint){
			lenToWrite = PAGE_SIZE - actualSizeMemoryPage;
		} else {
			lenToWrite = lenData - startingPoint;
		}

		//while(huart->gState == HAL_UART_STATE_BUSY_TX){} // Wait end of transmission before change MemoryPage array

		memcpy(MemoryPage + actualSizeMemoryPage, dataToWrite + startingPoint, lenToWrite);
		actualSizeMemoryPage += lenToWrite;

		if (actualSizeMemoryPage > PAGE_SIZE){
			memcpy(MemoryPage, "ERR", 3);
			return HAL_ERROR;
		}

		if(PAGE_SIZE == actualSizeMemoryPage || forceWrite){
			if(forceWrite){
				memset(MemoryPage + actualSizeMemoryPage, 0, PAGE_SIZE - actualSizeMemoryPage);
			}
			//_writeMemory(huart);
			actualSizeMemoryPage = 0;
		}
	} while(startingPoint + lenToWrite < lenData);
	return HAL_OK;
}

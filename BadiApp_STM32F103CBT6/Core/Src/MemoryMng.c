/*
 * MemoryMng.c
 *
 *  Created on: September 16, 2022
 *      Author: BadiBoard
 */

#include "MemoryMng.h"

uint8_t MemoryPage[2][1 + 3 + PAGE_SIZE];
//Bit 8: Initialization pageToWrite
//Bit 4: Write enable (1 -> enable, 0 -> not enable)
//Bit 3: Memory status (1 -> busy, 0 -> ready)
//Bit 2: Buffer[not(Bit1)] is ready to be written
//Bit 1: Buffer used (0 -> MemoryPage[0], 1 -> MemoryPage[1])
uint8_t MemoryStatus = 0;

uint16_t actualSizeMemoryPage;

uint16_t currentPageWrited;

uint32_t previousMillis_LogUpdate;

SPI_HandleTypeDef *Memoryhspi;

GPIO_PinState NSSPinStatus;


//SPI NSS Change status
void _NSSChangeStatus(GPIO_PinState NewState){
	HAL_GPIO_WritePin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin, NewState);
	NSSPinStatus = NewState;
}

//Page to byte: convert page to byte and write it into 3 position of array
void _pageToByte(uint16_t *pageToWrite,uint8_t *commandToWrite){
	uint32_t readPage = *pageToWrite * PAGE_SIZE;
	memcpy(commandToWrite, &readPage, 3); //Bit 1 of MemoryStatus
}

//Read header memory
uint8_t _readHeaderPage(uint16_t pageToRead){
	uint8_t commandToWrite[5] = {FLASH_DATA_READE};
	uint8_t dataRead[5];

	_pageToByte(&pageToRead, commandToWrite +1);//First position is for command

	//read data
	_NSSChangeStatus(GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(Memoryhspi, commandToWrite, dataRead, 5, WAIT_TIME * 5);
	_NSSChangeStatus(GPIO_PIN_SET);

	return dataRead[4];
}

//Initialization of pageToWrite (The first page to be written)
uint16_t _initPageToWrite(){
	uint16_t pageToWrite;
	MemoryStatus = MemoryStatus | 128; // Set Bit 8 = 1

	//Search the first free position
	pageToWrite = 0;
	do{
		if(_readHeaderPage(pageToWrite) == 0xFF)
			break;

		if(pageToWrite == NUMBER_OF_PAGES){
			pageToWrite = 0;
		} else {
			pageToWrite ++;
		}
	}while(pageToWrite != 0); //Exit if header of the page is == 0 or all headers are != 0

	return pageToWrite;
}

//Initialization of all variables
void initMemory(SPI_HandleTypeDef *hspi){
	_NSSChangeStatus(GPIO_PIN_SET);

	previousMillis_LogUpdate = HAL_GetTick();

	Memoryhspi = hspi;

	MemoryPage[0][0] = FLASH_WRITE_PAGE;
	MemoryPage[1][0] = FLASH_WRITE_PAGE;

	memset(MemoryPage[0] + 1, 0, PAGE_SIZE + 3);
	memset(MemoryPage[1] + 1, 0, PAGE_SIZE + 3);

	actualSizeMemoryPage = 0;
	currentPageWrited = _initPageToWrite();
	MemoryStatus = 0; // Init MemoryStatus
}

//Write enable (06h)
void _writeEnable(){
	uint8_t commandToWrite = FLASH_WRITE_EN;

	_NSSChangeStatus(GPIO_PIN_RESET);
	HAL_SPI_Transmit(Memoryhspi, &commandToWrite, 1, WAIT_TIME);
	_NSSChangeStatus(GPIO_PIN_SET);
}

//Erase sector memory
void _eraseSector(uint16_t *pageToErase){
	uint8_t commandToWrite[1 + 3] = {FLASH_SECTOR_ERASE};
	_pageToByte(pageToErase, commandToWrite + 1);//First position is for command

	_writeEnable();

	_NSSChangeStatus(GPIO_PIN_RESET);
	HAL_SPI_Transmit(Memoryhspi, commandToWrite, 3, WAIT_TIME * 3);
	_NSSChangeStatus(GPIO_PIN_SET);
}

//Read status register (ready and write enable)
void _status(){
	uint8_t commandToWrite[1 + 1] = {FLASH_READ_STATUS1};
	uint8_t dataRead[2];

	_NSSChangeStatus(GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(Memoryhspi, commandToWrite, dataRead, 2, WAIT_TIME * 2);
	_NSSChangeStatus(GPIO_PIN_SET);

	MemoryStatus = (MemoryStatus & 243) | ((dataRead[1] & 3) << 2);//Ready to write
}

//Check if memory is waiting to be written
//flesh data into memory
void flashPage(){
	if(NSSPinStatus == GPIO_PIN_SET){
		_writeEnable();
		_status();

#ifndef disableDataLogWrite
		if(MemoryStatus & 2 && !(MemoryStatus & 4) && MemoryStatus & 8){ //Ready and write enable
			_NSSChangeStatus(GPIO_PIN_RESET);
			HAL_SPI_Transmit_DMA(Memoryhspi, MemoryPage[(MemoryStatus & 1) ^ 1], 1 + 3 + PAGE_SIZE);
		}
#else
		MemoryMNG_Callback();
#endif

	}
}

//Write memory
void _writeMemory(){
	//Wait until write procedure is finished
	//It is very important to start writre memory function only when GPIO pin is = SET
	while(NSSPinStatus==GPIO_PIN_RESET){}

	//Reached end of memory
	if (currentPageWrited == NUMBER_OF_PAGES)
		currentPageWrited = 0;
	else
		currentPageWrited ++;

	//Calculate position to write
	_pageToByte(&currentPageWrited, MemoryPage[MemoryStatus & 1] + 1);//Bit 1 of MemoryStatus, first position is for command

	//Next page to write
	uint16_t nextPageToWrite = currentPageWrited;
	if(nextPageToWrite == NUMBER_OF_PAGES)
		nextPageToWrite = 0;
	else
		nextPageToWrite ++;
	//Check if the next page to write is in a new sector
	if (nextPageToWrite % SECTOR_SIZE == 0){
		//Check if the new sector is already writed
		if(_readHeaderPage(nextPageToWrite) != 0xFF)
			_eraseSector(&nextPageToWrite);
	}

	//Write new page
	flashPage();
}

//Erase all chip memory
//Return 1 if all is done
uint8_t chipErase(){
	if(NSSPinStatus==GPIO_PIN_SET){
		_writeEnable();
		_status();
		if(!(MemoryStatus & 4) && MemoryStatus & 8){
			uint8_t commandToWrite = FLASH_CHIP_ERASE;

			_NSSChangeStatus(GPIO_PIN_RESET);
			HAL_SPI_Transmit(Memoryhspi, &commandToWrite, 1, WAIT_TIME);
			_NSSChangeStatus(GPIO_PIN_SET);
			return 1;
		}
	}
	return 0;
}

//Print all pending data
HAL_StatusTypeDef updateLog(char *options, uint32_t value, uint8_t forceWrite) {
	char dataToWrite [strlen(options) + 10]; // 10 -> maximum number of characters in a uint32_t variable
	uint16_t lenData = sprintf(dataToWrite, options, value);
	uint16_t startingPoint = 0;
	uint16_t lenToWrite = 0;

	do {
		startingPoint += lenToWrite;
		if(PAGE_SIZE - HEADER_SIZE - actualSizeMemoryPage < lenData - startingPoint){
			lenToWrite = PAGE_SIZE - HEADER_SIZE - actualSizeMemoryPage;
		} else {
			lenToWrite = lenData - startingPoint;
		}

		memcpy(MemoryPage[MemoryStatus & 1] + 1 + 3 + HEADER_SIZE + actualSizeMemoryPage, dataToWrite + startingPoint, lenToWrite);
		actualSizeMemoryPage += lenToWrite;

		if (actualSizeMemoryPage > PAGE_SIZE - HEADER_SIZE){
			//ERRORE
			return HAL_ERROR;
		}

		if(PAGE_SIZE - HEADER_SIZE == actualSizeMemoryPage || forceWrite){
			if(forceWrite){
				memset(MemoryPage[MemoryStatus & 1] + 1 + 3 + HEADER_SIZE + actualSizeMemoryPage, 0, PAGE_SIZE - HEADER_SIZE - actualSizeMemoryPage);
			}

			if(MemoryStatus & 2){ //Bit 2 of MemoryStatus
				//TODO: Error: Both buffer are full of data
			}

			//Update memory status bits
			MemoryStatus = MemoryStatus | 2; // Set Bit 2 = 1 			-> Buffer[not(Bit1)] is ready to be written
			MemoryStatus = MemoryStatus ^ 1; // Set Bit 1 = not (Bit 1) -> Buffer[Bit1] is empty
			//Write memory
			_writeMemory();
			actualSizeMemoryPage = 0;
		}
	} while(startingPoint + lenToWrite < lenData);
	return HAL_OK;
}

//Callback
void MemoryMNG_Callback(){
	_NSSChangeStatus(GPIO_PIN_SET);
	MemoryStatus = MemoryStatus & 253;
}

/*
 * MemoryMng.h
 *
 *  Created on: September 16, 2022
 *      Author: BadiBoard
 */

#ifndef MEMORY_MNG_H_
#define MEMORY_MNG_H_

#define FLASH_WRITE_EN 		((uint8_t)0x06)
#define FLASH_WRITE_PAGE	((uint8_t)0x02)
#define FLASH_SECTOR_ERASE	((uint8_t)0x20)
#define FLASH_DATA_READE	((uint8_t)0x03)
#define FLASH_READ_STATUS1	((uint8_t)0x05)
#define FLASH_CHIP_ERASE	((uint8_t)0xC7)

#define NUMBER_OF_PAGES 65535 	// from 0 to 65535 [page] = 16.777.215 (number of byte) / 256 (byte in a page)
#define PAGE_SIZE 		256 	// bytes in a page
#define HEADER_SIZE 	1 		// byte used for header
#define SECTOR_SIZE 	16		// number of pages that will be erased at each time

#define WAIT_TIME 		1		//Time to wait for each bit (when DMA is not used)

#define DELAY_LOG_UPDATE_TIME 100    //every 100ms all new data will write on memory

#include "main.h"
#include <string.h>

//Buffer of a single page before write it
extern uint8_t MemoryPage[2][1 + 3 + PAGE_SIZE];
//Actual buffer filled
extern uint16_t actualSizeMemoryPage;

//Used bit from 0 to 16 to save the page that is just write
extern uint16_t currentPageWrited;

extern uint32_t previousMillis_LogUpdate;

//Initialization of all variables
void initMemory(SPI_HandleTypeDef *hspi);

//Print all pending data
HAL_StatusTypeDef updateLog(char *options, uint32_t value, uint8_t forceWrite);

//Check if memory is waiting to be written
void flashPage();

//Erase all chip memory
//Return 1 if all is done
uint8_t chipErase();

//Callback
void MemoryMNG_Callback();

#endif /* MEMORY_MNG_H_ */

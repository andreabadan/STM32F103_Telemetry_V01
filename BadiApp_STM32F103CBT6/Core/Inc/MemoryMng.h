/*
 * MemoryMng.h
 *
 *  Created on: September 16, 2022
 *      Author: BadiBoard
 */

#ifndef MEMORY_MNG_H_
#define MEMORY_MNG_H_

#define MEMORY_SIZE 128 // [M-bit]
#define PAGE_SIZE 5 // [byte]

#define DELAY_LOG_UPDATE_TIME 100    //every 100ms all new data will write on memory

#include "main.h"
#include <string.h>

extern char MemoryPage[PAGE_SIZE];
extern uint16_t actualSizeMemoryPage;

extern uint32_t previousMillis_LogUpdate;

//Initialization of all variables
void initMemory();

//Print all pending data
HAL_StatusTypeDef updateLog(char *options, uint32_t value, uint8_t forceWrite);

#endif /* MEMORY_MNG_H_ */

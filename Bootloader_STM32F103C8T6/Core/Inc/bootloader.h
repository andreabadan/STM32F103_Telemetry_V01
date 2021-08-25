/*
 * bootloader.h
 *
 *  Created on: June 6, 2021
 *      Author: BadiBoard
 */

#ifndef INC_BOOTLOADER_H_
#define INC_BOOTLOADER_H_

#define APP_START (0x08005000)			//Origin + Bootloader size (20kB)
#define FLASH_BANK_SIZE (0XB000)		//44kB
#define FLASH_PAGE_SIZE_USER (0x400)	//1kB

#define RAM_ADDRESS_BOOTMODE 0x20004FF9//RAM address where read/write BootloaderMode

#define ERASE_FLASH_MEMORY "#$ERASE_MEMORY"
#define FLASHING_START     "#$FLASH_START#"
#define FLASHING_FINISH    "#$FLASH_FINISH"
#define FLASHING_ABORT     "#$FLASH_ABORT#"
#define APPLICATION_START  "#$APPL_START$#"

#include "main.h"
#include "usbd_cdc_if.h"
#include <string.h>

typedef enum
{
    JumpMode   = 0x00000000,
	FlashMode  = 0xFFFFFFFF
} BootloaderMode;

typedef enum
{
    Unerased,
	Erased,
	Writing
} FlashStatus;

typedef enum
{
	Unlocked,
	Locked
} FlashLocked;

typedef enum
{
	InvalidCommand,
	EraseMemory,
	FlashStart,
	FlashFinish,
	FlashAbort,
	StartApplication
} Command;

typedef void (application_t)(void);

typedef struct
{
    uint32_t		stack_addr;     // Stack Pointer
    application_t*	func_p;        // Program Counter
} JumpStruct;

uint32_t Flashed_offset;
FlashStatus flashStatus;
FlashLocked flashLocked;
//uint32_t *bootReadPointer = (uint32_t*)RAM_ADDRESS_BOOTMODE;

extern USBD_HandleTypeDef hUsbDeviceFS;//it is defined in the usb_device.c

uint32_t Read_BootMode(uint32_t RAM_Address);
void Write_BootMode(uint32_t RAM_Address, uint32_t data);

void bootloaderInit();

void jumpToApp();
void deinitEverything();

void flashWord(uint32_t word);
uint32_t readWord(uint32_t address);

void errorBlink(char UnknounCommand);

Command commandDecoding(char array1[]);
uint8_t string_compare(char array1[], char array2[], uint16_t length);
void messageHandler(uint8_t* Buf);

#endif /* INC_BOOTLOADER_H_ */

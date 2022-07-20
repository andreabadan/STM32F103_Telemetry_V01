/*
 * bootloader.h
 *
 *  Created on: June 6, 2021
 *      Author: BadiBoard
 */

#ifndef INC_BOOTLOADER_H_
#define INC_BOOTLOADER_H_

#define APP_START (0x08005000)			//Origin + Bootloader size (20kB)
#define FLASH_BANK_SIZE (0X1B000)		//108kB
#define FLASH_PAGE_SIZE_USER (0x400)	//1kB

#define ERASE_FLASH_MEMORY "#$ERASE_MEMORY"
#define FLASHING_START     "#$FLASH_START#"
#define FLASHING_FINISH    "#$FLASH_FINISH"
#define FLASHING_ABORT     "#$FLASH_ABORT#"
#define APPLICATION_START  "#$APPL_START$#"

#define NUMBER_SHARED_CARACTERS 14

#define BOOTLOADER_RUNNING "b"
#define FLASHING_ERROR     "e"
#define FLASHING_OK        "k"

#include "main.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"
#include <string.h>

typedef enum
{
    JumpMode     = 0x00000000,
	FlashModeBT  = 0xFFFFFFFF,
	FlashModeUSB = 0xFFFFFFF0
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
	NotDone,
	Done
} FunctResult;

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

extern BootloaderMode bootLoaderMode;

extern uint32_t Flashed_offset;
extern FlashStatus flashStatus;
extern FlashLocked flashLocked;

void bootloaderInit();

void jumpToApp();
void deinitEverything();

void flashDoubleWord(uint64_t dataToFlash);
uint64_t readDoubleWord(uint32_t address);

void errorBlink();

Command commandDecoding(char array1[]);
uint8_t string_compare(char array1[], char array2[], uint16_t length);
void messageHandler(uint8_t* Buf);
void createMessage(uint8_t* Buf,  uint16_t Len);
void trasmitAckMessage(FunctResult Result);
void transmitMessage(uint8_t* Buf, uint16_t Len);

#endif /* INC_BOOTLOADER_H_ */

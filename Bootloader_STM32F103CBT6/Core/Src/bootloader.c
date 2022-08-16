/*
 * bootloader.c
 *
 *  Created on: June 6, 2021
 *      Author: BadiBoard
 */

#include "BootLoader.h"
#include "main.h"

uint32_t Flashed_offset;
FlashStatus flashStatus;
FlashLocked flashLocked;

BootloaderMode __attribute__((section(".BootOptions"))) bootLoaderMode;

void bootloaderInit()
{
	for(uint8_t i=0; i<3; i++){
		HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
		HAL_Delay(100);
	}
	HAL_Delay(200);

	Flashed_offset = 0;
	flashStatus = Unerased;
	flashLocked = Locked;

	switch(bootLoaderMode)
	{
		case FlashModeBT:
		case FlashModeUSB:
			for(uint8_t i=0; i<10; i++)
			{
				HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
				HAL_Delay(10);
				HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
				HAL_Delay(90);
			}
			transmitMessage((uint8_t*)BOOTLOADER_RUNNING, strlen(BOOTLOADER_RUNNING));
			break;
		case JumpMode:
			jumpToApp();
			break;
		default:
			bootLoaderMode = JumpMode;
			jumpToApp();
			break;
	}
}

void jumpToApp()
{
	for(uint8_t i=0; i<2; i++){
		HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
		HAL_Delay(50);
		HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
		HAL_Delay(50);
	}
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
	// Check if the application is there
	uint8_t emptyCellCount = 0;
	// TODO: change 20 constant
	for(uint8_t i=0; i<20; i++)
	{
		if(readDoubleWord(APP_START + (i*8)) == -1)
			emptyCellCount++;
	}
	if(emptyCellCount != 20)
	{
		HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);

		const JumpStruct* vector_p = (JumpStruct*)APP_START;

		deinitEverything();

		// Jump to app
		asm("msr msp, %0; bx %1;" : : "r"(vector_p->stack_addr), "r"(vector_p->func_p));
	}else{
		errorBlink();
		bootLoaderMode = FlashModeBT;
		NVIC_SystemReset();
	}
}

void deinitEverything()
{
	// Reset peripherals to guarantee flawless start of user application
	HAL_GPIO_DeInit(BootloaderLed_GPIO_Port, BootloaderLed_Pin);
	MX_USB_DEVICE_DeInit();
	  __HAL_RCC_GPIOC_CLK_DISABLE();
	  __HAL_RCC_GPIOD_CLK_DISABLE();
	  __HAL_RCC_GPIOB_CLK_DISABLE();
	  __HAL_RCC_GPIOA_CLK_DISABLE();
	HAL_RCC_DeInit();
	HAL_DeInit();
	SysTick->CTRL = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;
}

static FunctResult unlockMemory(){
	// Unock the Flash to enable the flash control register access
	if(HAL_FLASH_Unlock() == HAL_OK){
	// Allow Access to option bytes sector
		if (HAL_FLASH_OB_Unlock()==HAL_OK){
			flashLocked = Unlocked;
			return Done;
		}
	}
	flashLocked = Locked;
	return NotDone;
}

static FunctResult lockMemory(){
	// Lock the Flash to enable the flash control register access
	if(HAL_FLASH_Lock()==HAL_OK){
		// Lock Access to option bytes sector
		if(HAL_FLASH_OB_Lock()==HAL_OK){
			flashLocked = Locked;
			return Done;
		}
	}
	flashLocked = Unlocked;
	return NotDone;
}

static FunctResult eraseMemory()
{
	// Fill EraseInit structure
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = APP_START;
	EraseInitStruct.NbPages = FLASH_BANK_SIZE/FLASH_PAGE_SIZE_USER;
	uint32_t PageError;

	volatile HAL_StatusTypeDef status_erase;
	status_erase = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	Flashed_offset = 0;
	if(status_erase != HAL_OK){
		errorBlink();
		flashStatus = Unerased;
		return NotDone;
	} else {
		flashStatus = Erased;
		return Done;
	}
}


void flashDoubleWord(uint64_t dataToFlash)
{
	if((flashStatus == Erased || flashStatus == Writing) && flashLocked == Unlocked)
	{
	  volatile HAL_StatusTypeDef status;
	  uint8_t flash_attempt = 0;
	  uint32_t address;
	  //try 10 times to write before get the error exeption
	  do
	  {
		  address = APP_START + Flashed_offset;
		  status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, dataToFlash);
		  flash_attempt++;
	  } while(status != HAL_OK && flash_attempt < 10 && dataToFlash == readDoubleWord(address));
	  if(status != HAL_OK)  {//Error exeption
		  transmitMessage((uint8_t*)&FLASHING_ERROR, strlen(FLASHING_ERROR));
	  } else {//Word Flash Successful
		  if(flashStatus != Writing)
			  flashStatus = Writing;
		  Flashed_offset += 8;
		  transmitMessage((uint8_t*)&FLASHING_OK, strlen(FLASHING_OK));
	  }
	}else
	{
		transmitMessage((uint8_t*)&FLASHING_ERROR,strlen(FLASHING_ERROR));
	}
}

uint64_t readDoubleWord(uint32_t address)
{
	uint64_t read_data;
	read_data = *(uint64_t*)(address);
	return read_data;
}

void errorBlink()
{
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);

	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(500);

	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(800);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(800);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(800);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(500);

	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(3000);
}

Command commandDecoding(char array1[]){
	//Initialize command
	Command command = InvalidCommand;
	//Found right command
	//Erase memory
	if(string_compare((char*)array1, ERASE_FLASH_MEMORY, strlen(ERASE_FLASH_MEMORY)))
		command = EraseMemory;
	//Flash start
	if(string_compare((char*)array1, FLASHING_START, strlen(FLASHING_START)))
		command = FlashStart;
	if(string_compare((char*)array1, FLASHING_FINISH, strlen(FLASHING_FINISH)))
		command = FlashFinish;
	//Flash abort
	if(string_compare((char*)array1, FLASHING_ABORT, strlen(FLASHING_ABORT)))
		command = FlashAbort;
	//Restart application
	if(string_compare((char*)array1, APPLICATION_START, strlen(APPLICATION_START)))
		command = StartApplication;

	return(command);
}

uint8_t string_compare(char array1[], char array2[], uint16_t length)
{
	 uint8_t i;
	 for(i=0;i<length;i++){
		 if(array1[i]!=array2[i])
			 return 0;
	 }
	 return 1;
}

void messageHandler(uint8_t* Buf)
{
	Command comandReceived = commandDecoding((char*)Buf);
	FunctResult functResultTMP = Done;
	switch(comandReceived){
		case InvalidCommand:
			transmitMessage((uint8_t*)&BOOTLOADER_RUNNING FLASHING_ERROR, strlen(FLASHING_ERROR BOOTLOADER_RUNNING));
			break;
		case EraseMemory:
		case FlashAbort:
			if(flashLocked != Unlocked)
				functResultTMP = unlockMemory();
			if(flashStatus != Erased && functResultTMP == Done)
				functResultTMP = eraseMemory();
			trasmitAckMessage(lockMemory());
			break;
		case FlashStart:
			if(flashLocked != Unlocked)
				functResultTMP = unlockMemory();
			if(flashStatus != Erased && functResultTMP == Done)
				functResultTMP = eraseMemory();
			trasmitAckMessage(functResultTMP);
			break;
		case FlashFinish:
			if(flashStatus == Writing){
				flashStatus = Unerased;
				if(flashLocked != Locked)
					lockMemory();
				bootLoaderMode = JumpMode;
				transmitMessage((uint8_t*)&FLASHING_OK, strlen(FLASHING_OK));
				NVIC_SystemReset();
			} else {
				transmitMessage((uint8_t*)&FLASHING_ERROR, strlen(FLASHING_ERROR));
				unlockMemory();
				eraseMemory();
				lockMemory();
				NVIC_SystemReset();
			}
			break;
		case StartApplication:
			bootLoaderMode = JumpMode;
			NVIC_SystemReset();
			break;
	}
}

void createMessage(uint8_t* Buf,  uint16_t Len)
{
	if(Len == 8 && flashLocked == Unlocked && flashStatus != Unerased){
		uint64_t dataToFlash =  ((uint64_t)Buf[7]<<56) +
 								((uint64_t)Buf[6]<<48) +
								((uint64_t)Buf[5]<<40) +
								((uint64_t)Buf[4]<<32) +
								((uint64_t)Buf[3]<<24) +
								((uint64_t)Buf[2]<<16) +
								((uint64_t)Buf[1]<< 8) +
								 (uint64_t)Buf[0];//32bit Word contains 4 Bytes
		flashDoubleWord(dataToFlash);
	}else{
		messageHandler(Buf);
	}

	HAL_GPIO_TogglePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin);
}

void trasmitAckMessage(FunctResult Result){
	if(Result == Done)
		transmitMessage((uint8_t*)&FLASHING_OK, strlen(FLASHING_OK));
	else
		transmitMessage((uint8_t*)&FLASHING_ERROR, strlen(FLASHING_ERROR));
}

void transmitMessage(uint8_t* Buf, uint16_t Len){
	if(bootLoaderMode == FlashModeBT) {
		transmitUART(Buf, Len);
	} else if(bootLoaderMode == FlashModeUSB) {
		CDC_Transmit_FS(Buf, Len);
	}
}

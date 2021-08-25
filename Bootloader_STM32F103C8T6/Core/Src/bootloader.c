/*
 * bootloader.c
 *
 *  Created on: June 6, 2021
 *      Author: BadiBoard
 */

#include "bootloader.h"

uint32_t Read_BootMode(uint32_t RAM_Address) {
    uint32_t *RAM_Pointer = (uint32_t*) RAM_Address;
	return *RAM_Pointer;
}

void Write_BootMode(uint32_t RAM_Address, uint32_t data) {
	uint32_t *RAM_Pointer = (uint32_t*) RAM_Address;
	*RAM_Pointer = data;
}

void bootloaderInit()
{
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);

	Flashed_offset = 0;
	flashStatus = Unerased;
	flashLocked = Locked;

	BootloaderMode bootloaderMode = Read_BootMode(RAM_ADDRESS_BOOTMODE);

	switch(bootloaderMode)
	{
		case FlashMode:
			for(uint8_t i=0; i<10; i++)
			{
				HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
				HAL_Delay(10);
				HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
				HAL_Delay(90);
			}
			break;
		case JumpMode:
			jumpToApp();
			break;
		default:
			Write_BootMode(RAM_ADDRESS_BOOTMODE, JumpMode);
			jumpToApp();
			break;
	}
}

void jumpToApp()
{
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_RESET);
	//Check if the application is there
	uint8_t emptyCellCount = 0;
	for(uint8_t i=0; i<20; i++)
	{
		if(readWord(APP_START + (i*4)) == -1)
			emptyCellCount++;
	}
	if(emptyCellCount != 20)
	{
		const JumpStruct* vector_p = (JumpStruct*)APP_START;

		deinitEverything();

		/* let's do The Jump! */
		/* Jump, used asm to avoid stack optimization */
		asm("msr msp, %0; bx %1;" : : "r"(vector_p->stack_addr), "r"(vector_p->func_p));
	}else{
		errorBlink(0);
	}
}

void deinitEverything()
{
	//-- reset peripherals to guarantee flawless start of user application
	HAL_GPIO_DeInit(BootloaderLed_GPIO_Port, BootloaderLed_Pin);
	USBD_DeInit(&hUsbDeviceFS);
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

static void unlockMemory(){
	/* Unock the Flash to enable the flash control register access *************/
	while(HAL_FLASH_Unlock()!=HAL_OK)
		while(HAL_FLASH_Lock()!=HAL_OK);//Weird fix attempt

	/* Allow Access to option bytes sector */
	while(HAL_FLASH_OB_Unlock()!=HAL_OK)
		while(HAL_FLASH_OB_Lock()!=HAL_OK);//Weird fix attempt

	flashLocked = Unlocked;
}

static void lockMemory(){
	/* Lock the Flash to enable the flash control register access *************/
	while(HAL_FLASH_Lock()!=HAL_OK)
		while(HAL_FLASH_Unlock()!=HAL_OK);//Weird fix attempt

	/* Lock Access to option bytes sector */
	while(HAL_FLASH_OB_Lock()!=HAL_OK)
		while(HAL_FLASH_OB_Unlock()!=HAL_OK);//Weird fix attempt

	flashLocked = Locked;
}

static void eraseMemory()
{
	/* Fill EraseInit structure*/
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = APP_START;
	EraseInitStruct.NbPages = FLASH_BANK_SIZE/FLASH_PAGE_SIZE_USER;
	uint32_t PageError;

	volatile HAL_StatusTypeDef status_erase;
	status_erase = HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);

	if(status_erase != HAL_OK)
		errorBlink(0);
	flashStatus = Erased;
	Flashed_offset = 0;
}


void flashWord(uint32_t dataToFlash)
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
		  status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address, dataToFlash);
		  flash_attempt++;
	  }while(status != HAL_OK && flash_attempt < 10 && dataToFlash == readWord(address));
	  if(status != HAL_OK){//Error exeption
		  CDC_Transmit_FS((uint8_t*)&"Flashing Error!\n", strlen("Flashing Error!\n"));
	  } else {//Word Flash Successful
		  if(flashStatus != Writing)
			  flashStatus = Writing;
		  Flashed_offset += 4;
		  CDC_Transmit_FS((uint8_t*)&"Flash: OK\n", strlen("Flash: OK\n"));
	  }
	}else
	{
	  CDC_Transmit_FS((uint8_t*)&"Error: Memory not unlocked nor erased!\n",
			  strlen("Error: Memory not unlocked nor erased!\n"));
	}
}

uint32_t readWord(uint32_t address)
{
	uint32_t read_data;
	read_data = *(uint32_t*)(address);
	return read_data;
}

void errorBlink(char UnknounCommand)
{
	HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
	while(1)
	{
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

		if(UnknounCommand)
		{
			HAL_GPIO_WritePin(BootloaderLed_GPIO_Port, BootloaderLed_Pin, GPIO_PIN_SET);
			HAL_Delay(3000);
		}
	}
}

Command commandDecoding(char array1[]){
	//Initialize command
	Command command = InvalidCommand;
	//Found right command
	if(string_compare((char*)array1, ERASE_FLASH_MEMORY, strlen(ERASE_FLASH_MEMORY)))
		command = EraseMemory;
	if(string_compare((char*)array1, FLASHING_START, strlen(FLASHING_START)))
		command = FlashStart;
	if(string_compare((char*)array1, FLASHING_FINISH, strlen(FLASHING_FINISH)))
		command = FlashFinish;
	if(string_compare((char*)array1, FLASHING_ABORT, strlen(FLASHING_ABORT)))
		command = FlashAbort;
	if(string_compare((char*)array1, APPLICATION_START, strlen(APPLICATION_START)))
		command = StartApplication;

	return(command);
}

uint8_t string_compare(char array1[], char array2[], uint16_t length)
{
	 uint8_t comVAR=0, i;
	 for(i=0;i<length;i++)
	   	{
	   		  if(array1[i]==array2[i])
	   	  		  comVAR++;
	   	  	  else comVAR=0;
	   	}
	 if (comVAR==length)
		 	return 1;
	 else 	return 0;
}

void messageHandler(uint8_t* Buf)
{
	Command comandReceived = commandDecoding((char*)Buf);
	switch(comandReceived){
		case InvalidCommand:
			CDC_Transmit_FS((uint8_t*)&"Error: Unknown command!\n", strlen("Error: Unknown command!\n"));
			break;
		case EraseMemory:
			if(flashLocked != Unlocked)
				unlockMemory();
			if(flashStatus != Erased)
				eraseMemory();
			lockMemory();
			CDC_Transmit_FS((uint8_t*)&"Flash: Erased!\n", strlen("Flash: Erased!\n"));
			break;
		case FlashStart:
			if(flashLocked != Unlocked)
				unlockMemory();
			if(flashStatus != Erased)
				eraseMemory();
			CDC_Transmit_FS((uint8_t*)&"Flash: Unlocked & Erased!\n", strlen("Flash: Unlocked & Erased!\n"));
			break;
		case FlashFinish:
			if(flashStatus == Writing){
				flashStatus = Unerased;
				if(flashLocked != Locked)
					lockMemory();
				Write_BootMode(RAM_ADDRESS_BOOTMODE, JumpMode);
				CDC_Transmit_FS((uint8_t*)&"Flash: Success!\n", strlen("Flash: Success!\n"));
			} else {
				CDC_Transmit_FS((uint8_t*)&"Flash: Error: flash procedure not running\n", strlen("Flash: Error: flash procedure not running\n"));
			}
			break;
		case FlashAbort:
			if(flashLocked != Unlocked)
				unlockMemory();
			if(flashStatus != Erased)
				eraseMemory();
			lockMemory();
			CDC_Transmit_FS((uint8_t*)&"Flash: Aborted!\n", strlen("Flash: Aborted!\n"));
			break;
		case StartApplication:
			Write_BootMode(RAM_ADDRESS_BOOTMODE, JumpMode);
			break;
	}
}

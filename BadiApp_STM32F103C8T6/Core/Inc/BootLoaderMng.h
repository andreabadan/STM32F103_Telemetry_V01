/*
 * BootLoaderMng.h
 *
 *  Created on: October 15, 2021
 *      Author: BadiBoard
 */

#ifndef BOOT_LOADER_MNG_H_
#define BOOT_LOADER_MNG_H_

#define BOOTLOADER_WRITE_B 66 //->B in ASCII
#define BOOTLOADER_WRITE_O 79 //->O in ASCII
#define BOOTLOADER_WRITE_T 84 //->T in ASCII

typedef enum
{
    JumpMode   = 0x00000000,
	FlashMode  = 0xFFFFFFFF
} BootLoaderMode;
extern BootLoaderMode bootloaderMode;

#include "main.h"

//Initialization of all variables
void initBootLoaderMode();

//Execute jump into the BootLoader
void jumpToBootLoader(BootLoaderMode Mode);

#endif /* BOOT_LOADER_MNG_H_ */

/*
 * BootLoaderMng.h
 *
 *  Created on: October 15, 2021
 *      Author: BadiBoard
 */

#ifndef BOOT_LOADER_MNG_H_
#define BOOT_LOADER_MNG_H_

typedef enum
{
    JumpMode     = 0x00000000,
	FlashModeBT  = 0xFFFFFFFF,
	FlashModeUSB = 0xFFFFFFF0
} BootLoaderMode;
extern BootLoaderMode bootloaderMode;

#include "main.h"

//Initialization of all variables
void initBootLoaderMode();

//Execute jump into the BootLoader
void jumpToBootLoader(BootLoaderMode Mode);

#endif /* BOOT_LOADER_MNG_H_ */

/*
 * BootLoaderMng.c
 *
 *  Created on: October 15, 2021
 *      Author: BadiBoard
 */

#include "BootLoaderMng.h"
BootLoaderMode __attribute__((section(".BootOptions"))) bootLoaderMode;

//Initialization of all variables
void initBootLoaderMode(){
	bootLoaderMode = JumpMode;
}

//Execute jump into the BootLoader
void jumpToBootLoader(BootLoaderMode Mode){
	switch(Mode){
		//in some cases is required to add logic before jump
		default:
			bootLoaderMode = Mode;
	}
	NVIC_SystemReset();
}

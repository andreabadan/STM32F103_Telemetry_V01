/*
 * LAP_Timer.c
 *
 *  Created on: July 3, 2021
 *      Author: BadiBoard
 */

#include "Lap_Timer.h"

//Variable declaration
uint32_t previousMillisLap;

uint32_t Lap_Value;

uint32_t previousMillisLap_Display;
char LapUpdateDisplay;

//Initialization of all variables
void initCounterLap(){
	previousMillisLap = HAL_GetTick();
	Lap_Value = 0;

	previousMillisLap_Display = 0;
	LapUpdateDisplay = 0;
}

//Called after finish each lap
void deltaTimeInterruptLap(uint32_t currentMillisLap){
	uint32_t maxCurrentMillis = previousMillisLap + MAX_DELTA_TIME_MILLIS_LAP;

	if(maxCurrentMillis < currentMillisLap){ //Check if it is the first lap
		previousMillisLap = currentMillisLap;
		Lap_Value = MAX_DELTA_TIME_MILLIS_LAP;
		LapUpdateDisplay = 1;
	} else { //Calculate the time of the current lap
		uint32_t actualMillisLap = currentMillisLap - previousMillisLap;
		if(actualMillisLap > MIN_DELTA_TIME_MILLIS_LAP){
			previousMillisLap = currentMillisLap;
			Lap_Value = actualMillisLap;
			LapUpdateDisplay = 1;
		}
	}
}

/*
 * RPM_Counter.c
 *
 *  Created on: June 27, 2021
 *      Author: BadiBoard
 */

#include "RPM_Counter.h"

//Filter initialization
void initRPM_Filter(){
	RPM_Filter.In  = 0.0;
	RPM_Filter.R   = 0.01;
	RPM_Filter.Q   = 5e-03;
	RPM_Filter.P   = 1.0;
	RPM_Filter.Out = 0.0;
}


//Initialization of all variables
void initCounterRPM(){
	previousMicrosRPM = DWT->CYCCNT / (SystemCoreClock / 1000000U);
	counterAverageRPM = 0;
	RPM_DeltaTime = 0;
	RPM_Value = 0;

	previousMillisRPM_Display = previousMicrosRPM/1000U;

	initRPM_Filter();
}

//Called after each spark pulse
void deltaTimeInterruptRPM(uint32_t currentMicrosRPM){
	uint32_t maxCurrentMicros = previousMicrosRPM + MAX_DELTA_TIME_MICROS_RPM;

	if(maxCurrentMicros < currentMicrosRPM){ //Check if engine is turn on now
		previousMicrosRPM = currentMicrosRPM;
		RPM_DeltaTime = MAX_DELTA_TIME_MICROS_RPM;
		counterAverageRPM = 1;
	} else { //Calculate the delta time
		uint32_t actualMicrosRPM = currentMicrosRPM - previousMicrosRPM;
		if(actualMicrosRPM > MIN_DELTA_TIME_MICROS_RPM){
			previousMicrosRPM = currentMicrosRPM;
			RPM_DeltaTime += actualMicrosRPM;
			counterAverageRPM ++;
		}
	}
}

//Called when is necessary calculate RPM value
void calculateRPM(){
	if(counterAverageRPM > 0) {
		RPM_Filter.In = (60.0f * 1.0f /((float)(RPM_DeltaTime/counterAverageRPM)/1000000.0f))/100.0f; //Formula: 60*(1/(delta t[s]))
		KalmanFilter(&RPM_Filter);
		RPM_Value = RPM_Filter.Out * 100;
	} else {
		initRPM_Filter();
		RPM_Value = 0;
	}
	//Reset counters
	counterAverageRPM = 0;
	RPM_DeltaTime = 0;
}

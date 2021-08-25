/*
 * Temperature_Sensor.h
 *
 *  Created on: August 18, 2021
 *      Author: BadiBoard
 */

#include "Temperature_Sensor.h"
#include "math.h"

//Initialization of all variables
void initReadTemperature(){
	previousMillisTemperature_Read = HAL_GetTick();
	previousMillisTemperature_Display = previousMillisTemperature_Read;
	TemperatureValue = 0;

	counterAverageRead = 0;
	sumReadValue = 0;

	TemperatureAlarmUpdateDisplay = ProbeOk;
}

//Increment counters and readings
void averageRead(){
	sumReadValue += ActualRead;
	counterAverageRead ++;
}

//Convert read average to temperature
void calculateTemperature(){
	float Vin = V_MAX_TEMP*(float)((float)(sumReadValue/counterAverageRead)/4096.0);
	TemperatureValue = (float)(1.0/(1.0 / (TEMP_ZERO + 273.15) + (1.0 / BETA * log((KNOWN_RES_TEMP*Vin)/(V_MAX_TEMP-Vin)/RES_ZERO))) - 273.15)*10.0;

	sumReadValue = 0;
	counterAverageRead = 0;
}

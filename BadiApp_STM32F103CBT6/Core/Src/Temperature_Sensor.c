/*
 * Temperature_Sensor.h
 *
 *  Created on: August 18, 2021
 *      Author: BadiBoard
 */

#include "Temperature_Sensor.h"
#include "math.h"

//Variable declaration
uint32_t previousMillisTemperature_Read;
uint32_t previousMillisTemperature_Display;

unsigned char counterAverageRead;
uint32_t sumReadValue;
uint32_t ActualRead;

KalmanFilterStruct TemperatureFilter;

int16_t TemperatureAlarmThreeshold;
int16_t TemperatureValue;

TempAlarm TemperatureAlarmUpdateDisplay;

//Filter initialization
void initTempFilter(){
	TemperatureFilter.In  = 0.0;
	TemperatureFilter.R   = 0.01;
	TemperatureFilter.Q   = 5e-04;
	TemperatureFilter.P   = 1.0;
	TemperatureFilter.Out = 0.0;
}

//Initialization of all variables
void initReadTemperature(){
	previousMillisTemperature_Read = HAL_GetTick();
	previousMillisTemperature_Display = previousMillisTemperature_Read;
	TemperatureValue = 0;

	TemperatureAlarmThreeshold = 650;

	counterAverageRead = 0;
	sumReadValue = 0;

	initTempFilter();

	TemperatureAlarmUpdateDisplay = ProbeInit;
}

//Increment counters and readings
void averageRead(){
	sumReadValue += ActualRead;
	counterAverageRead ++;
}

//Convert read average to temperature
uint8_t calculateTemperature(){
	/*Save value only if the newest value change*/
	uint8_t TempUpdate = 0;

	float Vin = V_MAX_TEMP*(((float)sumReadValue/(float)counterAverageRead)/4096.0f);

	if(Vin > V_MIN_ERROR && Vin < V_MAX_ERROR) { //Probe OK
		TemperatureFilter.In = (1.0f/(1.0f / (TEMP_ZERO + 273.15f) + (1.0f / BETA * log((KNOWN_RES_TEMP*Vin)/(V_MAX_TEMP-Vin)/RES_ZERO))) - 273.15f);
		//TODO: Init out flter
		/*if(TemperatureAlarmUpdateDisplay != ProbeOk || TemperatureAlarmUpdateDisplay != HighTemperature){
		}*/
		KalmanFilter(&TemperatureFilter);
		int16_t TMP_TemperatureValue = TemperatureFilter.Out * 10.0;

		if(TemperatureValue != TMP_TemperatureValue) {
			TemperatureValue = TemperatureFilter.Out * 10.0;
			TempUpdate = 1;
		}
		if(TemperatureValue > TemperatureAlarmThreeshold) {
			TemperatureAlarmUpdateDisplay = HighTemperature;
		} else {
			TemperatureAlarmUpdateDisplay = ProbeOk;
		}
	} else { //Probe Error
		if(TemperatureAlarmUpdateDisplay != ProbeNotConnected) {
			initTempFilter();
			TempUpdate = 1;
		}
		TemperatureAlarmUpdateDisplay = ProbeNotConnected;
	}

	sumReadValue = 0;
	counterAverageRead = 0;

	return TempUpdate;
}

/*
 * Temperature_Sensor.h
 *
 *  Created on: August 18, 2021
 *      Author: BadiBoard
 */

#include "Temperature_Sensor.h"
#include "math.h"

//Filter initialization
void initFilter(){
	TemperatureFilter.In  = 0.0;
	TemperatureFilter.R   = 0.026971021;
	TemperatureFilter.Q   = 5e-04;
	TemperatureFilter.Pp  = 0.0;
	TemperatureFilter.K   = 0.0;
	TemperatureFilter.e   = 0.0;
	TemperatureFilter.P   = 1.0;
	TemperatureFilter.Xp  = 0.0;
	TemperatureFilter.Out = 0.0;
}

//Initialization of all variables
void initReadTemperature(){
	previousMillisTemperature_Read = HAL_GetTick();
	previousMillisTemperature_Display = previousMillisTemperature_Read;
	TemperatureValue = 0;

	counterAverageRead = 0;
	sumReadValue = 0;

	initFilter();

	TemperatureAlarmUpdateDisplay = ProbeOk;
}

//Increment counters and readings
void averageRead(){
	sumReadValue += ActualRead;
	counterAverageRead ++;
}

//Convert read average to temperature
void calculateTemperature(){
	float Vin = V_MAX_TEMP*(((float)sumReadValue/(float)counterAverageRead)/4096.0);
	if(Vin > V_MIN_ERROR && Vin < V_MAX_ERROR){ //Probe OK
		TemperatureFilter.In = (float)(1.0/(1.0 / (TEMP_ZERO + 273.15) + (1.0 / BETA * log((KNOWN_RES_TEMP*Vin)/(V_MAX_TEMP-Vin)/RES_ZERO))) - 273.15);
		KalmanFilter(&TemperatureFilter);
		TemperatureValue = TemperatureFilter.Out * 10.0;
		if(TemperatureValue > TemperatureAlarmThreeshold){
			TemperatureAlarmUpdateDisplay = HighTemperature;
		} else{
			TemperatureAlarmUpdateDisplay = ProbeOk;
		}
	} else { //Probe Error
		if(TemperatureAlarmUpdateDisplay != ProbeNotConnected){
			initFilter();
		}
		TemperatureAlarmUpdateDisplay = ProbeNotConnected;
	}

	sumReadValue = 0;
	counterAverageRead = 0;
}

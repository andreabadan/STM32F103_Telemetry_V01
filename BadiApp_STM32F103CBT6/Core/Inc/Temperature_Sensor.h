/*
 * Temperature_Sensor.h
 *
 *  Created on: August 18, 2021
 *      Author: BadiBoard
 */

#ifndef TEMPERATURE_SENSOR_H_
#define TEMPERATURE_SENSOR_H_

/* Resistance to temperature constant */
#define V_MAX_TEMP 3.3
#define KNOWN_RES_TEMP 10000.0
#define TEMP_ZERO 100.0
#define RES_ZERO 3300.0
#define BETA 3970.0

#define V_MAX_ERROR 3.28
#define V_MIN_ERROR 0.1

#define CALCULATE_TEMPERATUIRE_SENSOR_TIME 100     	   //250ms (0.25s)
#define DELAY_DISPLAY_TEMPERATUIRE_SENSOR_TIME 2000    //2000ms delay to fix the time of calculateTemperature (2s)

#include "main.h"
#include "CommonFunctions.h"

typedef enum
{
	ProbeInit,
	ProbeOk,
	ProbeNotConnected,
	ProbeErrorReading,
	HighTemperature
} TempAlarm;

extern uint32_t previousMillisTemperature_Read;     //Updated every CALCULATE_TEMPERATUIRE_SENSOR_TIME
extern uint32_t previousMillisTemperature_Display;  //Updated every DELAY_DISPLAY_TEMPERATUIRE_SENSOR_TIME

extern unsigned char counterAverageRead;
extern uint32_t sumReadValue;
extern uint32_t ActualRead;

extern KalmanFilterStruct TemperatureFilter;

extern int16_t TemperatureAlarmThreeshold;
extern int16_t TemperatureValue;

extern TempAlarm TemperatureAlarmUpdateDisplay;
extern uint8_t TempUpdate;

//Initialization of all variables
void initReadTemperature();

//Sum all value read and increment a counter
void averageRead();

//Calculate the current temperature (from average of value read)
void calculateTemperature();

#endif /* TEMPERATURE_SENSOR_H_ */

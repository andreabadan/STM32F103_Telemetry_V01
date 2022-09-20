/*
 * RPM_Counter.h
 *
 *  Created on: June 27, 2021
 *      Author: BadiBoard
 */

#ifndef RPM_COUNTER_H_
#define RPM_COUNTER_H_

#define MIN_DELTA_TIME_MICROS_RPM 2500   //24.000rpm maximum detection (0.0025s)
#define MAX_DELTA_TIME_MICROS_RPM 600000 //100rpm    minimum detection (0.6s)

#define CALCULATE_RPM_DELTA_TIME 200     //200ms (0.2s), max acceptable 637: (2.5 * 255)

typedef enum
{
    Off,
	TurnedOff,
	On,
	TurnedOn
} EngineStatus;

#include "main.h"
#include "CommonFunctions.h"

extern EngineStatus engineStatus;

extern uint32_t previousMicrosRPM;
extern uint8_t counterAverageRPM;
extern uint32_t RPM_DeltaTime;

extern uint16_t RPM_Value;

extern KalmanFilterStruct RPM_Filter;

extern uint32_t previousMillisRPM_Display;


//Initialization of all variables
void initCounterRPM();

//Sum all delta time read and increment a counter
void deltaTimeInterruptRPM(uint32_t currentMicrosRPM);

//Calculate the current RPM value (from average of value read)
void calculateRPM();
#endif /* RPM_COUNTER_H_ */

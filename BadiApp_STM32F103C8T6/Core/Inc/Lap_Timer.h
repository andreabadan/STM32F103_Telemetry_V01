/*
 * Lap_Timer.h
 *
 *  Created on: July 3, 2021
 *      Author: BadiBoard
 */

#ifndef LAP_TIMER_H_
#define LAP_TIMER_H_

#define MIN_DELTA_TIME_MILLIS_LAP 5000   //5000ms minimum detection (5s)
#define MAX_DELTA_TIME_MILLIS_LAP 999999 //999999ms maximum detection (16min 39s 999ms)

#define CALCULATE_LAP_DELTA_TIME 200     //200ms (0.2s)
#define DELAY_DISPLAY_LAP_TIME 1000      //1000ms delay to fix the time of the lap done (1s)

#include "main.h"

uint32_t previousMillisLap;

uint32_t Lap_Value;

uint32_t previousMillisLap_Display;
char LapUpdateDisplay;


//Initialization of all variables
void initCounterLap();

//Calculate the current lap time
void deltaTimeInterruptLap(uint32_t currentMillisLap);

#endif /* LAP_TIMER_H_ */

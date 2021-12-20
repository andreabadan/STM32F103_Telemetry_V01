/*
 * CommonFunctions.h
 *
 *  Created on: December 12, 2021
 *      Author: BadiBoard
 */

#ifndef COMMON_FUNCTIONS_H_
#define COMMON_FUNCTIONS_H_

#include "main.h"

typedef struct{
	float In;   // Input
	float R;    // variance of the noise on the measurement
	float Q;    // variance of the disturbance on the process
	float P;    // P (t | t) variance of the filtering error
	float Out;  // Output
}KalmanFilterStruct;

typedef struct{
	float In;   // Input
	uint8_t M;  // Linearization of error (from 0 to 255)
	float Out;  // Output
}IIRFilterStruct;

void KalmanFilter(KalmanFilterStruct *Struct);

void IIRFilter(IIRFilterStruct *Struct);

#endif /* COMMON_FUNCTIONS_H_ */

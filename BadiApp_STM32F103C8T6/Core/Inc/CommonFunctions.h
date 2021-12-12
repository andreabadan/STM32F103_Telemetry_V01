/*
 * CommonFunctions.h
 *
 *  Created on: December 12, 2021
 *      Author: BadiBoard
 */

#ifndef COMMON_FUNCTIONS_H_
#define COMMON_FUNCTIONS_H_

typedef struct{
	float In;   // Input
	float R;    // variance of the noise on the measurement
	float Q;    // variance of the disturbance on the process
	float Pp;   // P (t | t-1) variance of the prediction error
	float K;    // Kalman gain
	float e;    // Epsilon, term of innovation
	float P;    // P (t | t) variance of the filtering error
	float Xp;   // x_^ (t | t-1) forecast of the previous state
	float Out;  // Output
}KalmanFilterStruct;

#include "main.h"

void KalmanFilter(KalmanFilterStruct *Struct);

#endif /* COMMON_FUNCTIONS_H_ */

/*
 * CommonFunctions.c
 *
 *  Created on: December 12, 2021
 *      Author: BadiBoard
 */

#include "CommonFunctions.h"

//KalmanFilter
void KalmanFilter(KalmanFilterStruct *Struct){
	//P (t | t-1) variance of the prediction error
	float Pp = Struct->P + Struct->Q;                // (PREDICTION) prediction of the variance of error in the next step
	//x_^ (t | t-1) forecast of the previous state
	float Xp = Struct->Out;                          // (PREDICTION) state prediction in the next step
	//Kalman gain
	float K  = Pp/(Pp + Struct->R);                  // (CORRECTION) Kalman gain

	Struct->P  = (1-K)*Pp;                           // (CORRECTION) updating the variance of the filtering error
	Struct->Out = Xp + K*(Struct->In-Xp);            // (CORRECTION) output + Kalman gain * variance of the filtering error
}


//IIRFilter
void IIRFilter(IIRFilterStruct *Struct){
	float K;//IIR Gain
	if(Struct->In > Struct->Out) {
		K = (Struct->In - Struct->Out)*Struct->M;
	} else {
		K = (Struct->Out - Struct->In)*Struct->M;
	}

	if(K >= 1.0f) {
		Struct->Out = Struct->In;    //Change very high, so filter will initialize again
	} else if(K <= 0.0f) {
		Struct->Out = Struct->Out;   //Change very low, so output will not change
	} else {
		Struct->Out = K*Struct->In + (1.0f-K)*Struct->Out; //Calculate new output
	}
}

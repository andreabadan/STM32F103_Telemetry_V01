/*
 * CommonFunctions.c
 *
 *  Created on: December 12, 2021
 *      Author: BadiBoard
 */

#include "CommonFunctions.h"

//KalmanFilter
void KalmanFilter(KalmanFilterStruct *Struct){
	Struct->Pp = Struct->P + Struct->Q;                // (PREDICTION) prediction of the variance of error in the next step
	Struct->Xp = Struct->Out;                          // (PREDICTION) state prediction in the next step
	Struct->K  = Struct->Pp/(Struct->Pp + Struct->R);  // (CORRECTION) Kalman gain
	Struct->e  = Struct->In-Struct->Xp;                // (CORRECTION) innovation update
	Struct->P  = (1-Struct->K)*Struct->Pp;             // (CORRECTION) updating the variance of the filtering error
	Struct->Out = Struct->Xp + Struct->K*Struct->e;    // (CORRECTION) output
}

/*
 * Gorev.c
 *
 *  Created on: Sep 1, 2020
 *      Author: Merve
 */

#include "Gorev.h"
#include "math.h"

_Bool Gorev1_0x1(sSensor_Data_t *Sensor_Data){
		float angle;

		angle = sqrt(pow(Sensor_Data->roll, 2) + pow(Sensor_Data->pitch, 2));
		if(angle > 30) return 1;
		else return 0;
}

_Bool Gorev1_0x2(sSensor_Data_t *Sensor_Data){
	if(Sensor_Data->Vz < 5.0) return 1;
	else return 0;
}

_Bool Gorev2(sSensor_Data_t *Sensor_Data, _Bool Gorev1){

	if(Gorev1){
		if((Sensor_Data->Alt) < 650) return 1;
		else return 0;
	}
	else return 0;
}

/*
 * Gorev.c
 *
 *  Created on: Sep 1, 2020
 *      Author: Merve
 */
#include "Gorev.h"
#include "math.h"

_Bool Gorev1(sBMP280_handle_t *hBMP280){
	static float prev = 0;
	hBMP280->Vz = (hBMP280->Altitude - prev)*10;
	prev = hBMP280->Altitude;
	if(hBMP280->Vz < 5.0) return 1;
	else return 0;
}



_Bool Gorev2(sBMP280_handle_t *hBMP280, _Bool Gorev1){

	if(Gorev1){
		if((hBMP280->Altitude) < 650) return 1;
		else return 0;
	}
	else return 0;
}



/*
 * Telemetry.c
 *
 *  Created on: Jul 26, 2020
 *      Author: Faruk
 */

#include "Telemetry.h"
#include "string.h"
#include "stdio.h"


extern UART_HandleTypeDef huart2;

void Telemetry_send_data(sGPS_handle_t *hGPS){
	uint8_t data_byte[12];
	float data_float[2];
	data_float[0] = hGPS->longitude;
	data_float[1] = hGPS->latitude;


	int i = 0;
	while(i<2){
		float_to_uint8(data_float[i], &data_byte[(i*4)+2]);
		i++;
	}

	data_byte[0] = 36;
	data_byte[1] = 36;
	data_byte[10] = 10;
	data_byte[11] = 10;

	HAL_UART_Transmit(&huart2, data_byte, 12, 1000);

}


void float_to_uint8(float dataIn, uint8_t *adress){
	union FloatingPointIEEE754 {
		struct {
			unsigned int mantissa : 23;
			unsigned int exponent : 8;
			unsigned int sign : 1;
		} raw;
		float f;
	}number;

	number.f = dataIn;
	*(adress+3) = (number.raw.mantissa) | 0x00;
	*(adress+2) = (number.raw.mantissa >> 8) | 0x00;
	*(adress+1) = (number.raw.mantissa >> 16) | (number.raw.exponent << 7);
	*(adress+0) = (number.raw.exponent >> 1) | (number.raw.sign << 7);
};


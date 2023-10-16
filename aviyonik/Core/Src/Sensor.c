/*
 * Sensor.c
 *
 *  Created on: Jul 26, 2020
 *      Author: Faruk
 */

#include "Sensor.h"
#include "math.h"
#include "stdlib.h"


void Sensor_location(sSensor_Data_t *Sensor_Data, sSensor_Data_raw_t *Raw_Data, sGPS_handle_t hGPS, sBMP280_handle_t hBMP280){
	Sensor_Data->Lat = hGPS.latitude;
	Sensor_Data->Lon = hGPS.longitude; //??????????????????????????????????????

	Sensor_Data->Alt = Sensor_filter(Raw_Data->Altitude, hBMP280.Altitude);

}

void Sensor_euler(sSensor_Data_t *Sensor_Data, sBNO055_handle_t hBNO055){
	Sensor_Data->head = hBNO055.head;
	Sensor_Data->roll = hBNO055.roll;
	Sensor_Data->pitch = hBNO055.pitch;
}

void Sensor_velocity(sSensor_Data_t *Sensor_Data, sBMP280_handle_t hBMP280){

	static float temp = 0.0;
	Sensor_Data->Vz = (Sensor_Data->Alt - temp)/ 0.1f;
	temp = Sensor_Data->Alt;

}

float Sensor_filter(float *array1, float newdata){
	float array2[15], array3[15];

		int i = 0;
		while(i < 15){
			array2[i] = array1[i+1];
			i++;
		}
		array2[14] = newdata;

		i = 0;

		while(i < 15){
			array1[i] = array2[i];
			array3[i] = array2[i];
			i++;
		}

		int j, min_idx;

				for (i = 0; i < 14; i++) {
	    			min_idx = i;
		        	for (j = i + 1; j < 15; j++)
		            	if (array3[j] < array3[min_idx]){
		            		min_idx = j;
						}
		   				float temp = array3[min_idx];
		   				array3[min_idx] = array3[i];
		    			array3[i] = temp;
					}

				return (float)array3[7];


}

/*
 * Sensor.h
 *
 *  Created on: Jul 26, 2020
 *      Author: Faruk
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "BNO055.h"
#include "BMP280.h"
//#include "BMI088.h"
#include "GPS.h"

typedef struct{
	float Lon, Lat, Alt;
	float head, roll, pitch;
	float Vz;
}sSensor_Data_t;

typedef struct{
	float Altitude[15];
	float head[15], roll[15], pitch[15];
}sSensor_Data_raw_t;



void Sensor_location(sSensor_Data_t *Sensor_Data, sSensor_Data_raw_t *Raw_Data, sGPS_handle_t hGPS, sBMP280_handle_t hBMP280);
void Sensor_euler(sSensor_Data_t *Sensor_Data, sBNO055_handle_t hBNO055);
void Sensor_velocity(sSensor_Data_t *Sensor_Data, sBMP280_handle_t hBMP280);
float Sensor_filter(float *array1, float newdata);


#endif /* INC_SENSOR_H_ */

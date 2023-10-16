/*
 * GPS.h
 *
 *  Created on: Jul 29, 2020
 *      Author: Faruk
 */

#ifndef INC_GPS_H_
#define INC_GPS_H_

#include "stm32g4xx_hal.h"
#include "stdlib.h"



typedef struct {
	uint8_t checkBuffer;
	uint8_t gpsIndex;
	uint8_t packageFind;

	uint8_t gpsBuffer[100];
	char thisSentence[3];

	  float latitude;  ///< Floating point latitude value in degrees/minutes
	                          ///< as received from the GPS (DDMM.MMMM)
	  float longitude; ///< Floating point longitude value in degrees/minutes
	                          ///< as received from the GPS (DDDMM.MMMM)

	  /** Fixed point latitude and longitude value with degrees stored in units of
	    1/10000000 of a degree. See pull #13 for more details:
	    https://github.com/adafruit/Adafruit-GPS-Library/pull/13 */
	  int32_t latitude_fixed;  ///< Fixed point latitude in decimal degrees.
	                           ///< Divide by 10000000.0 to get a double.
	  int32_t longitude_fixed; ///< Fixed point longitude in decimal degrees
	                           ///< Divide by 10000000.0 to get a double.

	  float latitudeDegrees;  ///< Latitude in decimal degrees
	  float longitudeDegrees; ///< Longitude in decimal degrees
	  float geoidheight;      ///< Diff between geoid height and WGS84 height
	  float altitude;         ///< Altitude in meters above MSL
	  float speed;            ///< Current speed over ground in knots
	  float angle;            ///< Course in degrees from true north
	  float magvariation; ///< Magnetic variation in degrees (vs. true north)
	  float HDOP; ///< Horizontal Dilution of Precision - relative accuracy
	                     ///< of horizontal position
	  float VDOP; ///< Vertical Dilution of Precision - relative accuracy
	                     ///< of vertical position
	  float PDOP; ///< Position Dilution of Precision - Complex maths derives
	                     //< a simple, single number for each kind of DOP

	  char lat;    ///< N/S
	  char lon;    ///< E/W
	  char mag;    ///< Magnetic variation direction

	  _Bool fix;          ///< Have a fix?

	  uint8_t fixquality;    ///< Fix quality (0, 1, 2 = Invalid, GPS, DGPS)
	  uint8_t fixquality_3d; ///< 3D fix quality (1, 3, 3 = Nofix, 2D fix, 3D fix)
	  uint8_t satellites;    ///< Number of satellites in use



}sGPS_handle_t;


int parseGPS(sGPS_handle_t *hGPS);

int parseCoord(sGPS_handle_t *hGPS, char *pStart, float *angleDegrees, float *angle, int32_t *angle_fixed, char *dir);
int isEmpty(char *pStart);

#endif /* INC_GPS_H_ */

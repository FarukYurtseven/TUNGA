/*
 * GPS.c
 *
 *  Created on: Jul 29, 2020
 *      Author: Faruk
 */
#include "GPS.h"

#include "string.h"
#include "stdlib.h"

extern UART_HandleTypeDef huart1;



int isEmpty(char *pStart) {
	     if (',' != *pStart && '*' != *pStart && pStart != NULL)
	       return 0;
	     else
	       return 1;
}



int parseCoord(sGPS_handle_t *hGPS, char *pStart, float *angleDegrees, float *angle, int32_t *angle_fixed, char *dir){
 char *p = pStart;
 if (!isEmpty(p)) {
   // get the number in DDDMM.mmmm format and break into components
   char degreebuff[10] = {0}; // Ensure string is terminated after strncpy
   char *e = strchr(p, '.');
   if (e == NULL || e - p > 6)
     return 0;                // no decimal point in range
   strncpy(degreebuff, p, e - p); // get DDDMM
   long dddmm = atol(degreebuff);
   long degrees = (dddmm / 100);         // truncate the minutes
   long minutes = dddmm - degrees * 100; // remove the degrees
   p = e;                                // start from the decimal point
   float decminutes = atof(e); // the fraction after the decimal point
   p = strchr(p, ',') + 1;            // go to the next field

   // get the NSEW direction as a character
   char nsew = 'X';
   if (!isEmpty(p))
     nsew = *p; // field is not empty
   else
     return 0; // no direction provided

   // set the various numerical formats to their values
   long fixed = degrees * 10000000 + (minutes * 10000000) / 60 +
                (decminutes * 10000000) / 60;
   float ang = degrees * 100 + minutes + decminutes;
   float deg = fixed / (float)10000000.;
   if (nsew == 'S' ||
       nsew == 'W') { // fixed and deg are signed, but DDDMM.mmmm is not
     fixed = -fixed;
     deg = -deg;
   }

   // reject directions that are not NSEW
   if (nsew != 'N' && nsew != 'S' && nsew != 'E' && nsew != 'W')
     return 0;

   // reject angles that are out of range
   if (nsew == 'N' || nsew == 'S')
     if (abs(deg) > 90)
       return 0;
   if (abs(deg) > 180)
     return 0;

   // store in locations passed as args
   if (angle != NULL)
     *angle = ang;
   if (angle_fixed != NULL)
     *angle_fixed = fixed;
   if (angleDegrees != NULL)
     *angleDegrees = deg;
   if (dir != NULL)
     *dir = nsew;
 } else
   return 0; // no number
 return 1;
}

int parseGPS(sGPS_handle_t *hGPS){

	  char *p = hGPS->gpsBuffer; // Pointer to move through the sentence -- good parsers are
	                  // non-destructive
	  p+=3;

	  strncpy(hGPS->thisSentence, p, 3);
	  p = strchr(p, ',') + 1; // Skip to char after the next comma, then check.

	  // This may look inefficient, but an M0 will get down the list in about 1 us /
	  // strcmp()! Put the GPS sentences from Adafruit_GPS at the top to make
	  // pruning excess code easier. Otherwise, keep them alphabetical for ease of
	  // reading.
	  if (!strcmp(hGPS->thisSentence, "GGA")) { //************************************GGA
	    // Adafruit from Actisense NGW-1 from SH CP150C

	    p = strchr(p, ',') + 1; // parse time with specialized function
	    // parse out both latitude and direction, then go to next field, or fail
	    parseCoord(hGPS, p, &hGPS->latitudeDegrees, &hGPS->latitude, &hGPS->latitude_fixed, &hGPS->lat);

	    p = strchr(p, ',') + 1;
	    p = strchr(p, ',') + 1;
	    // parse out both longitude and direction, then go to next field, or fail
	    parseCoord(hGPS, p, &hGPS->longitudeDegrees, &hGPS->longitude, &hGPS->longitude_fixed, &hGPS->lon);



	  }
//	  else if (!strcmp(hGPS->thisSentence, "RMC")) { //*****************************RMC
//	    // in Adafruit from Actisense NGW-1 from SH CP150C
//
//	    p = strchr(p, ',') + 1;
//
//	    p = strchr(p, ',') + 1;
//	    // parse out both latitude and direction, then go to next field, or fail
//	    parseCoord(hGPS, p, &hGPS->latitudeDegrees, &hGPS->latitude, &hGPS->latitude_fixed, &hGPS->lat);
//
//	    p = strchr(p, ',') + 1;
//	    p = strchr(p, ',') + 1;
//	    // parse out both longitude and direction, then go to next field, or fail
//	    parseCoord(hGPS, p, &hGPS->longitudeDegrees, &hGPS->longitude, &hGPS->longitude_fixed, &hGPS->lon);
//
//	    } // skip the rest

	    else {
	      return 0; // didn't find the required sentence definition
	    }

	    return 1;

}

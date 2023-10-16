/*
 * Telemetry.h
 *
 *  Created on: Jul 26, 2020
 *      Author: Faruk
 */

#ifndef INC_TELEMETRY_H_
#define INC_TELEMETRY_H_


#include "GPS.h"

void Telemetry_send_data(sGPS_handle_t *hGPS);

void float_to_uint8(float data_float, uint8_t *data_byte);

#endif /* INC_TELEMETRY_H_ */

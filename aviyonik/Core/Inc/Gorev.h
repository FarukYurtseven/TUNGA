/*
 * Gorev.h
 *
 *  Created on: Sep 1, 2020
 *      Author: Merve
 */

#ifndef INC_GOREV_H_
#define INC_GOREV_H_

#include "Sensor.h"

_Bool Gorev1_0x1(sSensor_Data_t *Sensor_data);

_Bool Gorev1_0x2(sSensor_Data_t *Sensor_data);

_Bool Gorev2(sSensor_Data_t *Sensor_data, _Bool Gorev1);

#endif /* INC_GOREV_H_ */

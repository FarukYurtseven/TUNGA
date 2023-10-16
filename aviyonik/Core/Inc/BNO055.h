/*
 * BNO055.h
 *
 *  Created on: Jul 27, 2020
 *      Author: Faruk
 */

#ifndef INC_BNO055_H_
#define INC_BNO055_H_

#include "stm32g4xx_hal.h"

typedef struct{
	float head, roll, pitch;
	float Ax, Ay, Az;
}sBNO055_handle_t;



void BNO055_init();


void BNO055_get_euler(sBNO055_handle_t *hBNO055);

void BNO055_read_reg(uint8_t reg, uint8_t *data, uint8_t len);
void BNO055_write_reg(uint8_t reg, uint8_t *data, uint8_t len);

#endif /* INC_BNO055_H_ */

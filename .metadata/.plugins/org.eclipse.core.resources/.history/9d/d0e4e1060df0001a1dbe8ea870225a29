/*
 * BMP280.h
 *
 *  Created on: Jul 26, 2020
 *      Author: Faruk
 */

#ifndef INC_BMP280_H_
#define INC_BMP280_H_


#include "stm32g4xx_hal.h"

typedef struct{
    float Altitude;
	uint16_t    t1;
    int16_t     t2, t3;
    uint16_t    p1;
    int16_t     p2, p3, p4, p5, p6, p7, p8, p9;
    uint16_t    reserved0;
}sBMP280_handle_t;




void BMP280_init(sBMP280_handle_t *hBMP280);

void BMP280_get_calibrate(sBMP280_handle_t *hBMP280);

void BMP280_readReg(uint8_t reg, uint8_t *data, uint8_t len);
void BMP280_writeReg(uint8_t reg, uint8_t *data, uint8_t len);

void BMP280_calc_alt(sBMP280_handle_t *hBMP280);

#endif /* INC_BMP280_H_ */

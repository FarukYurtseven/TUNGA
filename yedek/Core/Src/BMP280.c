/*
 * BMP280.c
 *
 *  Created on: Jul 26, 2020
 *      Author: Faruk
 */

#include "BMP280.h"
#include "math.h"

extern I2C_HandleTypeDef hi2c1;

void BMP280_init(sBMP280_handle_t *hBMP280){
	uint8_t chip_id, reset = 0xB6;
	BMP280_writeReg(0xE0, &reset, 1);
	BMP280_readReg(0xD0, &chip_id, 1);

	HAL_Delay(500);
	uint8_t data[2];
	data[0] = 0b10110111;
	data[1] = 0b01010100;
	BMP280_writeReg(0xF4, data, 2);
	HAL_Delay(500);

	BMP280_get_calibrate(hBMP280);

	HAL_Delay(500);
}


void BMP280_get_calibrate(sBMP280_handle_t *hBMP280){


	uint8_t rx_buff[24];
	BMP280_readReg(0x88, rx_buff, 24);

	hBMP280->t1 =(rx_buff[0])+(rx_buff[1]<<8);
	hBMP280->t2 =(rx_buff[2])+(rx_buff[3]<<8);
	hBMP280->t3 =(rx_buff[4])+(rx_buff[5]<<8);
	hBMP280->p1 =(rx_buff[6])+(rx_buff[7]<<8);
	hBMP280->p2 =(rx_buff[8])+(rx_buff[9]<<8);
	hBMP280->p3 =(rx_buff[10])+(rx_buff[11]<<8);
	hBMP280->p4 =(rx_buff[12])+(rx_buff[13]<<8);
	hBMP280->p5 =(rx_buff[14])+(rx_buff[15]<<8);
	hBMP280->p6 =(rx_buff[16])+(rx_buff[17]<<8);
	hBMP280->p7 =(rx_buff[18])+(rx_buff[19]<<8);
	hBMP280->p8 =(rx_buff[20])+(rx_buff[21]<<8);
	hBMP280->p9 =(rx_buff[22])+(rx_buff[23]<<8);
}

void BMP280_calc_alt(sBMP280_handle_t *hBMP280){

	uint8_t data[6];

	BMP280_readReg(0xf7, data, 6);
	int32_t press_raw =(int32_t)((data[0] << 12) | (data[1] << 4) | (data[2] >> 4));
	int32_t	temp_raw = (int32_t)((data[3] << 12) | (data[4] << 4) | (data[5] >> 4));

	int32_t   v_t1, v_t2;
	int64_t   v_p1, v_p2, pressure;
	int32_t   t_fine;

	v_t1 = ((((temp_raw >> 3) - ((int32_t) hBMP280->t1 << 1))) * ((int32_t) hBMP280->t2)) >> 11;
	v_t2 = (((((temp_raw >> 4) - ((int32_t) hBMP280->t1)) * ((temp_raw >> 4) - ((int32_t) hBMP280->t1))) >> 12) * ((int32_t) hBMP280->t3)) >> 14;
	t_fine = v_t1 + v_t2;

	v_p1 = ((int64_t) t_fine) - 128000;
	v_p2 = v_p1 * v_p1 * (int64_t) hBMP280->p6;
	v_p2 = v_p2 + ((v_p1 * (int64_t) hBMP280->p5) << 17);
	v_p2 = v_p2 + (((int64_t) hBMP280->p4) << 35);
    v_p1 = ((v_p1 * v_p1 * (int64_t) hBMP280->p3) >> 8) + ((v_p1 * (int64_t) hBMP280->p2) << 12);
    v_p1 = (((((int64_t) 1) << 47) + v_p1)) * ((int64_t) hBMP280->p1) >> 33;

    if(v_p1 == 0) return;

    pressure = 1048576 - press_raw;
    pressure = (((pressure << 31) - v_p2) * 3125) / v_p1;
    v_p1 = (((int64_t) hBMP280->p9) * (pressure >> 13) * (pressure >> 13)) >> 25;
    v_p2 = (((int64_t) hBMP280->p8) * pressure) >> 19;
    pressure = ((pressure + v_p1 + v_p2) >> 8) + (((int64_t) hBMP280->p7) << 4);
    pressure = (pressure / 256);

    hBMP280->Altitude = 44330.0 * (1.0f - pow(pressure / 101325.0, 0.1903));
}

void BMP280_readReg(uint8_t reg, uint8_t *data, uint8_t len)
{

	HAL_I2C_Mem_Read(&hi2c1, (0x76)<<1, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);

}

void BMP280_writeReg(uint8_t reg, uint8_t *data, uint8_t len)
{

	HAL_I2C_Mem_Write(&hi2c1, (0x76)<<1, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);

}

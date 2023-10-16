/*
 * BNO055.c
 *
 *  Created on: Jul 27, 2020
 *      Author: Faruk
 */

#include "BNO055.h"

extern I2C_HandleTypeDef hi2c1;

void BNO055_init(){
	uint8_t data = 0b00001100;
	BNO055_write_reg(0x3D, &data, 1);
	HAL_Delay(200);
}

void BNO055_get_euler(sBNO055_handle_t *hBNO055){
	int16_t head_raw, roll_raw, pitch_raw;
	uint8_t data[6];

	BNO055_read_reg(0x1A, data, 6);

    head_raw = (int16_t)((data[1] << 8) | data[0]);
    roll_raw = (int16_t)((data[3] << 8) | data[2]);
    pitch_raw = (int16_t)((data[5] << 8) | data[4]);

	hBNO055->head = head_raw / 16.0f;
	hBNO055->roll = roll_raw / 16.0f;
	hBNO055->pitch = pitch_raw / 16.0f;
}


void BNO055_read_reg(uint8_t reg, uint8_t *data, uint8_t len){

	HAL_I2C_Mem_Read(&hi2c1, (0x28)<<1, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);

}
void BNO055_write_reg(uint8_t reg, uint8_t *data, uint8_t len){

	HAL_I2C_Mem_Write(&hi2c1, (0x28)<<1, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);

}

/*
 * lcd_i2c.h
 *
 *  Created on: Dec 12, 2025
 *      Author: cthanh
 */

#ifndef INC_LCD_I2C_H_
#define INC_LCD_I2C_H_

#include "global.h"

void lcd_init(void);
void lcd_clear(void);
void lcd_print_at(uint8_t row, uint8_t col, char *str);
void lcd_display_times(int lane1_sec, int lane2_sec);
void lcd_display_mode_and_tmp(int mode, int tmp_value);


#endif /* INC_LCD_I2C_H_ */

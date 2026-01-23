/*
 * lcd_i2c.c
 *
 *  Created on: Dec 12, 2025
 *      Author: HP
 */

#include "lcd_i2c.h"
#include "i2c.h"
#include <string.h>
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;

// Thử 0x27 (thường thấy). Nếu không, đổi sang 0x3F.
#define PCF8574_ADDR (0x27 << 1)

// bit masks on PCF8574 wiring used by many modules
#define LCD_BACKLIGHT 0x08
#define LCD_EN        0x04
#define LCD_RW        0x02
#define LCD_RS        0x01

static void pcf_write(uint8_t data) {
    HAL_I2C_Master_Transmit(&hi2c1, PCF8574_ADDR, &data, 1, 100);
    HAL_Delay(1);
}

static void lcd_pulse_enable(uint8_t data) {
    pcf_write(data | LCD_EN | LCD_BACKLIGHT);
    HAL_Delay(1);
    pcf_write((data & ~LCD_EN) | LCD_BACKLIGHT);
    HAL_Delay(1);
}

static void lcd_write4(uint8_t nibble, uint8_t flag_rs) {
    uint8_t data = (nibble & 0x0F) << 4;
    if(flag_rs) data |= LCD_RS;
    data |= LCD_BACKLIGHT; // giữ backlight on
    pcf_write(data);
    lcd_pulse_enable(data);
}

static void lcd_cmd(uint8_t cmd) {
    lcd_write4((cmd >> 4) & 0x0F, 0);
    lcd_write4(cmd & 0x0F, 0);
    HAL_Delay(2);
}

static void lcd_write_char(char c) {
    lcd_write4((c >> 4) & 0x0F, 1);
    lcd_write4(c & 0x0F, 1);
}

void lcd_init(void) {
    HAL_Delay(50);
    // init sequence for 4-bit via PCF8574
    pcf_write(LCD_BACKLIGHT);
    HAL_Delay(10);

    // initial 4-bit sequence
    lcd_write4(0x03, 0);
    HAL_Delay(5);
    lcd_write4(0x03, 0);
    HAL_Delay(5);
    lcd_write4(0x03, 0);
    HAL_Delay(1);
    lcd_write4(0x02, 0); // set 4-bit

    // function set: 4-bit, 2 line, 5x8
    lcd_cmd(0x28);
    // display on, cursor off, blink off
    lcd_cmd(0x0C);
    // clear
    lcd_cmd(0x01);
    HAL_Delay(2);
    // entry mode set
    lcd_cmd(0x06);
}

void lcd_clear(void) {
    lcd_cmd(0x01);
    HAL_Delay(2);
}

void lcd_print_at(uint8_t row, uint8_t col, char *str) {
    uint8_t addr;
    switch(row) {
        case 0: addr = 0x00 + col; break;
        case 1: addr = 0x40 + col; break;
        default: addr = 0x00 + col; break;
    }
    lcd_cmd(0x80 | addr);
    for (size_t i = 0; i < strlen(str); ++i) {
        lcd_write_char(str[i]);
    }
}

void lcd_display_times(int lane1_sec, int lane2_sec) {
    char buf[20];
    snprintf(buf, sizeof(buf), "Lane1_time:%02d", lane1_sec);
    lcd_print_at(0, 0, buf);
    snprintf(buf, sizeof(buf), "Lane2_time:%02d", lane2_sec);
    lcd_print_at(1, 0, buf);
}

void lcd_display_mode_and_tmp(int mode, int tmp_value) {
    char buf[20];
    snprintf(buf, sizeof(buf), "Mode:%d Tmp:%02d   ", mode, tmp_value);
    lcd_print_at(1, 0, buf);
}


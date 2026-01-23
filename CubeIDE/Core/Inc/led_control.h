/*
 * led_control.h
 *
 *  Created on: Dec 12, 2025
 *      Author: HP
 */

#ifndef INC_LED_CONTROL_H_
#define INC_LED_CONTROL_H_

#include "global.h"


#define LED_ON   GPIO_PIN_RESET
#define LED_OFF  GPIO_PIN_SET

void traffic_all_off();

/* Horizontal */
void horizontal_red_on();
void horizontal_green_on();
void horizontal_yellow_on();
void horizontal_red_off();
void horizontal_green_off();
void horizontal_yellow_off();

/* Vertical */
void vertical_red_on();
void vertical_green_on();
void vertical_yellow_on();
void vertical_red_off();
void vertical_green_off();
void vertical_yellow_off();

#endif /* INC_LED_CONTROL_H_ */

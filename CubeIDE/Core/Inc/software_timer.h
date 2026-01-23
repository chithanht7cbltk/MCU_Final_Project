/*
 * software_timer.h
 *
 *  Created on: Dec 12, 2025
 *      Author: HP
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIMER_CYCLE 10

void setTimer(int index, int duration);
int isTimerExpired(int index);
extern int timer_flag[10];

void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */

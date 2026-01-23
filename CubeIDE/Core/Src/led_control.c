#include "led_control.h"

/* NOTE:
   This implementation assumes CubeMX generated macros:
     LED_RED1_GPIO_Port, LED_RED1_Pin
     LED_GREEN1_GPIO_Port, LED_GREEN1_Pin
     LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin
     LED_RED2_GPIO_Port, LED_RED2_Pin
     LED_GREEN2_GPIO_Port, LED_GREEN2_Pin
     LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin

   If any macro name differs in your project, replace accordingly.
*/

void traffic_all_off(void)
{
    HAL_GPIO_WritePin(LED_RED1_GPIO_Port,    LED_RED1_Pin,    LED_OFF);
    HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port,  LED_GREEN1_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, LED_OFF);

    HAL_GPIO_WritePin(LED_RED2_GPIO_Port,    LED_RED2_Pin,    LED_OFF);
    HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port,  LED_GREEN2_Pin,  LED_OFF);
    HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, LED_OFF);
}

/* Horizontal (lane 1) */
void horizontal_red_on(void)    { HAL_GPIO_WritePin(LED_RED1_GPIO_Port,    LED_RED1_Pin,    LED_ON);  }
void horizontal_red_off(void)   { HAL_GPIO_WritePin(LED_RED1_GPIO_Port,    LED_RED1_Pin,    LED_OFF); }

void horizontal_green_on(void)  { HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port,  LED_GREEN1_Pin,  LED_ON);  }
void horizontal_green_off(void) { HAL_GPIO_WritePin(LED_GREEN1_GPIO_Port,  LED_GREEN1_Pin,  LED_OFF); }

void horizontal_yellow_on(void) { HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, LED_ON);  }
void horizontal_yellow_off(void){ HAL_GPIO_WritePin(LED_YELLOW1_GPIO_Port, LED_YELLOW1_Pin, LED_OFF); }

/* Vertical (lane 2) */
void vertical_red_on(void)      { HAL_GPIO_WritePin(LED_RED2_GPIO_Port,    LED_RED2_Pin,    LED_ON);  }
void vertical_red_off(void)     { HAL_GPIO_WritePin(LED_RED2_GPIO_Port,    LED_RED2_Pin,    LED_OFF); }

void vertical_green_on(void)    { HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port,  LED_GREEN2_Pin,  LED_ON);  }
void vertical_green_off(void)   { HAL_GPIO_WritePin(LED_GREEN2_GPIO_Port,  LED_GREEN2_Pin,  LED_OFF); }

void vertical_yellow_on(void)   { HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, LED_ON);  }
void vertical_yellow_off(void)  { HAL_GPIO_WritePin(LED_YELLOW2_GPIO_Port, LED_YELLOW2_Pin, LED_OFF); }

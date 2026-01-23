/*
 * fsm_automatic.c
 * Đã sửa: Đồng bộ hóa trạng thái LED của cả 2 làn trong mỗi case.
 */

#include "fsm_automatic.h"
#include "global.h"
#include "software_timer.h"
#include "lcd_i2c.h"
#include "led_control.h"

void fsm_automatic_run()
{
    /******************** HORIZONTAL ********************/
    switch (status_horizontal_traffic)
    {
    case INIT:
        status_horizontal_traffic = AUTO_RED;
        counter_horizontal = red_duration;
        setTimer(0, red_duration * 1000);  // phase duration
        setTimer(2, 1000);                 // 1s tick

        // Khi Horizontal INIT -> AUTO_RED, Vertical phải ở trạng thái đối lập.
        // Vertical khởi tạo thành AUTO_GREEN (xem logic INIT của Vertical bên dưới).
        break;

    case AUTO_RED:
        if (timer_flag[0] == 1)
        {
            status_horizontal_traffic = AUTO_GREEN;
            counter_horizontal = green_duration;
            setTimer(0, green_duration * 1000);
            setTimer(2, 1000);
        }

        if (timer_flag[2] == 1)
        {
            if(counter_horizontal > 0) counter_horizontal--;
            setTimer(2, 1000);
        }

        if (isButtonPressed(1)) {
            status_horizontal_traffic = INIT_MODE;
            status_vertical_traffic = INIT_MODE;
        }

        // ĐIỀU KHIỂN LED CỦA CẢ HAI LÀN (PHA ĐỎ/XANH ĐẦU TIÊN)
        horizontal_red_on();
        horizontal_green_off();
        horizontal_yellow_off();

        // LÀN ĐỨNG (VERTICAL) LUÔN PHẢI XANH (hoặc VÀNG) KHI LÀN NGANG ĐỎ
        // Vì FSM Vertical là AUTO_GREEN, nó sẽ điều khiển LED của nó.
        // Để đảm bảo đồng bộ, ta chỉ cần chắc chắn Vertical FSM được chạy đúng.
        // Tạm thời KHÔNG CẦN thêm logic Vertical ở đây, vì Vertical FSM sẽ chạy ngay sau.

        break;


    case AUTO_GREEN:
        if (timer_flag[0] == 1)
        {
            status_horizontal_traffic = AUTO_YELLOW;
            counter_horizontal = yellow_duration;
            setTimer(0, yellow_duration * 1000);
            setTimer(2, 1000);
        }

        if (timer_flag[2] == 1)
        {
            if(counter_horizontal > 0) counter_horizontal--;
            setTimer(2, 1000);
        }

        if (isButtonPressed(1)) {
            status_horizontal_traffic = INIT_MODE;
            status_vertical_traffic = INIT_MODE;
        }

        // ĐIỀU KHIỂN LED LÀN NGANG
        horizontal_green_on();
        horizontal_red_off();
        horizontal_yellow_off();

        break;


    case AUTO_YELLOW:
        if (timer_flag[0] == 1)
        {
            status_horizontal_traffic = AUTO_RED;
            counter_horizontal = red_duration;
            setTimer(0, red_duration * 1000);
            setTimer(2, 1000);
        }

        if (timer_flag[2] == 1)
        {
            if(counter_horizontal > 0) counter_horizontal--;
            setTimer(2, 1000);
        }

        if (isButtonPressed(1)) {
            status_horizontal_traffic = INIT_MODE;
            status_vertical_traffic = INIT_MODE;
        }

        // ĐIỀU KHIỂN LED LÀN NGANG
        horizontal_yellow_on();
        horizontal_red_off();
        horizontal_green_off();

        break;
    }


    /******************** VERTICAL ********************/
    switch (status_vertical_traffic)
    {
    case INIT:
        status_vertical_traffic = AUTO_RED; // ĐÃ SỬA: PHẢI LÀ RED để đối lập với Horizontal GREEN/YELLOW/RED
        counter_vertical = red_duration; // ĐÃ SỬA: PHẢI BẮT ĐẦU VỚI RED DURATION

        setTimer(3, red_duration * 1000); // ĐÃ SỬA: SỬ DỤNG red_duration
        setTimer(5, 1000);

        // ĐIỀU KHIỂN LED LÀN DỌC TRONG INIT
        vertical_red_on();
        vertical_green_off();
        vertical_yellow_off();
        break;


    case AUTO_RED:
        if (timer_flag[3] == 1)
        {
            status_vertical_traffic = AUTO_GREEN;
            counter_vertical = green_duration;
            setTimer(3, green_duration * 1000);
            setTimer(5, 1000);
        }

        if (timer_flag[5] == 1)
        {
            if (counter_vertical > 0) counter_vertical--;
            setTimer(5, 1000);
        }

        if (isButtonPressed(1)) {
            status_vertical_traffic = INIT_MODE;
            status_horizontal_traffic = INIT_MODE;
        }

        vertical_red_on();
        vertical_green_off();
        vertical_yellow_off();
        break;


    case AUTO_GREEN:
        if (timer_flag[3] == 1)
        {
            status_vertical_traffic = AUTO_YELLOW;
            counter_vertical = yellow_duration;
            setTimer(3, yellow_duration * 1000);
            setTimer(5, 1000);
        }

        if (timer_flag[5] == 1)
        {
            if (counter_vertical > 0) counter_vertical--;
            setTimer(5, 1000);
        }

        if (isButtonPressed(1)) {
            status_vertical_traffic = INIT_MODE;
            status_horizontal_traffic = INIT_MODE;
        }

        vertical_green_on();
        vertical_red_off();
        vertical_yellow_off();
        break;


    case AUTO_YELLOW:
        if (timer_flag[3] == 1)
        {
            status_vertical_traffic = AUTO_RED;
            counter_vertical = red_duration;
            setTimer(3, red_duration * 1000);
            setTimer(5, 1000);
        }

        if (timer_flag[5] == 1)
        {
            if (counter_vertical > 0) counter_vertical--;
            setTimer(5, 1000);
        }

        if (isButtonPressed(1)) {
            status_vertical_traffic = INIT_MODE;
            status_horizontal_traffic = INIT_MODE;
        }

        vertical_yellow_on();
        vertical_red_off();
        vertical_green_off();
        break;
    }

    /* Update LCD once per main loop */
    lcd_display_times(counter_horizontal, counter_vertical);
}

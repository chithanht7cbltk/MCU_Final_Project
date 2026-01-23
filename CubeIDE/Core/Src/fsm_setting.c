/*
 * fsm_setting.c
 * Đã sửa: Khắc phục lỗi biến 'vertical_duration' còn sót lại ở MODE3 và MODE4.
 */

#include "fsm_setting.h"
#include "lcd_i2c.h"
#include "software_timer.h"
#include "global.h"
#include "traffic.h"

void fsm_setting_run()
{
    switch (status_horizontal_traffic)
    {
    case INIT_MODE:
        status_horizontal_traffic = MODE2;
        clear_all();
        setTimer(1, 10000); // timeout đổi mode (10s)
        setTimer(2, 250);
        setTimer(3, 250);
        set_tmp_duration();
        // show initial mode on LCD
        lcd_display_mode_and_tmp(2, red_duration_tmp);
        break;
    case MODE1:
        if (timer_flag[0] == 1)
        {
            status_horizontal_traffic = INIT;
            status_vertical_traffic = INIT;
        }
        if (isButtonPressed(1) == 1)
        {
            status_horizontal_traffic = MODE2;
            setTimer(1, 10000);
            setTimer(2, 250);
            setTimer(3, 250);
        }
        set_tmp_duration();
        break;
    case MODE2:
        enable_vertical(0);
        // show mode and tmp on LCD
        lcd_display_mode_and_tmp(2, red_duration_tmp);
        counter_horizontal = red_duration_tmp;
        // update lcd times as preview
        lcd_display_times(red_duration_tmp, counter_vertical);

        if (timer_flag[3] == 1)
        {
            // not using 7seg scanning; keep for compatibility
            setTimer(3, 250);
        }

        if (timer_flag[2] == 1)
        {
            custom_red_mode(); // blink red leds
            setTimer(2, 250);
        }
        if (isButtonPressed(1) == 1)
        {
            status_horizontal_traffic = MODE3;
            setTimer(1, 10000);
        }
        if (isButtonPressed(2) == 1)
        {
            red_duration_tmp++;
            if (red_duration_tmp > 99)
                red_duration_tmp = 0;
            setTimer(1, 10000);
            // update lcd preview
            lcd_display_mode_and_tmp(2, red_duration_tmp);
            lcd_display_times(red_duration_tmp, counter_vertical);
        }

        // auto tăng liên tục khi giữ >1s (mỗi 0.5s)
        if (isButtonLongPressed(2))
        {
            red_duration_tmp++;
            if (red_duration_tmp > 99) red_duration_tmp = 0;
            lcd_display_mode_and_tmp(2, red_duration_tmp);
            lcd_display_times(red_duration_tmp, counter_vertical);
        }

        if (isButtonPressed(3) == 1)
        {
            red_duration = red_duration_tmp;
            status_horizontal_traffic = MODE1;
            clear_all();
            // ĐÃ SỬA: Dùng red_duration cho Lane 2 (mặc định)
            lcd_display_times(red_duration, red_duration);
            setTimer(0, 50); // 0.5s wait before auto (50 * 10ms)
        }
        if (timer_flag[1] == 1)
        {
            status_horizontal_traffic = MODE1;
        }
        break;

    case MODE3:
        enable_vertical(0);
        lcd_display_mode_and_tmp(3, green_duration_tmp);
        counter_horizontal = green_duration_tmp;
        lcd_display_times(counter_horizontal, counter_vertical);

        if (timer_flag[3] == 1) { setTimer(3, 250); }

        if (timer_flag[2] == 1) { custom_green_mode(); setTimer(2, 250); }

        if (isButtonPressed(1) == 1) {
            status_horizontal_traffic = MODE4;
            setTimer(1, 10000);
        }
        if (isButtonPressed(2) == 1) {
            green_duration_tmp++;
            if (green_duration_tmp > 99) green_duration_tmp = 0;
            lcd_display_mode_and_tmp(3, green_duration_tmp);
            lcd_display_times(green_duration_tmp, counter_vertical);
        }
        if (isButtonLongPressed(2)) {
            green_duration_tmp++;
            if (green_duration_tmp > 99) green_duration_tmp = 0;
            lcd_display_mode_and_tmp(3, green_duration_tmp);
            lcd_display_times(green_duration_tmp, counter_vertical);
        }
        if (isButtonPressed(3) == 1)
        {
            green_duration = green_duration_tmp;
            status_horizontal_traffic = MODE1;
            clear_all();
            // ĐÃ SỬA: Dùng red_duration cho Lane 2 (mặc định)
            lcd_display_times(green_duration, red_duration); // KHẮC PHỤC LỖI BIẾN Ở ĐÂY
            setTimer(0, 50);
        }
        if (timer_flag[1] == 1) {
            status_horizontal_traffic = MODE1;
        }
        break;

    case MODE4:
        enable_vertical(0);
        lcd_display_mode_and_tmp(4, yellow_duration_tmp);
        counter_horizontal = yellow_duration_tmp;
        lcd_display_times(counter_horizontal, counter_vertical);

        if (timer_flag[3] == 1) { setTimer(3, 250); }

        if (timer_flag[2] == 1) { custom_yellow_mode(); setTimer(2, 250); }

        if (isButtonPressed(1) == 1) {
            status_horizontal_traffic = MODE1;
            clear_all();
            setTimer(0, 50);
        }
        if (isButtonPressed(2) == 1) {
            yellow_duration_tmp++;
            if (yellow_duration_tmp > 99) yellow_duration_tmp = 0;
            lcd_display_mode_and_tmp(4, yellow_duration_tmp);
            lcd_display_times(yellow_duration_tmp, counter_vertical);
        }
        if (isButtonLongPressed(2)) {
            yellow_duration_tmp++;
            if (yellow_duration_tmp > 99) yellow_duration_tmp = 0;
            lcd_display_mode_and_tmp(4, yellow_duration_tmp);
            lcd_display_times(yellow_duration_tmp, counter_vertical);
        }
        if (isButtonPressed(3) == 1)
        {
            yellow_duration = yellow_duration_tmp;
            status_horizontal_traffic = MODE1;
            clear_all();
            // ĐÃ SỬA: Dùng red_duration cho Lane 2 (mặc định)
            lcd_display_times(yellow_duration, red_duration); // KHẮC PHỤC LỖI BIẾN Ở ĐÂY
            setTimer(0, 50);
        }
        if (timer_flag[1] == 1) {
            status_horizontal_traffic = MODE1;
        }
        break;

    default:
        break;
    }
}

#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && defined(ENABLE_RGB_MATRIX_CUSTOM_DIGITAL_RAIN)
RGB_MATRIX_EFFECT(CUSTOM_DIGITAL_RAIN)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#        ifndef RGB_CUSTOM_DIGITAL_RAIN_DROPS
// lower the number for denser effect/wider keyboard
#            define RGB_CUSTOM_DIGITAL_RAIN_DROPS 24
#        endif

bool CUSTOM_DIGITAL_RAIN(effect_params_t* params) {
    // algorithm ported from https://github.com/tremby/Kaleidoscope-LEDEffect-DigitalRain
    uint8_t speed = rgb_matrix_config.speed > 0 ? rgb_matrix_config.speed : 1;
    HSV hsv = rgb_matrix_config.hsv;
    uint16_t drop_ticks                 = 1792 / speed;
    const uint8_t pure_green_intensity = 0xd0;
    const uint8_t max_brightness_boost = 0xc0;
    const uint8_t max_intensity        = 0xff;

    static uint8_t drop = 0;

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
        memset(g_rgb_frame_buffer, 0, sizeof(g_rgb_frame_buffer));
        drop = 0;
    }

    if (drop_ticks < 1) {
        drop_ticks = 1;
    } else if (drop_ticks > 200) {
        drop_ticks = 200;
    }

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            if (row == 0 && drop == 0 && rand() < RAND_MAX / RGB_CUSTOM_DIGITAL_RAIN_DROPS) {
                // top row, pixels have just fallen and we're
                // making a new rain drop in this column
                g_rgb_frame_buffer[row][col] = max_intensity;
            } else if (g_rgb_frame_buffer[row][col] > 0 && g_rgb_frame_buffer[row][col] < max_intensity) {
                // neither fully bright nor dark, decay it
                if (g_rgb_frame_buffer[row][col] < 3) {
                    g_rgb_frame_buffer[row][col] = 0;
                } else {
                    g_rgb_frame_buffer[row][col] -= 3;
                }
            }
            // set the pixel colour
            uint8_t led[LED_HITS_TO_REMEMBER];
            uint8_t led_count = rgb_matrix_map_row_column_to_led(row, col, led);

            // TODO: multiple leds are supported mapped to the same row/column
            if (led_count > 0) {
                if (g_rgb_frame_buffer[row][col] > pure_green_intensity) {
                    const uint8_t boost = (uint8_t)((uint16_t)max_brightness_boost * (g_rgb_frame_buffer[row][col] - pure_green_intensity) / (max_intensity - pure_green_intensity));
                    rgb_matrix_set_color(led[0], boost, max_intensity, boost);
                } else {
                    hsv.v = (uint8_t)((uint16_t)hsv.v * g_rgb_frame_buffer[row][col] / pure_green_intensity);
                    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
                    rgb_matrix_set_color(led[0], rgb.r, rgb.g, rgb.b);
                }
            }
        }
    }

    if (++drop > drop_ticks) {
        // reset drop timer
        drop = 0;
        for (uint8_t row = MATRIX_ROWS - 1; row > 0; row--) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                // if ths is on the bottom row and bright allow decay
                if (row == MATRIX_ROWS - 1 && g_rgb_frame_buffer[row][col] == max_intensity) {
                    g_rgb_frame_buffer[row][col]--;
                }
                // check if the pixel above is bright
                if (g_rgb_frame_buffer[row - 1][col] == max_intensity) {
                    // allow old bright pixel to decay
                    g_rgb_frame_buffer[row - 1][col]--;
                    // make this pixel bright
                    g_rgb_frame_buffer[row][col] = max_intensity;
                }
            }
        }
    }
    return false;
}

#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS) && !defined(ENABLE_RGB_MATRIX_CUSTOM_DIGITAL_RAIN)

/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

#undef VENDOR_ID
#undef PRODUCT_ID
#undef MANUFACTURER
#undef PRODUCT

#define VENDOR_ID  0x6969
#define PRODUCT_ID 0x0420

#define MANUFACTURER devplayer0
#define PRODUCT EpicBoard

#define EE_HANDS

#define UNICODE_SELECTED_MODES UC_MAC, UC_LNX, UC_WIN

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 150
#endif

#ifdef RGB_MATRIX_ENABLE
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
    #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#endif

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD_PER_KEY
#define TAPPING_TERM 180

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK

#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTIONS       { 4 }
#define ENCODER_RESOLUTIONS_RIGHT { 2 }

#define MOUSEKEY_INTERVAL 30
#define MOUSEKEY_DELAY 200
#define MOUSEKEY_TIME_TO_MAX 30

#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_HIDRGB

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
#include QMK_KEYBOARD_H
#include "split_util.h"
#include "transactions.h"

enum layers {
    _COLEMAK_DH = 0,
    _NAV,
    _SYM,
    _AUX,
    _ADJUST,

    _GAME,
    _GAME_EXTRA,
};

#define KC_EURO  UC(0x20AC)
#define KC_PUND  UC(0x00A3)

// Aliases for readability
#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define AUX      MO(_AUX)
#define ADJUST   MO(_ADJUST)

#define SYM_SPC  LT(_SYM, KC_SPACE)
#define NAV_BKSP LT(_NAV, KC_BSPACE)
#define AUX_TAB  LT(_AUX, KC_TAB)


// Mod-taps
#define MT_A MT(MOD_LALT, KC_A)
#define MT_R MT(MOD_LCTL, KC_R)
#define MT_S MT(MOD_LGUI, KC_S)
#define MT_T MT(MOD_LSFT, KC_T)

#define MT_O MT(MOD_RALT, KC_O)
#define MT_I MT(MOD_RCTL, KC_I)
#define MT_E MT(MOD_RGUI, KC_E)
#define MT_N MT(MOD_RSFT, KC_N)

#define GO_GME  TO(_GAME)
#define MO_GEXT MO(_GAME_EXTRA)
#define NO_GME  TO(_COLEMAK_DH)

enum tapdance {
    TD_GO_GAME,
    TD_NO_GAME,
};

void dance_go_game(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_BSLS);
    } else if (state->count == 3) {
        layer_move(_GAME);
    } else {
        reset_tap_dance(state);
    }
}

void dance_no_game(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_LCTL);
    } else if (state->count == 3) {
        layer_clear();
    } else {
        reset_tap_dance(state);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_GO_GAME] = ACTION_TAP_DANCE_FN(dance_go_game),
    [TD_NO_GAME] = ACTION_TAP_DANCE_FN(dance_no_game),
};

#define BSLS_GME TD(TD_GO_GAME)
#define CTL_NGM  TD(TD_NO_GAME)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |    `   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | '  " |  =  +  |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   Esc  | A+⎇ |  R+⎈ |  S+◆ |  T+⇧ |   G  |                              |   M  |  N+⇧ |  E+⎈ |  I+◆ | O+⎇ |  ;  :  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | /+Game |   Z  |   X  |   C  |   D  |   V  |      |      |  |      |      |   K  |   H  | ,  < | . >  | /  ? |  -  _  |
 * `----------------------+------+------+------|      |      |  |      |      |------+------+------+----------------------'
 *                        | Play/| ScLck|CapsLk| Space| Nav  |  | Enter|Nav/Bk|  Del | RAlt |  Adj |
 *                        | Pause|      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_DH] = LAYOUT(
      KC_GRV  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                        KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_QUOT, KC_EQUAL,
      KC_ESC  , MT_A ,  MT_R   ,  MT_S  ,   MT_T ,   KC_G ,                                        KC_M,   MT_N ,  MT_E ,   MT_I ,  MT_O , KC_SCLN,
      BSLS_GME, KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V , XXXXXXX,XXXXXXX,     XXXXXXX, XXXXXXX, KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_MINUS,
                                 KC_MPLY, KC_SCRL, KC_CAPS, SYM_SPC,AUX_TAB,      KC_ENT, NAV_BKSP,KC_DEL, KC_RALT, ADJUST
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |  M↑  |      |      |                              |      |  M1  |   ↑  |  M2  |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  Esc |  M←  |  M↓  |  M→  |      |                              |      |  ←   |   ↓  |   →  |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------|      |      |  |      |      |------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, _______, _______, KC_MS_U, _______, _______,                                     _______, KC_BTN1, KC_UP,   KC_BTN2, _______, _______,
      _______,  KC_ESC, KC_MS_L, KC_MS_D, KC_MS_R, _______,                                     _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  $   |  :   |  {   |  }   |  ~   |                              |   +  |  7   |  8   |  9   |  *   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  !   |  ;   |  (   |  )   |  _   |                              |   -  |  4   |  5   |  6   |  =   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  `   |  #   |  [   |  ]   |  &   |      |      |  |      |      |   |  |  1   |  2   |  3   |  %   |        |
 * `----------------------+------+------+------|      |      |  |      |      |------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |   0  |  .   |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
      _______,  KC_DLR, KC_COLN, KC_LCBR, KC_RCBR, KC_TILD,                                     KC_PLUS,    KC_7,    KC_8,    KC_9, KC_ASTR, _______,
      _______, KC_EXLM, KC_SCLN, KC_LPRN, KC_RPRN, KC_UNDS,                                     KC_MINS,    KC_4,    KC_5,    KC_6,  KC_EQL, _______,
      _______,KC_GRAVE, KC_HASH, KC_LBRC, KC_RBRC, KC_AMPR, _______, _______, _______, _______, KC_PIPE,    KC_1,    KC_2,    KC_3, KC_PERC, _______,
                                 _______, _______, _______, _______, _______, _______, _______,    KC_0,  KC_DOT, _______
    ),

/*
 * Aux Layer: Function keys and extra symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   F1   |  F2  |  F3  |  F4  |  F5  |  F6  |                              |  F7  |  F8  |  F9  |  F10 |  F11 |  F12   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |   €  |   ^  |   \  |   @  |      |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |   £  |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------|      |      |  |      |      |------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_AUX] = LAYOUT(
       KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,                                      KC_F7 ,  KC_F8 ,  KC_F9 ,  KC_F10,  KC_F11,  KC_F12,
      _______, KC_EURO, KC_CIRC, KC_BSLS,  KC_AT , _______,                                     _______, _______, _______, _______, _______, _______,
      _______, KC_PUND, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Adjust Layer: Default layer settings, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |UC WIN|                              | Game |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |   TOG  | SAI  | HUI  | VAI  | MOD  |UC LNX|                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        | SAD  | HUD  | VAD  | RMOD |UC MAC|      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------|      |      |  |      |      |------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______, _______, _______, _______, _______, UC_M_WI,                                     GO_GME, _______, _______, _______,  _______, _______,
      RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI,  RGB_MOD,UC_M_LN,                                    _______, _______, _______, _______,  _______, _______,
      _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,UC_M_MA,_______, _______, _______, _______, _______, _______, _______, _______,  _______, EEP_RST,
                                 _______, _______, _______,_______, _______, _______, _______, _______, _______, _______
    ),

/*
 * Gaming
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |   M    | Tab  |  Q   |  W   |  E   |  R   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  ESC   | Shift|  A   |  S   |  D   |  F   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |Ctrl+Def|  Z   |  X   |  G   |  V   |  I   |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------|      |      |  |      |      |------+------+------+----------------------'
 *                        |      |  B   |  C   |Space | GEXT |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME] = LAYOUT(
         KC_M,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       KC_ESC, KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,                                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      CTL_NGM,    KC_Z,    KC_X,    KC_G,    KC_V,    KC_I, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX,    KC_B,    KC_C,  KC_SPC, MO_GEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

/*
 * Gaming extra
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  T   |  4   |      |  3   |  U   |                              |Leave |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  Y   |  1   |      |  2   |  H   |                              |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  5   |  6   |  7   |  8   |  9   |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------|      |      |  |      |      |------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_GAME_EXTRA] = LAYOUT(
      _______,    KC_T,    KC_4, _______,    KC_3,    KC_U,                                      NO_GME, _______, _______, _______, _______, _______,
      _______,    KC_Y,    KC_1, _______,    KC_2,    KC_H,                                     _______, _______, _______, _______, _______, _______,
      _______,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------|      |      |  |      |      |------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (IS_LAYER_OFF(_SYM)) {
            // Page up/Page down
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        } else {
            if (clockwise) {
                tap_code(KC_MEDIA_NEXT_TRACK);
            } else {
                tap_code(KC_MEDIA_PREV_TRACK);
            }
        }
    }

    return false;
}
#endif

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    if (isLeftHand) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM qmk_logo[] = {
            0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
            0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
            0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
        // clang-format on

        oled_write_P(qmk_logo, false);
        oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _COLEMAK_DH:
                oled_write_P(PSTR("Colemak-DH\n"), false);
                break;
            case _NAV:
                oled_write_P(PSTR("NAV\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("SYM\n"), false);
                break;
            case _AUX:
                oled_write_P(PSTR("AUX\n"), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            case _GAME:
                oled_write_P(PSTR("Game\n"), false);
                break;
            case _GAME_EXTRA:
                oled_write_P(PSTR("Game extra\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }

        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_P(led_usb_state.num_lock    ? PSTR("NUMLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.caps_lock   ? PSTR("CAPLCK ") : PSTR("       "), false);
        oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }

    return false;
}
#endif

#ifdef RAW_ENABLE
#include "raw_hid.h"
#include "usb_descriptor.h"
#include "lufa.h"

#ifdef RGB_MATRIX_ENABLE
void apply_hidrgb(const uint8_t *data, uint8_t length) {
    size_t count = (data[1] * 4) + 2 > length ? 7 : data[1];
    for (size_t i = 0; i < count; i++) {
        size_t o = (i * 4) + 2;
        rgb_matrix_set_color(data[o], data[o + 1], data[o + 2], data[o + 3]);
    }
}

void user_sync_hidrgb_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    apply_hidrgb(in_data, in_buflen);
}
#endif

void raw_hid_receive(uint8_t *data, uint8_t length) {
    switch (data[0]) {
#ifdef RGB_MATRIX_ENABLE
    case 0: {
        rgb_matrix_set_flags(LED_FLAG_NONE);

        data[0] = DRIVER_LED_TOTAL;
        raw_hid_send(data, length);

        for (size_t i = 0; i < DRIVER_LED_TOTAL; i++) {
            data[0] = g_led_config.point[i].x;
            data[1] = g_led_config.point[i].y;

            // TODO: Make LUFA-specific code more generic
            uint8_t ep = Endpoint_GetCurrentEndpoint();
            Endpoint_SelectEndpoint(RAW_IN_EPNUM);
            while (!Endpoint_IsINReady());
            Endpoint_SelectEndpoint(ep);

            raw_hid_send(data, length);
        }
        break;
    }
    case 1: {
        apply_hidrgb(data, length);
        transaction_rpc_send(USER_SYNC_HIDRGB, length, data);
        break;
    }
#endif
    }
}
#endif

void keyboard_post_init_user(void) {
    debug_enable = false;
#if defined(RAW_ENABLE) && defined(RGB_MATRIX_ENABLE)
    transaction_register_rpc(USER_SYNC_HIDRGB, user_sync_hidrgb_slave_handler);
#endif
}

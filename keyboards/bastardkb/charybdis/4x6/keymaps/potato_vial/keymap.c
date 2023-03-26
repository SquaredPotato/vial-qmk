/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_POINTER,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJUST,
    LAYER_QWERTY,
    LAYER_GAME,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

/** \brief Set autoshift tap duration in milliseconds */
#define AUTO_SHIFT_TIMEOUT 150

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1300
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD

#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 3
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_charybdis_4x6(
  // ╭───────────────────────────────────────────────────────╮ ╭─────────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,     KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├───────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────┤
        KC_TAB,KC_COMMA,   KC_DOT,    KC_P,    KC_Y,    KC_F,       KC_G,    KC_C,    KC_R,    KC_L, KC_BSPC, KC_BSLS,
  // ├───────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────┤
LSFT_T(KC_CLCK),   KC_A,     KC_O,    KC_E,    KC_U,    KC_I,       KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_QUOT,
  // ├───────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────┤
       KC_LCTL,    PT_Z,     KC_Q,    KC_J,    KC_K,    KC_X,       KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_MINUS,
  // ╰───────────────────────────────────────────────────────┤ ├─────────────────────────────────────────────────────────╯
LT(LAYER_RAISE, KC_ENT),KC_LGUI,LT(LAYER_ADJUST, XXXXXXX),     KC_BTN1,  LT(LAYER_LOWER, KC_SPC),
                        LT(LAYER_LOWER, KC_DEL), KC_LALT,      LT(LAYER_RAISE, KC_DEL)
  //                             ╰───────────────────────────╯ ╰──────────────────╯
  ),
  [LAYER_POINTER] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       KC_ESC , XXXXXXX, XXXXXXX, XXXXXXX, EEPROM_RESET, QK_BOOT,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EEPROM_RESET, QK_BOOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
LSFT_T(KC_CLCK), KC_LGUI, DRGSCRL, SNIPING, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX,  KC_LALT,KC_LCTRL, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN1, KC_BTN2,
                                           XXXXXXX, KC_BTN2,    KC_BTN3
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
  [LAYER_LOWER] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_EXLM,   KC_AT, KC_LCBR, KC_RCBR, KC_PIPE,    _______, _______, _______, _______, KC_RBRC, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
LSFT_T(KC_CLCK), KC_HASH,  KC_DLR, KC_LPRN, KC_RPRN,  KC_GRV,    KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_PEQL,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,    KC_AMPR,  KC_EQL, KC_COMM,  KC_DOT, KC_SLSH, KC_PDOT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                            XXXXXXX, XXXXXXX, TO(LAYER_GAME), TO(LAYER_QWERTY), MO(LAYER_ADJUST),
                                     XXXXXXX, TO(LAYER_BASE), TO(LAYER_BASE)
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
  [LAYER_RAISE] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_TAB, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT, KC_MPLY, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT,    XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       MOD_LCTL,KC_MPRV, KC_HOME, KC_PGUP, KC_PGDN,  KC_END,    XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, XXXXXXX,    XXXXXXX, LT(LAYER_ADJUST, KC_SCOLON),
                                  MO(LAYER_ADJUST), _______,    MO(LAYER_ADJUST)
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
  [LAYER_ADJUST] = LAYOUT_charybdis_4x6(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
      KC_POWER, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
LSFT_T(KC_CLCK), XXXXXXX, RGB_MOD, RGB_SAI, RGB_VAI, RGB_HUI,    XXXXXXX, XXXXXXX, XXXXXXX,  KC_F11,  KC_F12, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
      MOD_LCTL, XXXXXXX, RGB_TOG, RGB_SAD, RGB_VAD, RGB_HUD,    _______, EEP_RST, XXXXXXX, XXXXXXX, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  XXXXXXX, KC_LGUI, XXXXXXX,     KC_DEL, KC_SPC,
                                           KC_LALT, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
    [LAYER_QWERTY] = LAYOUT_charybdis_4x6(
  // ╭───────────────────────────────────────────────────────╮              ╭─────────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,     KC_2,    KC_3,    KC_4,    KC_5,                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├───────────────────────────────────────────────────────┤              ├─────────────────────────────────────────────────────────┤
        KC_TAB,KC_COMMA,   KC_DOT,  KC_P,      KC_Y,    KC_F,                    KC_G,    KC_C,    KC_R,    KC_L, KC_BSPC, KC_BSLS,
  // ├───────────────────────────────────────────────────────┤              ├─────────────────────────────────────────────────────────┤
LSFT_T(KC_CLCK),   KC_A,     KC_O,    KC_E,    KC_U,    KC_I,                    KC_D,    KC_H,    KC_T,    KC_N,    KC_S, KC_QUOT,
  // ├───────────────────────────────────────────────────────┤              ├─────────────────────────────────────────────────────────┤
       KC_LCTL,    KC_Z,     KC_Q,    KC_J,    KC_K,    KC_X,                    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, KC_MINUS,
  // ╰───────────────────────────────────────────────────────┤              ├─────────────────────────────────────────────────────────╯
LT(LAYER_RAISE, KC_ENT),LT(LAYER_LOWER, KC_LGUI),LT(LAYER_ADJUST, XXXXXXX),   LT(LAYER_RAISE, KC_DEL),  LT(LAYER_LOWER, KC_SPC),
                                            KC_LALT, KC_BSPC,                 KC_BTN1
  //                             ╰───────────────────────────╯              ╰──────────────────╯
  ),
    [LAYER_GAME] = LAYOUT_charybdis_4x6(
  // ╭───────────────────────────────────────────────────────╮              ╭─────────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,     KC_2,    KC_3,    KC_4,    KC_5,                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_PSCR,
  // ├───────────────────────────────────────────────────────┤              ├─────────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  // ├───────────────────────────────────────────────────────┤              ├─────────────────────────────────────────────────────────┤
LSFT_T(KC_CLCK),   KC_A,     KC_S,    KC_D,    KC_U,    KC_G,                    KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
  // ├───────────────────────────────────────────────────────┤              ├─────────────────────────────────────────────────────────┤
       KC_LCTL,    KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,                    KC_B,    KC_N,    KC_M,KC_COMMA,  KC_DOT, KC_MINUS,
  // ╰───────────────────────────────────────────────────────┤              ├─────────────────────────────────────────────────────────╯
LT(LAYER_RAISE, KC_ENT),LT(LAYER_LOWER, KC_LGUI),LT(LAYER_ADJUST, XXXXXXX),   LT(LAYER_RAISE, KC_DEL),  LT(LAYER_LOWER, KC_SPC),
                                            KC_LALT, KC_BSPC,                 KC_BTN1
  //                             ╰───────────────────────────╯              ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_sethsv_noeeprom(HSV_CYAN);
        //rgb_matrix_mode_noeeprom(RGB_MATRIX_STARTUP_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(1);
    rgblight_setrgb_red();
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
}

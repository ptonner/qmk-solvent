/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "flow.h"

// Layers
enum layers {
    DEF,
    MED,
    NAV,
    MOU,
    SYM,
    NUM,
    FUN,
    MISC
};


// Flow

enum custom_keycodes {
  TM_NEXT = SAFE_RANGE,
  TM_PREV,
  TM_LEFT,
  TM_RIGHT,
  TM_NEW,
  TM_SLCT,
  TM_SRCH,
  TM_URL,
  OS_MISC,
  OS_TMUX,
  OS_FUNC,
  LT_OSLNX,
};

// flow_config should correspond to following format:
// * layer keycode
// * modifier keycode
const uint16_t flow_config[FLOW_COUNT][2] = {
    {LT_NAV, KC_LALT},
    {LT_NAV, KC_LGUI},
    {LT_NAV, KC_LCTL},
    {LT_NAV, KC_LSFT},
    {LT_SYM, KC_LCTL},
    {LT_SYM, KC_LGUI},
    {LT_SYM, KC_LALT},
};


// for layers configuration follow this format:
// * custom layer key
// * layer name
const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {OS_MISC, MISC},
};

// Add following to handle flow

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;
    return true;
}

void matrix_scan_user(void) {
    flow_matrix_scan();
}

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           LT_MED,  LT_NAV,  LT_MOU,     LT_SYM,  LT_NUM,  LT_FUN
                                      //`--------------------------'  `--------------------------'

  ),

    // NOTE: this is currently included just to enable compilation
    // with flow layers, which require at least one to avoid compile
    // time errors
    [MISC] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     XXXXXXX  ,XXX   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                 KC_BRID ,KC_BRIU ,KC_PSCR ,XXXXXXX ,XXX , XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX  ,XXXXXXX ,XXXXXXX ,XXX   ,LT_OSLNX,XXXXXXX ,                 XXXXXXX  ,KC_MPRV ,KC_MPLY ,KC_MNXT ,XXXXXXX ,XXX ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                 XXXXXXX  ,KC_VOLD ,KC_VOLU ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                            XXXXXXX  ,XXXXXXX ,    XXXXXXX ,        XXXXXXX ,    XXXXXXX, XXXXXXX
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  )
};

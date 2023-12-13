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
  // Oneshot
  OS_DEF,
  OS_MED,
  OS_NAV,
  OS_MOU,
  OS_SYM,
  OS_NUM,
  OS_FUN,
  OS_MISC,
  OS_TMUX,
  OS_FUNC,
  // LT_OSLNX,
};

// flow_config should correspond to following format:
// * layer keycode
// * modifier keycode
const uint16_t flow_config[FLOW_COUNT][2] = {

    {L_NUM, KC_LGUI},
    {L_NUM, KC_LALT},
    {L_NUM, KC_LCTL},
    {L_NUM, KC_LSFT},

    {L_NAV, KC_LGUI},
    {L_NAV, KC_LALT},
    {L_NAV, KC_LCTL},
    {L_NAV, KC_LSFT},

    {L_SYM, KC_LGUI},
    {L_SYM, KC_LALT},
    {L_SYM, KC_LCTL},
    {L_SYM, KC_LSFT},

};


// for layers configuration follow this format:
// * custom layer key
// * layer name
const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2] = {
    {OS_MED, MED},
    {OS_NAV, NAV},
    {OS_MOU, MOU},
    {OS_SYM, SYM},
    {OS_NUM, NUM},
    {OS_FUN, FUN},
};

// Add following to handle flow

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!update_flow(keycode, record->event.pressed, record->event.key)) return false;
    return true;
}

void matrix_scan_user(void) {
    flow_matrix_scan();
}

// NOTE: miryoku thumbs:
// LT(U_MEDIA,KC_ESC),LT( XXXV,KC_SPC),LT(U_MOUSE,KC_TAB), LT(U_SYM,KC_ENT),LT(U_NUM,KC_BSPC),LT(U_FUN,KC_DEL)
// KC_ESC, KC_SPC, KC_TAB, KC_ENT, KC_BSPC, KC_DEL

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_split_3x6_3(
      XXXXXXX, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P,  XXXXXXX,
      XXXXXXX, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, XXXXXXX,
      XXXXXXX, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, XXXXXXX,
                                           OS_MED,  OS_NAV,  OS_MOU,     OS_SYM,  OS_NUM,  OS_FUN
                                      //`--------------------------'  `--------------------------'
  ),

    [MED] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXX, XXX, XXX, XXX, XXX, XXX, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG, XXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXX, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, XXX, XXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXX, XXX, KC_ALGR, KC_ESC, KC_SPC, KC_TAB, XXX, XXX, XXX, XXX, OU_AUTO, XXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     KC_ESC,KC_SPC,KC_TAB, KC_MSTP, KC_MPLY, KC_MUTE
                                      //`--------------------------'  `--------------------------'
  ),

    [NAV] = LAYOUT_split_3x6_3(
     XXX, XXX, XXX,  XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
     XXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXX, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, CW_TOGG, XXX,
     XXX, XXX, KC_ALGR, KC_ESC, KC_SPC, KC_TAB, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_INS, XXX,
     KC_ESC, KC_SPC, KC_TAB,KC_ENT, KC_BSPC, KC_DEL
  ),

    [MOU] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXX, XXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXX, KC_ALGR,           KC_ESC,KC_SPC,KC_TAB, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXX, XXX, XXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     KC_ESC, KC_SPC, KC_TAB, KC_BTN2, KC_BTN1, KC_BTN3
                                      //`--------------------------'  `--------------------------'
    ),

    [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXX, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, XXX,              XXX,   XXX,  XXX,    XXX, XXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXX, KC_COLN, KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, XXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXX, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_PIPE, XXX,              XXX,    XXX, KC_ALGR, XXX, XXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
     KC_LPRN, KC_RPRN, KC_UNDS, KC_ENT, KC_BSPC, KC_DEL
                                      //`--------------------------'  `--------------------------'
    ),

    [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
          XXX, KC_LBRC, KC_7, KC_8, KC_9, KC_RBRC,                          XXX,     XXX,     XXX,     XXX,     XXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
          XXX, KC_SCLN, KC_4, KC_5, KC_6, KC_EQL,                          XXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,     XXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
          XXX, KC_GRV, KC_1, KC_2, KC_3, KC_BSLS,                          XXX, KC_ENT, KC_BSPC, KC_DEL, KC_ALGR,     XXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
 KC_DOT, KC_0, KC_MINS,      KC_ENT, KC_BSPC, KC_DEL
                                      //`--------------------------'  `--------------------------'
  ),

    [FUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXX, KC_F12, KC_F7, KC_F8, KC_F9, KC_PSCR, XXX,              XXX,   XXX,  XXX,    XXX, XXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXX, KC_F11, KC_F4, KC_F5, KC_F6, KC_SCRL, XXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXX, KC_F10, KC_F1, KC_F2, KC_F3, KC_PAUS, XXX,              XXX,    XXX, KC_ALGR, XXX, XXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
	KC_APP, KC_SPC, KC_TAB, KC_ENT, KC_BSPC, KC_DEL
                                      //`--------------------------'  `--------------------------'
    ),

    // NOTE: this is currently included just to enable compilation
    // with flow layers, which require at least one to avoid compile
    // time errors
    [MISC] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┐                         ┌────────┬────────┬────────┬────────┬────────┐
     XXXXXXX  ,XXX   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX , KC_BRID ,KC_BRIU ,KC_PSCR ,XXXXXXX ,XXX , XXXXXXX,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX  ,XXXXXXX ,XXXXXXX ,XXX   ,  XXX,XXXXXXX ,                 XXXXXXX  ,KC_MPRV ,KC_MPLY ,KC_MNXT ,XXXXXXX ,XXX ,
  //├────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┤
     XXXXXXX  ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                 XXXXXXX  ,KC_VOLD ,KC_VOLU ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //└────────┴────────┴────────┴────┬───┴────┬───┼────────┐       ┌────────┼───┬────┴───┬────┴────────┴────────┴────────┘
                            XXXXXXX  ,XXXXXXX ,    XXXXXXX ,        XXXXXXX ,    XXXXXXX, XXXXXXX
  //                                └────────┘   └────────┘       └────────┘   └────────┘
  )
};

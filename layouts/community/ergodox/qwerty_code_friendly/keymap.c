/* -*- Mode:C; c-basic-offset:2; tab-width:2; indent-tabs-mode:nil; evil-indent-convert-tabs:t; -*- */

#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/**
 * See `readme.md` for notes on each define.
 */

/* Personal preference (enable by passing EXTRAFLAGS=... to make). */
/* #define CFQ_USE_MOMENTARY_LAYER_KEYS */

/* Holding right/left or left/right shift for single or double quote pair */
/* #define CFQ_USE_SHIFT_QUOTES */

#define CFQ_USE_DYNAMIC_MACRO

#if !defined(CFQ_USER_KEY0)
#  define CFQ_USER_KEY0 KC_BSPC
#endif
#if !defined(CFQ_USER_KEY1)
#  define CFQ_USER_KEY1 CFQ_KC_FN1
#endif
#if !defined(CFQ_USER_KEY2)
#  define CFQ_USER_KEY2 KC_INS
#endif
#if !defined(CFQ_USER_KEY3)
#  define CFQ_USER_KEY3 KC_NLCK
#endif
#if !defined(CFQ_USER_KEY4)
#  define CFQ_USER_KEY4 KC_BSPC
#endif
#if !defined(CFQ_USER_KEY5)
#  define CFQ_USER_KEY5 KC_DELT
#endif
#if !defined(CFQ_USER_KEY6)
#  define CFQ_USER_KEY6 KC_CAPS
#endif
#if !defined(CFQ_USER_KEY7)
#  define CFQ_USER_KEY7 CFQ_KC_FN3
#endif
#if !defined(CFQ_USER_KEY8)
#  define CFQ_USER_KEY8 KC_DEL
#endif

#ifndef CFQ_WORD_A
#define CFQ_WORD_A ""
#endif
#ifndef CFQ_WORD_B
#define CFQ_WORD_B ""
#endif
#ifndef CFQ_WORD_C
#define CFQ_WORD_C ""
#endif
#ifndef CFQ_WORD_D
#define CFQ_WORD_D ""
#endif
#ifndef CFQ_WORD_E
#define CFQ_WORD_E ""
#endif
#ifndef CFQ_WORD_F
#define CFQ_WORD_F ""
#endif
#ifndef CFQ_WORD_G
#define CFQ_WORD_G ""
#endif
#ifndef CFQ_WORD_H
#define CFQ_WORD_H ""
#endif
#ifndef CFQ_WORD_I
#define CFQ_WORD_I ""
#endif
#ifndef CFQ_WORD_J
#define CFQ_WORD_J ""
#endif
#ifndef CFQ_WORD_K
#define CFQ_WORD_K ""
#endif
#ifndef CFQ_WORD_L
#define CFQ_WORD_L ""
#endif
#ifndef CFQ_WORD_M
#define CFQ_WORD_M ""
#endif
#ifndef CFQ_WORD_N
#define CFQ_WORD_N ""
#endif
#ifndef CFQ_WORD_O
#define CFQ_WORD_O ""
#endif
#ifndef CFQ_WORD_P
#define CFQ_WORD_P ""
#endif
#ifndef CFQ_WORD_Q
#define CFQ_WORD_Q ""
#endif
#ifndef CFQ_WORD_R
#define CFQ_WORD_R ""
#endif
#ifndef CFQ_WORD_S
#define CFQ_WORD_S ""
#endif
#ifndef CFQ_WORD_T
#define CFQ_WORD_T ""
#endif
#ifndef CFQ_WORD_U
#define CFQ_WORD_U ""
#endif
#ifndef CFQ_WORD_V
#define CFQ_WORD_V ""
#endif
#ifndef CFQ_WORD_W
#define CFQ_WORD_W ""
#endif
#ifndef CFQ_WORD_X
#define CFQ_WORD_X ""
#endif
#ifndef CFQ_WORD_Y
#define CFQ_WORD_Y ""
#endif
#ifndef CFQ_WORD_Z
#define CFQ_WORD_Z ""
#endif

/* lower and title capitals versions (setup at start). */
static char *cfq_word_lut[2][26] = {
  {
    CFQ_WORD_A, CFQ_WORD_B, CFQ_WORD_C, CFQ_WORD_D, CFQ_WORD_E, CFQ_WORD_F,
    CFQ_WORD_G, CFQ_WORD_H, CFQ_WORD_I, CFQ_WORD_J, CFQ_WORD_K, CFQ_WORD_L,
    CFQ_WORD_M, CFQ_WORD_N, CFQ_WORD_O, CFQ_WORD_P, CFQ_WORD_Q, CFQ_WORD_R,
    CFQ_WORD_S, CFQ_WORD_T, CFQ_WORD_U, CFQ_WORD_V, CFQ_WORD_W, CFQ_WORD_X,
    CFQ_WORD_Y, CFQ_WORD_Z,
  },
  {NULL}
};

/* Storage for title-caps strings. */
static char cfq_word_lut_title_caps[
    sizeof(CFQ_WORD_A) + sizeof(CFQ_WORD_B) + sizeof(CFQ_WORD_C) + sizeof(CFQ_WORD_D) +
    sizeof(CFQ_WORD_E) + sizeof(CFQ_WORD_F) + sizeof(CFQ_WORD_G) + sizeof(CFQ_WORD_H) +
    sizeof(CFQ_WORD_I) + sizeof(CFQ_WORD_J) + sizeof(CFQ_WORD_K) + sizeof(CFQ_WORD_L) +
    sizeof(CFQ_WORD_M) + sizeof(CFQ_WORD_N) + sizeof(CFQ_WORD_O) + sizeof(CFQ_WORD_P) +
    sizeof(CFQ_WORD_Q) + sizeof(CFQ_WORD_R) + sizeof(CFQ_WORD_S) + sizeof(CFQ_WORD_T) +
    sizeof(CFQ_WORD_U) + sizeof(CFQ_WORD_V) + sizeof(CFQ_WORD_W) + sizeof(CFQ_WORD_X) +
    sizeof(CFQ_WORD_Y) + sizeof(CFQ_WORD_Z)
];

#define BASE 0 /* default layer */
#define SYMB 1 /* symbols */
#define MDIA 2 /* media keys */
#define WORD 3 /* experimental keys */

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, /* can always be here */
  RGB_SLD,

  M_BRACKET_IN_CBR,
  M_BRACKET_IN_PRN,
  M_BRACKET_IN_BRC,
  M_BRACKET_IN_ANG,
  M_BRACKET_OUT_CBR,
  M_BRACKET_OUT_PRN,
  M_BRACKET_OUT_BRC,
  M_BRACKET_OUT_ANG,
  M_ARROW_RMINUS,
  M_ARROW_LMINUS,
  M_ARROW_REQL,
  M_ARROW_LEQL,

  /* allow user defined words for each character:
   * use CFQ_WORD_[A-Z] defines. */
  M_WORD_A, M_WORD_B, M_WORD_C, M_WORD_D, M_WORD_E, M_WORD_F,
  M_WORD_G, M_WORD_H, M_WORD_I, M_WORD_J, M_WORD_K, M_WORD_L,
  M_WORD_M, M_WORD_N, M_WORD_O, M_WORD_P, M_WORD_Q, M_WORD_R,
  M_WORD_S, M_WORD_T, M_WORD_U, M_WORD_V, M_WORD_W, M_WORD_X,
  M_WORD_Y, M_WORD_Z,

#ifdef CFQ_USE_DYNAMIC_MACRO
  DYNAMIC_MACRO_RANGE,
#endif
};

#ifdef CFQ_USE_DYNAMIC_MACRO
#include "dynamic_macro.h"
#endif

#ifdef CFQ_USE_MOMENTARY_LAYER_KEYS
#define CFQ_KC_FN1 MO(1)
#define CFQ_KC_FN2 MO(2)
#define CFQ_KC_FN3 MO(3)
#else
#define CFQ_KC_FN1 KC_FN1
#define CFQ_KC_FN2 KC_FN2
#define CFQ_KC_FN3 KC_FN3
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Grave  |   !  |   @  |   #  |   $  |   %  |   {  |           |  }   |   ^  |   &  |   *  |   -  |   =  | BSpace |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   (  |           |  )   |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Esc    |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|   [  |           |  ]   |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtl |Super | Alt  | ~L1  |Space |                                       | Left | Down | Up   |Right | Del  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Ins  |NumClk|       | Home | End  |
 *                                 ,------+------+------|       |------+------+------.
 *                                 |      |      |CapsLk|       | PgUp |      |      |
 *                                 |BSpace| Del  |------|       |------| ~L2  |Enter |
 *                                 |      |      | ~L3  |       | PgDn |      |      |
 *                                 `--------------------'       `--------------------'
 *
 * Optional overrides: see CFQ_USER_KEY# defines.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      | USR0   |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | USR1 |      |                                       |      |      |      |      | USR8 |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | USR2 | USR3 |       |      |      |
 *                                 ,------+------+------|       |------+------+------.
 *                                 |      |      | USR6 |       |      |      |      |
 *                                 | USR4 | USR5 |------|       |------|      |      |
 *                                 |      |      | USR7 |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

/* If it accepts an argument (i.e, is a function), it doesn't need KC_.
 * Otherwise, it needs KC_* */
[BASE] = LAYOUT_ergodox(  /* layer 0 : default */
  /* left hand */
  KC_GRV,  KC_EXLM, KC_AT,   KC_HASH,       KC_DLR, KC_PERC, KC_LCBR,
  KC_TAB,  KC_Q,    KC_W,    KC_E,          KC_R,   KC_T,    KC_LPRN,
  KC_ESC,  KC_A,    KC_S,    KC_D,          KC_F,   KC_G,
  KC_LSFT, KC_Z,    KC_X,    KC_C,          KC_V,   KC_B,    KC_LBRC,
  KC_LCTL, KC_LGUI, KC_LALT, CFQ_USER_KEY1, KC_SPC,
                                                    CFQ_USER_KEY2, CFQ_USER_KEY3,
                                                                   CFQ_USER_KEY6,
                                     CFQ_USER_KEY4, CFQ_USER_KEY5, CFQ_USER_KEY7,
  /* right hand */
  KC_RCBR,     KC_CIRC, KC_AMPR, KC_ASTR,KC_MINS, KC_EQL,    CFQ_USER_KEY0,
  KC_RPRN,     KC_Y,    KC_U,    KC_I,   KC_O,    KC_P,      KC_BSLS,
               KC_H,    KC_J,    KC_K,   KC_L,    KC_SCLN,   KC_QUOT,
  KC_RBRC,     KC_N,    KC_M,    KC_COMM,KC_DOT,  KC_SLSH,   KC_RSFT,
                        KC_LEFT, KC_DOWN,KC_UP,   KC_RGHT,   CFQ_USER_KEY8,
  KC_HOME, KC_END,
  KC_PGUP,
  KC_PGDN, CFQ_KC_FN2, KC_ENT
),/* Keymap 1: KeyPad, Macro Record
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |  {}  |           |  }{  |      |NumLck|   /  |   *  |   -  |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |  =>  |  ()  |           |  )(  |  <=  |   7  |   8  |   9  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |  ->  |------|           |------|  <-  |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|  []  |           |  ][  |------+------+------+------+------+--------|
 * |        |      |      |      |      |  <>  |      |           |      |  ><  |   1  |   2  |   3  | Enter|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |      |   .  | Enter|      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,--------------.
 *                                        |Start1|Start2|       |      |       |
 *                                 ,------+------+------|       |------+-------+------.
 *                                 |      |      | Stop |       |      |       |      |
 *                                 |Play1 |Play2 |------|       |------|       |      |
 *                                 |      |      |      |       |      |       |      |
 *                                 `--------------------'       `---------------------'
 */
/* SYMBOLS */
[SYMB] = LAYOUT_ergodox(
  /* left hand */
  KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,            M_BRACKET_IN_CBR,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M_ARROW_REQL,     M_BRACKET_IN_PRN,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M_ARROW_RMINUS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, M_BRACKET_IN_ANG, M_BRACKET_IN_BRC,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
#ifdef CFQ_USE_DYNAMIC_MACRO
                               DYN_REC_START1, DYN_REC_START2,
                                               DYN_REC_STOP,
                              DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, KC_TRNS,
#else
                                      KC_TRNS, KC_TRNS,
                                               KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS,
#endif
  /* right hand */
  M_BRACKET_OUT_CBR, KC_TRNS,           KC_NLCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,  KC_TRNS,
  M_BRACKET_OUT_PRN, M_ARROW_LEQL,      KC_KP_7, KC_KP_8,     KC_KP_9,        KC_KP_PLUS,  KC_TRNS,
                     M_ARROW_LMINUS,    KC_KP_4, KC_KP_5,     KC_KP_6,        KC_KP_PLUS,  KC_TRNS,
  M_BRACKET_OUT_BRC, M_BRACKET_OUT_ANG, KC_KP_1, KC_KP_2,     KC_KP_3,        KC_KP_ENTER, KC_TRNS,
                                        KC_KP_0, KC_TRNS,     KC_KP_DOT,      KC_KP_ENTER, KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: F-Keys, media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |MWhlUp|           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------| Left | Down | Up   |Right |      |        |
 * |--------+------+------+------+------+------|MWhlDn|           |      |------+------+------+------+------+--------|
 * |        |      | Rclk | Mclk | Lclk |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | MRwd | MFwd |       | MPrv | MNxt |
 *                                 ,------+------+------|       |------+------+------.
 *                                 |      |      |      |       |VolUp |      |      |
 *                                 | Mute |      |------|       |------|      | Play |
 *                                 |      |      |      |       |VolDn |      |      |
 *                                 `--------------------'       `--------------------'
 */
/* MEDIA AND MOUSE */
[MDIA] = LAYOUT_ergodox(
  /* left hand */
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_WH_U,
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_BTN2, KC_BTN3, KC_BTN1, KC_TRNS, KC_WH_D,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                      KC_MRWD, KC_MFFD,
                                               KC_TRNS,
                             KC_MUTE, KC_TRNS, KC_TRNS,
  /* right hand */
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
  KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_MPRV, KC_MNXT,
  KC_VOLU,
  KC_VOLD, KC_TRNS, KC_MPLY
),
/* Keymap 3: Entire Words (one for each key)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F11 |           | F12  |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------+------+------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

/* WORDS */
[WORD] = LAYOUT_ergodox(
  /* left hand */
  KC_TRNS, KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,
  KC_TRNS, M_WORD_Q, M_WORD_W, M_WORD_E, M_WORD_R, M_WORD_T, KC_TRNS,
  KC_TRNS, M_WORD_A, M_WORD_S, M_WORD_D, M_WORD_F, M_WORD_G,
  KC_TRNS, M_WORD_Z, M_WORD_X, M_WORD_C, M_WORD_V, M_WORD_B, KC_TRNS,
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                                                   KC_TRNS,  KC_TRNS,
                                                             KC_TRNS,
                                         KC_TRNS,  KC_TRNS,  KC_TRNS,
  /* right hand */
  KC_F12,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_TRNS,
  KC_TRNS, M_WORD_Y, M_WORD_U, M_WORD_I, M_WORD_O, M_WORD_P, KC_TRNS,
           M_WORD_H, M_WORD_J, M_WORD_K, M_WORD_L, KC_TRNS,  KC_TRNS,
  KC_TRNS, M_WORD_N, M_WORD_M, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
  KC_TRNS, KC_TRNS,
  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),               /* FN1 - Momentary Layer 1 (Symbols) */
  [2] = ACTION_LAYER_TAP_TOGGLE(MDIA),               /* FN2 - Momentary Layer 2 (Media) */
  [3] = ACTION_LAYER_TAP_TOGGLE(WORD),               /* FN3 - Momentary Layer 3 (Words) */
};


    #define WITHOUT_MODS(...) \
      do { \
        uint8_t _real_mods = get_mods(); \
        clear_mods(); \
        { __VA_ARGS__ } \
        set_mods(_real_mods); \
      } while (0)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CFQ_USE_DYNAMIC_MACRO
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }
#endif
  switch (keycode) {
    /* dynamically generate these. */
    case RGB_SLD:
      if (record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
        rgblight_mode(1);
#endif
      }
      return false;
      break;
    case M_BRACKET_IN_CBR:  /* {} */
      if (record->event.pressed) {
        SEND_STRING("{}" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_IN_PRN:  /* () */
      if (record->event.pressed) {
        SEND_STRING("()" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_IN_BRC:  /* [] */
      if (record->event.pressed) {
        SEND_STRING("[]" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_IN_ANG:  /* <> */
      if (record->event.pressed) {
        SEND_STRING("<>" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_OUT_CBR:  /* }{ */
      if (record->event.pressed) {
        SEND_STRING("}{" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_OUT_PRN:  /* )( */
      if (record->event.pressed) {
        SEND_STRING(")(" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_OUT_BRC:  /* ][ */
      if (record->event.pressed) {
        SEND_STRING("][" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_BRACKET_OUT_ANG:  /* >< */
      if (record->event.pressed) {
        SEND_STRING("><" SS_TAP(X_LEFT));
        return false;
      }
      break;
    case M_ARROW_LMINUS:  /* <- */
      if (record->event.pressed) {
        SEND_STRING("<-");
        return false;
      }
      break;
    case M_ARROW_RMINUS:  /* -> */
      if (record->event.pressed) {
        SEND_STRING("->");
        return false;
      }
      break;
    case M_ARROW_LEQL:  /* <= */
      if (record->event.pressed) {
        SEND_STRING("<=");
        return false;
      }
      break;
    case M_ARROW_REQL:  /* => */
      if (record->event.pressed) {
        SEND_STRING("=>");
        return false;
      }
      break;
#ifdef CFQ_USE_SHIFT_QUOTES
    case KC_LSHIFT:  /* '' */
      if (record->event.pressed && (keyboard_report->mods & (MOD_BIT(KC_RSFT)))) {
        WITHOUT_MODS({
            SEND_STRING("''" SS_TAP(X_LEFT) SS_DOWN(X_RSHIFT) SS_DOWN(X_LSHIFT));
          });
        return false;
      }
      break;
    case KC_RSHIFT:  /* "" */
      if (record->event.pressed && (keyboard_report->mods & (MOD_BIT(KC_LSFT)))) {
        WITHOUT_MODS({
            SEND_STRING("\x22\x22" SS_TAP(X_LEFT) SS_DOWN(X_LSHIFT) SS_DOWN(X_RSHIFT));
          });
        return false;
      }
      break;
#endif  /* CFQ_USE_SHIFT_QUOTES */
    case M_WORD_A...M_WORD_Z:
    {
      uint8_t shift_index = (keyboard_report->mods & (MOD_BIT(KC_RSFT) | MOD_BIT(KC_LSFT))) ? 1 : 0;
      const char *word = cfq_word_lut[shift_index][keycode - M_WORD_A];
      if (record->event.pressed) {
        if (*word) {
          WITHOUT_MODS({
              send_string(word);
            });
        }
        return false;
      }
      break;
    }
  }

  return true;
}

/* Runs just one time when the keyboard initializes. */
void matrix_init_user(void) {

  /* Duplicate 'cfq_word_lut[0][...]' into 'cfq_word_lut[1][...]' */
  {
    char *d = cfq_word_lut_title_caps;
    for (uint16_t i = 0; i < 26; i++) {
      char *s = cfq_word_lut[0][i];
      cfq_word_lut[1][i] = d;
      while ((*d++ = *s++)) {}
    }
  }
  /* Title caps. */
  for (uint16_t i = 0; i < 26; i++) {
    char *w = cfq_word_lut[1][i];
    bool prev_is_alpha = false;
    if (*w) {
      while (*w) {
        bool is_lower = (*w >= 'a' && *w <= 'z');
        bool is_upper = (*w >= 'A' && *w <= 'Z');
        if (prev_is_alpha == false && is_lower) {
          *w -= ('a' - 'A');
        }
        prev_is_alpha = is_lower || is_upper;
        w++;
      }
    }
  }
};

/* Runs constantly in the background, in a loop. */
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
  switch (layer) {
    case 1:
      ergodox_right_led_1_on();
      break;
    case 2:
      ergodox_right_led_2_on();
      break;
    case 3:
      ergodox_right_led_3_on();
      break;
    default:
      /* none */
      break;
  }

};

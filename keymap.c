#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _NUMPAD 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  DM_BRCT,   //()+LEFT
  DM_BRCTL,  //[]+LEFT
  DM_BRCTM,  //{}+LEFT
  DM_SQUOT,  //''+LEFT
  DM_DQUOT,  //""+LEFT
  NUMPAD,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_NUMPAD NUMPAD
#define KC_ADJST ADJUST

#define KC_DBRCT  DM_BRCT
#define KC_DBRCTL DM_BRCTL
#define KC_DBRCTM DM_BRCTM
#define KC_DSQUOT DM_SQUOT
#define KC_DDQUOT DM_DQUOT

#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD

#define KC_RSSPC LT(_RAISE,KC_SPC)
#define KC_LWSPC LT(_LOWER,KC_SPC)

// layer
#define KC_L_JPEN   LT(_LOWER, LALT(KC_GRV) )
#define KC_F_ESC    LT(_NUMR,  KC_ESC)
#define KC_AJ_SPC   LT(_ADJUST,  KC_SPC)

// shift_t
#define KC_S_TAB    LSFT_T(KC_TAB)
#define KC_S_ESC    LSFT_T(KC_ESC)
#define KC_S_MNS    SFT_T(KC_MINS)
#define KC_S_CLN    SFT_T(KC_COLN)
#define KC_S_DOT    SFT_T(KC_DOT)

// ctl_t
#define KC_C_BS     LCTL_T(KC_BSPC)
#define KC_C_TAB    CTL_T(KC_TAB)
#define KC_C_SPC    CTL_T(KC_SPC)
#define KC_C_JA     CTL_T(KC_LANG1)

// alt_t
#define KC_A_SL     ALT_T(KC_SLSH)
#define KC_A_DEL    ALT_T(KC_DEL)
#define KC_A_INS    ALT_T(KC_INS)
#define KC_A_ENT    ALT_T(KC_ENT)
#define KC_A_NUM    ALT_T(KC_NUMPAD)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,   DEL,\
      C_TAB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH, S_MNS,\
	                         A_INS,LOWER , C_SPC,    C_SPC,  RAISE,  A_ENT
  ),

  [_LOWER] = LAYOUT_kc(	\
  //    ESC,     !,     @,     #,     $,     %,                      ^,     &,     *,     (,     ),  BSPC,
  //  CTLTB,     `,     -,     =,     \,     [,                      ],     ',     ,,     .,     /,     ;,
  //   LSFT,     ~,     _,     +,     |,     {,                      },     ",     <,     >,     ?, SFCLN,
  //                              ALINS,   SPC, LOWER,    RAISE,   ENT,  RALT
        ESC,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  BSPC,\
      C_TAB,   GRV,  MINS,   EQL,  BSLS,  LBRC,                   RBRC,  QUOT,  COMM,   DOT,  SLSH,  SCLN,\
       LSFT,  TILD,  UNDS,  PLUS,  PIPE,  LCBR,                   RCBR,  DQUO,  LABK,  RABK,  QUES, S_CLN,\
                                  _____ , LOWER , _____,    _____,  RAISE,  _____
  ),
  
  [_RAISE] = LAYOUT_kc( \
        ESC,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,  BSPC,\
      C_TAB, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   LEFT,  DOWN,    UP, RIGHT, XXXXX, XXXXX,\
       LSFT, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  DBRCT,DBRCTL,DBRCTM,DSQUOT,DDQUOT, XXXXX,\
                                   _____, LOWER , _____,    _____,  RAISE,  _____

 ),
  
  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 _____, LOWER , _____,    _____,  RAISE,  _____
                              //`--------------------'  `--------------------'
 ),

  [_NUMPAD] = LAYOUT_kc( \
      XXXXX,    F1,    F2,    F3,    F4,    F5,                  XXXXX, 7,     8,     9,   EQL,  XXXXX, \
      XXXXX,    F6,    F7,    F8,    F9,   F10,                   COMM, 4,     5,     6,  ASTR,   SLSH, \
      XXXXX,   F11,   F12, XXXXX, XXXXX, XXXXX,                    DOT, 1,     2,     3,  PLUS,   MINS, \
                                  _____, LOWER, _____,    _____,  RAISE,      0
 ),

};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t stored_keycode;
  bool is_tapped;
  bool is_toggled = false;
  static uint16_t time_on_pressed;
  uint16_t prev_keycode = stored_keycode;

  is_tapped = ( (!record->event.pressed) && (keycode == prev_keycode ));
  stored_keycode = keycode;

  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;

    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
	time_on_pressed = record->event.time;
      } else {
        layer_off(_LOWER);
        if( is_tapped){
          if (TIMER_DIFF_16(record->event.time, time_on_pressed) < TAPPING_TERM) {
            SEND_STRING(SS_TAP(X_SPACE));
          }
        }
	time_on_pressed = 0;
      }
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      return false;

    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
	time_on_pressed = record->event.time;
      } else {
        layer_off(_RAISE);
        if (TIMER_DIFF_16(record->event.time, time_on_pressed) < TAPPING_TERM) {
          if( is_tapped){
            SEND_STRING(SS_TAP(X_ENTER));
          }
        }
	time_on_pressed = 0;
      }
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      return false;

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;

    case NUMPAD:
      is_toggled = !is_toggled;
      if( is_toggled ){
        layer_on(_NUMPAD);
      } else {
        layer_off(_NUMPAD);
      }
      return false;

    case DM_BRCT:
      if (record->event.pressed) {
        SEND_STRING("()"SS_TAP(X_LEFT));
      }
      return false;

    case DM_BRCTL:
      if (record->event.pressed) {
        SEND_STRING("[]"SS_TAP(X_LEFT));
      }
      return false;

    case DM_BRCTM:
      if (record->event.pressed) {
        SEND_STRING("{}"SS_TAP(X_LEFT));
      }
      return false;

    case DM_SQUOT:
      if (record->event.pressed) {
        SEND_STRING("\'\'"SS_TAP(X_LEFT));
      }
      return false;

    case DM_DQUOT:
      if (record->event.pressed) {
        SEND_STRING("\"\""SS_TAP(X_LEFT));
      }
      return false;

    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;

    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
  }
  return true;
}


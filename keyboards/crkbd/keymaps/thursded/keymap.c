#include QMK_KEYBOARD_H
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

// From RJ. Possibly not needed?
  #ifdef OLED_DRIVER_ENABLE
  static uint32_t        oled_timer = 0;
  static char     keylog_str[6]   = {};
  static uint16_t log_timer       = 0;
  static const char PROGMEM code_to_name[0xFF] = {
  //   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
      ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
      'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
      '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
      ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
      ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
      'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
      ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
  };

  void add_keylog(uint16_t keycode);
  #endif
// end RJ

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _FF14 1
#define _LOWER 2
#define _RAISE 3
#define _ADJUST 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FF14,
  LOWER,
  RAISE,
  ADJUST/*,
  BACKLIT,
  RGBRST*/
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
//#define KC_LRST  RGBRST
//#define KC_LTOG  RGB_TOG
//#define KC_LHUI  RGB_HUI
//#define KC_LHUD  RGB_HUD
//#define KC_LSAI  RGB_SAI
//#define KC_LSAD  RGB_SAD
//#define KC_LVAI  RGB_VAI
//#define KC_LVAD  RGB_VAD
//#define KC_LMOD  RGB_MOD
//#define KC_GUIEI GUI_T(KC_LANG2)
//#define KC_ALTKN ALT_T(KC_LANG1)

#define KC_SHDEL  RSFT_T(KC_DEL)
#define KC_ALGUI  ALT_T(KC_LGUI)
#define KC_QWERTY QWERTY
#define KC_FF14   FF14
#define KC_ROMA   LALT(GRV)
#define KC_HIRA   LCTL(CAPS)
#define KC_KATA   LALT(CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH, SHDEL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER,   SPC,      ENT, RAISE,  RALT \
                              //`--------------------'  `--------------------'
  ),

  [_FF14] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH, SHDEL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LALT, LOWER,   SPC,      ENT, RAISE,  LGUI \
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,    F1,    F2,    F3,    F4, XXXXX,                   PSCR,  SLCK,  PAUS,  LBRC,  RBRC,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,    F5,    F6,    F7,    F8, XXXXX,                    INS,  PGUP,    UP,  PGDN,  HOME,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,    F9,   F10,   F11,   F12,   GRV,                    DEL,  LEFT,  DOWN, RIGHT,   END, SHDEL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER,   SPC,      ENT, RAISE, ALGUI \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     1,     2,     3,     4,  COMM,                   PSCR,  SLCK,  PAUS,  LBRC,  RBRC,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     5,     6,     7,     8,   DOT,                    INS,  PGUP,    UP,  PGDN,  HOME,  BSLS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     9,     0,  MINS,   EQL,   GRV,                    DEL,  LEFT,  DOWN, RIGHT,   END, SHDEL,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER,   SPC,      ENT, RAISE, ALGUI \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST, XXXXX, XXXXX, XXXXX, XXXXX,  ROMA,                 QWERTY,  FF14, XXXXX, XXXXX, XXXXX,  VOLU,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       CALC, XXXXX, XXXXX, XXXXX, XXXXX,  HIRA,                   MRWD,  MPRV,  MPLY,  MNXT,  MFFD,  VOLD,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       CAPS, XXXXX, XXXXX, XXXXX, XXXXX,  KATA,                  XXXXX, XXXXX,  MSTP, XXXXX, XXXXX,  MUTE,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LGUI, LOWER,   SPC,      ENT, RAISE, ALGUI \
                              //`--------------------'  `--------------------'
  )
};

/* -snip- Foostan code
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
      //matrix_write_ln(matrix, read_keylog());
      //matrix_write_ln(matrix, read_keylogs());
      //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
      //matrix_write_ln(matrix, read_host_led_state());
      matrix_write_ln(matrix, read_timelog());
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
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
-snip- */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
        add_keylog(keycode);
#endif
#ifndef SPLIT_KEYBOARD
        if (keycode == RESET && !is_master) {
            return false;
        }
#endif
    }
    return true;
}

 #ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_master) {
    return OLED_ROTATION_270;
  } else {
    return OLED_ROTATION_180;
  }
}

void add_keylog(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
    keycode = keycode & 0xFF;
  } else if (keycode > 0xFF) {
    keycode = 0;
  }

  for (uint8_t i = 4; i > 0; --i) {
    keylog_str[i] = keylog_str[i - 1];
  }

  if (keycode < (sizeof(code_to_name) / sizeof(char))) {
    keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
  }

  log_timer = timer_read();
}

void update_log(void) {
  if (timer_elapsed(log_timer) > 750) {
    //add_keylog(0);
  }
}

void render_keylogger_status(void) {
  oled_write_P(PSTR("KLGGR"), false);
  oled_write(keylog_str, false);
}

void render_layer_state(void) {
  oled_write_ln_P(PSTR("Layr:"), false);
  oled_write_ln_P(PSTR("BASE"), layer_state_is(_QWERTY));
  oled_write_ln_P(PSTR("FF14"), layer_state_is(_FF14));
  oled_write_ln_P(PSTR("LOWER"), layer_state_is(_LOWER));
  oled_write_ln_P(PSTR("RAISE"), layer_state_is(_RAISE));
  oled_write_ln_P(PSTR("ADJST"), layer_state_is(_ADJUST));
  oled_write_ln_P(PSTR(" "), false);
}

void render_keylock_status(uint8_t led_usb_state) {
  oled_write_P(PSTR("Lock:"), false);
  oled_write_ln_P(PSTR("NUM"), led_usb_state & (1 << USB_LED_NUM_LOCK));
  oled_write_ln_P(PSTR("CAPS"), led_usb_state & (1 << USB_LED_CAPS_LOCK));
  oled_write_ln_P(PSTR("SCRL"), led_usb_state & (1 << USB_LED_SCROLL_LOCK));
  oled_write_ln_P(PSTR(" "), false);
}

void render_mod_status(uint8_t modifiers) {
  oled_write_P(PSTR("Mods:"), false);
  oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
  oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
  oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
  oled_write_ln_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
  oled_write_ln_P(PSTR(" "), false);
}

/* RJ's logo. Not used
  void render_rj_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};
    oled_write_P(crkbd_logo, false);
  }
*/

// Using oled_write_raw method. FF14 Logo.
void render_ff14_logo(void) {
  static const char PROGMEM ff14_logo[] = {
  // 'FF14 Logo', 128x32px
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xe0, 
  0x00, 0x00, 0x80, 0xe0, 0xf0, 0xe0, 0xe0, 0x30, 0x18, 0x1c, 0x1c, 0x1c, 0x1e, 0x1c, 0x06, 0x03, 
  0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd8, 0xf0, 0xf8, 0xfc, 0x3d, 0x0f, 0x0f, 0x07, 
  0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0x0f, 0x1e, 0x3c, 0xfe, 0xfe, 0xfe, 
  0xa3, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x14, 0x04, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 
  0x08, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0x14, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xfc, 0x14, 0x00, 0x00, 0x00, 0xfc, 0x14, 0xfc, 0x00, 0x00, 0xfc, 0x0c, 
  0x18, 0xfc, 0x00, 0x00, 0x04, 0xfc, 0x04, 0x00, 0x00, 0xfc, 0x14, 0x14, 0xfc, 0x00, 0x00, 0x7c, 
  0xc4, 0x8c, 0x00, 0x00, 0x1c, 0xf0, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0xf0, 
  0x0c, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xe0, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xfb, 
  0xe0, 0x60, 0x20, 0x19, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 
  0x00, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x10, 0x10, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 
  0x00, 0x1f, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x0e, 
  0x10, 0x0f, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x01, 
  0x1e, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x07, 0x1c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 0x1f, 0x1e, 0x3c, 0xf8, 
  0x70, 0x70, 0x70, 0xf0, 0x70, 0x30, 0x30, 0x30, 0x78, 0xf8, 0x7c, 0x1e, 0x1f, 0x0f, 0x01, 0x01, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  oled_write_raw_P(ff14_logo, sizeof(ff14_logo));
}

void render_oriCorne_logo(void) {
  static const char PROGMEM oriCorne_logo[] = {
    // 'Corne Logo', 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 
    0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 
    0x00, 0x00, 0xf0, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0x01, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x7f, 0x1f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 
    0xfc, 0x1e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x1e, 0x3c, 0x38, 0x30, 0x00, 0x00, 0xf0, 0xf8, 
    0xfc, 0x1e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x1e, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0xfe, 0xfe, 
    0xfc, 0x1c, 0x0e, 0x0e, 0x0e, 0x0e, 0x00, 0x00, 0xfe, 0xfe, 0xfc, 0x1c, 0x0e, 0x0e, 0x0e, 0x0e, 
    0x1e, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0xde, 0xce, 0xce, 0xce, 0xce, 0xce, 0xce, 
    0xde, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 
    0xfe, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xc1, 0x80, 0x80, 0x80, 0xc0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x1f, 
    0x3f, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x3c, 0x1c, 0x0c, 0x00, 0x00, 0x0f, 0x1f, 
    0x3f, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x3f, 0x1f, 0x0f, 0x00, 0x00, 0x7f, 0x7f, 
    0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x7f, 0x7f, 0x7f, 0x00, 0x00, 0x0f, 0x1f, 0x3f, 0x79, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 
    0x79, 0x3d, 0x1d, 0x0d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 
    0x03, 0x03, 0x03, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x03, 0x03, 0x01, 0x03, 0x07, 0x07, 
    0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00*/
  }
  oled_write_raw_P(oriCorne_logo, sizeof(oriCorne_logo));
}
void render_status_main(void) {
  //layers first//
  render_layer_state();
  /* Show Keyboard Layout  */
  render_keylock_status(host_keyboard_leds());
  //render_mod_status(get_mods()|get_oneshot_mods());
  //render_keylogger_status();
}

void render_status_secondary(void) {
  if(layer_state_is(_FF14)){
    render_ff14_logo();
  }
  else {
    render_oriCorne_logo();
  }
}

void oled_task_user(void) {
  if (timer_elapsed32(oled_timer) > 30000) {
    oled_off();
    return;
  }
  #ifndef SPLIT_KEYBOARD
    else { oled_on(); }
  #endif

  update_log();
  if (is_master) {
    render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
  } else {
    render_status_secondary();
  }
}



  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
    case FF14:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_FF14);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
/*    case RGB_MOD:
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
      #endif*/
      break;
  }
  return true;
}

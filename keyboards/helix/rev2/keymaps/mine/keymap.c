#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
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
enum layer_number {
    _QWERTY = 0,
    _EXT1,
    _EXT2,
    _MQWERTY,
    _MEXT1,
    _MEXT2
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EXT1,
  EXT2,
  MQWERTY,
  MEXT1,
  MEXT2,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ext1 |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | GUI  | Alt  | Ctrl |Space | SAS  |Enter | Ext2 | ESC  | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      EXT1, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,        KC_RBRC,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______ , \
      _______,  _______,  KC_LGUI, KC_LALT, KC_LCTL,    KC_SPC,   RSFT_T(KC_SPC), KC_ENT,      EXT2,   KC_ESC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  /* Ext1
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  ^`  | ^Up  |^Left | S^`  |^Right|  ^5  |             |  ^6  |  ^7  |  ^8  |  ^9  |  ^0  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |  ^A  |  ^S  |  Up  |  ^F  |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ext1 | Home | Left | Down | Right| End  |             |      | Bksp |  F7  |  F8  |  F10 | Del  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Shift |  ^Z  |  ^X  |  ^C  |  ^V  |      |      |      |      |      |      |      |  ^/  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | GUI  | Alt  | Ctrl |Space |^Space|^Enter| Ext2 | ESC  |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_EXT1] = LAYOUT( \
      LCTL(KC_GRV), LCTL(KC_UP), LCTL(KC_LEFT), LCTL(LSFT(KC_GRV)), LCTL(KC_RGHT), LCTL(KC_5), LCTL(KC_6), LCTL(KC_7), LCTL(KC_8), LSFT(LCTL(KC_TAB)), LCTL(KC_TAB),  _______, \
      KC_TAB, LCTL(KC_A), LCTL(KC_S), KC_UP, LCTL(KC_F), LCTL(KC_T),           LCTL(KC_Y), LCTL(KC_U), LCTL(KC_I), LCTL(KC_O), LCTL(KC_P), LCTL(KC_BSPC), \
      EXT1, KC_HOME,    KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_END,                      LCTL(KC_H),    KC_BSPC,    KC_F7,    KC_F8,    KC_F10,    KC_DEL, \
      KC_LSFT, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_B), LCTL(KC_LBRC), LCTL(KC_RBRC), LCTL(KC_K), LCTL(KC_M), LCTL(KC_COMM), LCTL(KC_DOT), LCTL(KC_SLSH), _______, \
      _______, _______, KC_LGUI, KC_LALT, KC_LCTL, KC_SPC, KC_LANG5, LCTL(KC_ENT),  EXT2, KC_ESC, LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_UP), LCTL(KC_RGHT) \
      ),

  /* Ext2
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|      |      |      |             |      |  -   |  =   |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |Aud on|Audoff| Mac  |             | Win  |Qwerty|MQwert|      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | GUI  | Alt  | Ctrl |      |Shift |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_EXT2] =  LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      _______, RESET,   RGBRST,  _______, _______, _______,                   _______, KC_MINS, KC_EQL , _______, _______, KC_PSCR, \
      _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, QWERTY,  MQWERTY, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, KC_LGUI, KC_LALT, KC_LCTL, _______, KC_LSFT, _______, _______, _______, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD \
      ),

  /* MQwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |MExt1 |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | Ctrl | Alt  | GUI  |Space | SAS  |Enter |MExt2 | ESC  | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_MQWERTY] = LAYOUT( \
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      MEXT1, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,        KC_RBRC,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______ , \
      _______,  _______,  KC_LCTL, KC_LALT, KC_LGUI,    KC_SPC,   SFT_T(KC_SPC), KC_ENT,     MEXT2,   KC_ESC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
      ),

  /* MExt1
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  ^`  | ^Up  |^Left | S^`  |^Right|  ^5  |             |  ^6  |  ^7  |  ^8  |  ^9  |  ^0  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |  ^A  |  ^S  |  Up  |  ^F  |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |MExt1 | Home | Left | Down | Right| End  |             |      | Bksp |  F7  |  F8  |  F10 | Del  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl |  ^Z  |  ^X  |  ^C  |  ^V  |      |      |      |      |      |      |      |  ^/  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | Ctrl | Alt  | GUI  |Space |^Space|^Enter|MExt2 | ESC  |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_MEXT1] = LAYOUT( \
      LGUI(KC_GRV), LCTL(KC_UP), LCTL(KC_LEFT), LGUI(LSFT(KC_GRV)), LCTL(KC_RGHT), LGUI(KC_5), LGUI(KC_6), LGUI(KC_7), LGUI(KC_8), LSFT(LCTL(KC_TAB)), LCTL(KC_TAB),  _______, \
      KC_TAB, LGUI(KC_A), LGUI(KC_S), KC_UP, LGUI(KC_F), LGUI(KC_T),           LGUI(KC_Y), LGUI(KC_U), LGUI(KC_I), LGUI(KC_O), LGUI(KC_P), LGUI(KC_BSPC), \
      MEXT1, LGUI(KC_LEFT),    KC_LEFT,    KC_DOWN,    KC_RGHT,    LGUI(KC_RGHT),                      LGUI(KC_H),    KC_BSPC,    LSFT(LALT(KC_K)), LSFT(LALT(KC_L)), LSFT(LALT(KC_P)),    KC_DEL, \
      KC_LCTL, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(KC_B), LGUI(KC_LBRC), LGUI(KC_RBRC), LGUI(KC_K), LGUI(KC_M), LGUI(KC_COMM), LGUI(KC_DOT), LGUI(KC_SLSH), _______, \
      _______, _______, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, LGUI(KC_SPC), LGUI(KC_ENT), MEXT2, KC_ESC, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_UP), LGUI(KC_RGHT) \
      ),

  /* MExt2
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|      |      |      |             |      |  -   |  =   |      |      | Pscr |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |Aud on|Audoff| Mac  |             | Win  |Qwerty|MQwert|      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      | Ctrl | Alt  | GUI  |      |Shift |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_MEXT2] =  LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      _______, RESET,   RGBRST,  _______, _______, _______,                   _______, KC_MINS, KC_EQL , _______, _______, LGUI(LSFT(KC_4)), \
      _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, QWERTY,  MQWERTY, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, KC_LCTL, KC_LALT, KC_LGUI, _______, KC_LSFT, _______, _______, _______, RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD \
      )
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case EXT1:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(16);
          #endif
        }
        layer_on(_EXT1);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_EXT1);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case EXT2:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
          #endif
        }
        layer_on(_EXT2);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_EXT2);
        TOG_STATUS = false;
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case MQWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_MQWERTY);
      }
      return false;
      break;
    case MEXT1:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(16);
          #endif
        }
        layer_on(_MEXT1);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_MEXT1);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case MEXT2:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(15);
          #endif
        }
        layer_on(_MEXT2);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_MEXT2);
        TOG_STATUS = false;
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(35);
__attribute__ ((weak))
void led_test_init(void) {}

void matrix_scan_user(void) {
     led_test_init();
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_EXT1 (1<<_EXT1)
#define L_EXT2 (1<<_EXT2)
#define L_MBASE (1<<_MQWERTY)
#define L_MEXT1 (1<<_MEXT1)
#define L_MEXT2 (1<<_MEXT2)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Win/Linux"));
           break;
        case L_MBASE:
           matrix_write_P(matrix, PSTR("Mac"));
           break;
        case L_EXT1:
        case L_MEXT1:
           matrix_write_P(matrix, PSTR("Ext1"));
           break;
        case L_EXT2:
        case L_MEXT2:
           matrix_write_P(matrix, PSTR("Ext2"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

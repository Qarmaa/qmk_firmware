#include QMK_KEYBOARD_H

bool is_alt_tab_active = false;
bool is_lang_active = false;
uint16_t lang_timer = 0;
uint16_t alt_tab_timer = 0;
uint16_t tt_paste_timer;
uint16_t copy_timer = 0;
uint16_t paste_timer = 0;
uint16_t del_timer = 0;
uint16_t ps_timer = 0;
uint16_t sae_timer = 0;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _MN 0
#define _SET 1
#define _MCR 2
#define _AEG 3
#define _GEN 4
#define _PT 5

enum custom_keycodes {
  SUB_START = SAFE_RANGE,
  SUB_END,
  PREV_SUB,
  NEXT_SUB,
  CF_SHIFT,
  SET_START,
  SET_END,
  PREV_FRAME,
  NEXT_FRAME,
  S_SHIFT,
  REDO,
  PLAY,
  NEWLINE,
  SAE,
  DEL_SUB,
  SPLIT_SUB,
  JOIN_SUB,
  COPY,
  PASTE,
  TT_REN_A,
  TT_REN_B,
  SCR_PY_PATH,
  WN_PREV_D,
  WN_NEXT_D,
  WN_ALT_TAB,
  WN_LANG,
  WN_BS,
  WN_PS,
  SHIFT_E,
  PT_TRIM,
  PT_NOTE,
  PT_SOLO,
  PT_MUTE,
  PT_BOUNCE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,-------------------.
   * |Esc |TAB | FN | BS |
   * |----|----|----|----|
   * | NL | /  | *  | -  |
   * |----|----|----|----|
   * | 7  | 8  | 9  |    |
   * |----|----|----| +  |
   * | 4  | 5  | 6  |    |
   * |----|----|----|----|
   * | 1  | 2  | 3  |    |
   * |----|----|----| En |
   * |   0     | .  |    |
   * `-------------------'
   */

  /* Defaul layer with non-standart numpad
   * First row is for layer togling and activating
   * Other keys are pretty standart except for last colume
   * whitch is modyfied for use as orto:
   * Minus, BS, Plus, Comma, En
   */
[_MN] = LAYOUT_ortho_6x4(
  KC_ESC,     KC_TRNS,  TG(_MCR),  MO(_SET), \
  KC_NLCK,    KC_PSLS,  KC_PAST,   KC_BSPC, \
  KC_P7,      KC_P8,    KC_P9,     KC_PMNS, \
  KC_P4,      KC_P5,    KC_P6,     KC_PPLS, \
  KC_P1,      KC_P2,    KC_P3,     KC_TAB, \
  KC_P0,      KC_NO,    KC_PDOT,   KC_PENT), 

[_SET] = LAYOUT_ortho_6x4(
  _______,    _______,  _______,   _______, \
  RGB_MOD,    RGB_M_P,  BL_TOGG,   _______, \
  RGB_HUD,    RGB_HUI,  BL_ON,     _______, \
  RGB_SAD,    RGB_SAI,  BL_OFF,    _______, \
  RGB_VAD,    RGB_VAI,  BL_STEP,   _______, \
  _______,    _______,  _______,   RESET), 

[_MCR] = LAYOUT_ortho_6x4(
  KC_NO,    KC_NO,    KC_TRNS, KC_NO, \
  TG(_AEG), TG(_GEN), TG(_PT), KC_NO, \
  KC_NO,    KC_NO,    KC_NO,   KC_NO, \
  KC_NO,    KC_NO,    KC_NO,   KC_NO, \
  KC_NO,    KC_NO,    KC_NO,   KC_NO, \
  KC_NO,    KC_NO,    KC_NO,   KC_NO),

[_AEG] = LAYOUT_ortho_6x4(
  SAE,        REDO,      KC_TRNS,     SHIFT_E, \
  KC_TRNS,    SPLIT_SUB, JOIN_SUB,    DEL_SUB, \
  SUB_START,  PREV_SUB,  SUB_END,     COPY, \
  PREV_FRAME, S_SHIFT,   NEXT_FRAME,  PASTE, \
  SET_START,  NEXT_SUB,  SET_END,     KC_NO, \
  NEWLINE,    KC_NO,     CF_SHIFT,    PLAY),

[_GEN] = LAYOUT_ortho_6x4(
  SAE,       KC_NO,     KC_NO,       WN_PS, \
  KC_NO,     KC_TRNS,   KC_NO,       WN_BS, \
  TT_REN_A,  TT_REN_B,  SCR_PY_PATH, COPY, \
  KC_NO,     KC_NO,     KC_NO,       PASTE, \
  WN_PREV_D, KC_NO,     WN_NEXT_D,   WN_ALT_TAB, \
  KC_NO,     KC_NO,     WN_LANG,     KC_PENT),

[_PT] = LAYOUT_ortho_6x4(
  KC_ESC,     PT_NOTE,  PT_TRIM,   PT_BOUNCE, \
  KC_2,       KC_3,     KC_TRNS,   KC_DELETE, \
  KC_R,       KC_T,     KC_LSHIFT, PT_MUTE, \
  KC_A,       KC_S,     KC_B,      PT_SOLO, \
  KC_D,       KC_G,     KC_F,      KC_TAB, \
  KC_RCTL,    KC_LGUI,  KC_Z,      KC_SPACE),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BL_TOGG:
       if (record->event.pressed) {
          cospad_bl_led_togg();
       }
       return false;
    case BL_ON:
       if (record->event.pressed) {
          cospad_bl_led_on();
       }
       return false;
    case BL_OFF:
       if(record->event.pressed) {
          cospad_bl_led_off();
       }
       return false;
    // Aegisub Hotkeys
    case SUB_START:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("1"));
      }
      return false;
    case SUB_END:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("2"));
      }
      return false;
    case PREV_SUB:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_KP_8));
      } else {
        SEND_STRING(SS_UP(X_LCTRL)SS_UP(X_KP_8));
      }
      return false;
    case NEXT_SUB:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_KP_2));
      } else {
        SEND_STRING(SS_UP(X_LCTRL)SS_UP(X_KP_2));
      }
      return false;
    case CF_SHIFT:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("5"));
      }
      return false;
    case SET_START:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("3"));
      }
      return false;        
    case SET_END:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("4"));
      }
      return false;
    case PREV_FRAME:
      if (record->event.pressed) {
        SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_KP_4));
      } else {
        SEND_STRING(SS_UP(X_LCTRL)SS_UP(X_KP_4));
      }
      return false;
    case NEXT_FRAME:
      if (record->event.pressed) {
      SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_KP_6));
      } else {
        SEND_STRING(SS_UP(X_LCTRL)SS_UP(X_KP_6));
      }
      return false; 
    case S_SHIFT:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("6"));
      }
      return false;
    case REDO:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("z"));
      }
      return false;
    case PLAY:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("p"));
      }
      return false;
    case NEWLINE:
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT(SS_TAP(X_ENTER)));
      }
      return false;
    case SAE:
      if (record->event.pressed) {
        sae_timer = timer_read();
      } else {
        if IS_LAYER_ON(_AEG) {
          if (timer_elapsed(sae_timer) > 200) {
            layer_off(_AEG);
            layer_on(_MCR);
            layer_invert(_GEN);
          } else {
            SEND_STRING(SS_LCTRL("s")SS_LCTRL("q"));
          }
        } else if IS_LAYER_ON(_GEN) {
          if (timer_elapsed(sae_timer) > 2000) {
            layer_off(_GEN);
            layer_off(_MCR);
          } else if (timer_elapsed(sae_timer) > 200) {
            layer_off(_GEN);
            layer_on(_MCR);
            layer_invert(_AEG);
          } else {
            SEND_STRING(SS_TAP(X_ESCAPE));
          }
        }
      }
      return false;
    case DEL_SUB:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL(SS_TAP(X_DELETE)));
      }
      return false;
    case SPLIT_SUB:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("d"));
      }
      return false;
    case JOIN_SUB:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("\\"));
      }
      return false;
    case SHIFT_E:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("i"));
      }
    case COPY:
      if (record->event.pressed) {
        copy_timer = timer_read();
      } else {
        if (timer_elapsed(copy_timer) > 200) { 
          SEND_STRING(SS_LCTRL("a")SS_LCTRL("c"));
        } else {
          SEND_STRING(SS_LCTRL("c"));
        }
      }
      return false;
    case PASTE:
      if (record->event.pressed) {
        paste_timer = timer_read();
      } else {
        if (timer_elapsed(paste_timer) > 200) { 
          SEND_STRING(SS_LCTRL("a")SS_LCTRL("v"));
        } else {
          SEND_STRING(SS_LCTRL("v"));
        }
      }
      return false;
    // General Macro GRP
    case TT_REN_A:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_F2)SS_LCTRL("c")SS_TAP(X_ESCAPE));
      }
      return false;
    case TT_REN_B:
      if (record->event.pressed) {
        tt_paste_timer = timer_read();
        SEND_STRING(SS_TAP(X_F2)SS_LCTRL("v"));
      } else {
        if (timer_elapsed(tt_paste_timer) < 200) {
          SEND_STRING(SS_TAP(X_ENTER));
        }   
      }
      return false;
    case SCR_PY_PATH:
      if (record->event.pressed) {
          SEND_STRING("C:\\Users\\Nikolas\\Desktop\\VSPort371\\python.exe ");
      }
      return false;
    case WN_PREV_D:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_LEFT))));
      }
      return false;
    case WN_NEXT_D:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_RIGHT))));
      }
      return false;
    case WN_BS:
      if (record->event.pressed) {
        del_timer = timer_read();
      } else {
        if (timer_elapsed(del_timer) > 200) { 
          SEND_STRING(SS_LCTRL(SS_TAP(X_BSPACE)));
        } else {
          SEND_STRING(SS_TAP(X_BSPACE));
        }
      }
      return false;
    case WN_PS:
      if (record->event.pressed) {
        ps_timer = timer_read();
      } else {
        if (timer_elapsed(ps_timer) > 200) {
          SEND_STRING(SS_LALT(SS_TAP(X_PSCREEN)));
        } else {
          SEND_STRING(SS_TAP(X_PSCREEN));
        }
      }
      return false;
    // PT Macro
     case PT_MUTE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("m"));
      }
      return false;  
     case PT_SOLO:
      if (record->event.pressed) {
        SEND_STRING(SS_LSFT("s"));
      }
      return false;
     case PT_TRIM:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("t"));
      }
      return false;
     case PT_NOTE:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LCTRL("g")));
        SEND_STRING(SS_LCTRL(SS_LSFT("r")));
      }
      return false;
     case PT_BOUNCE:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_LCTRL("b")));
      }
      return false;
    case WN_ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        } 
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case WN_LANG:
      if (record->event.pressed) {
        if (!is_lang_active) {
          is_lang_active = true;
          register_code(KC_LGUI);
        } 
        lang_timer = timer_read();
        register_code(KC_SPACE);
      } else {
        unregister_code(KC_SPACE);
      }
      break;
   }
   return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 500) {
      unregister_code(KC_LALT);
      unregister_code(KC_TAB);
      is_alt_tab_active = false;
    }
  }
  if (is_lang_active) {
    if (timer_elapsed(lang_timer) > 500) {
      unregister_code(KC_LGUI);
      unregister_code(KC_SPACE);
      is_lang_active = false;
    }
  }
}

uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
    case _MN:
          rgblight_setrgb(0xFF, 0x00, 0x00);
          rgblight_mode_noeeprom(1);
        break;
    case _SET:
          rgblight_setrgb(0xFF, 0xFF, 0xFF);
          rgblight_mode_noeeprom(1);
        break;
    case _MCR:
          rgblight_setrgb(0xFF,  0x00, 0x00);
          rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);
        break;
    case _GEN:
          rgblight_setrgb(0x00,  0xFF, 0x00);
          rgblight_mode_noeeprom(1);
        break;
    case _AEG:
          rgblight_setrgb(0xFF,  0x00, 0x00);
          rgblight_mode_noeeprom(1);
        break;
    default:
          rgblight_setrgb(0xFF, 0x00, 0x00);
          rgblight_mode_noeeprom(1);
        break;
    }
  return state;
}

#include "quantum.h"

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  // https://beta.docs.qmk.fm/using-qmk/simple-keycodes/feature_advanced_keycodes#alt-escape-for-alt-tab-id-alt-escape-for-alt-tab
  if (get_mods() & MOD_MASK_CTRL) { // If CTRL is held
    uint8_t mod_state = get_mods(); // Store all  modifiers that are held
    unregister_mods(MOD_MASK_CTRL); // Immediately unregister the CRTL key (don't send CTRL-PgDn) - del_mods doesn't work here (not immediate)
    if (clockwise) {
      tap_code(KC_PGDN);
    } else {
      tap_code(KC_PGUP);
    }
    set_mods(mod_state); // Add back in the CTRL key - so ctrl-key will work if ctrl was never released after paging.
  } else if (get_mods() & MOD_MASK_SHIFT) {
    uint8_t mod_state = get_mods();
    unregister_mods(MOD_MASK_SHIFT);
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE   // If using the mouse scroll - make sure MOUSEKEY is enabled
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_VOLU);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_VOLD);
      #endif
    }
    set_mods(mod_state);
  } else if (clockwise) { // All else volume.
    tap_code(KC_VOLU);
  } else {
    tap_code(KC_VOLD);
  }
  return true;
}
#endif //ENCODER_ENABLE

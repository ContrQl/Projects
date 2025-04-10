// Default layout for WT60-D
#include QMK_KEYBOARD_H
#define OS_MACOS

enum layer_names {
    _BASE = 0,
    _LAYER1,
    _LAYER2
};

enum custom_keycodes {
	DSKT_TOGGLE = SAFE_RANGE, // DESKTOP TOGGLE
    AP_GLOB, // APPLE GLOBE
    LAYER, // CHANGE BETWEEN BASE AND LAYER 2
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_env_1 = true;  // Track current environment
    static bool layer2_active = false; // Variable to keep track of Layer 2 status

    switch (keycode) {
        // Function to trigger Apple Globe Fn (which is MO(1)) + G (which is AP_GLOB)

        case AP_GLOB:
            host_consumer_send(record->event.pressed ? AC_NEXT_KEYBOARD_LAYOUT_SELECT : 0);
            return false; // Skip normal processing

        // Function to switch between desktops in a 2 monitor setup, with desktop 1+3 in first task and 2+4 in second task

        case DSKT_TOGGLE:
            if (record->event.pressed) {
                if (is_env_1) {
                    // Switch to Environment 2: Alt+2 then Alt+4
                    register_code(KC_LALT);
                    tap_code(KC_2);
                    unregister_code(KC_LALT);

                    wait_ms(100);  // Ensure reliable switching

                    register_code(KC_LALT);
                    tap_code(KC_4);
                    unregister_code(KC_LALT);
                } else {
                    // Switch to Environment 1: Alt+1 then Alt+3
                    register_code(KC_LALT);
                    tap_code(KC_1);
                    unregister_code(KC_LALT);

                    wait_ms(100);

                    register_code(KC_LALT);
                    tap_code(KC_3);
                    unregister_code(KC_LALT);
                }
                is_env_1 = !is_env_1;  // Toggle state
            }
            return false;  // Skip normal processing

        // Function to toggle between layer 0 and 2 using Fn (which is MO(1)) + L (which is LAYER)

        case LAYER:
            if (record->event.pressed) {
                if (layer2_active) {
                    layer_off(_LAYER2);  // Deactivate Layer 2
                } else {
                    layer_on(_LAYER2);   // Activate Layer 2
                }
                layer2_active = !layer2_active;  // Toggle the state of Layer 2
            }
            return false;  // Skip normal processing

    }
    return true;  // Process other keys normally
}

// Keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Main or Base Layer
[0] = LAYOUT_all(
	KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
	KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
	KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
	KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
	KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, MO(1),   KC_RCTL),

// Momentary Layer with Macros
[1] = LAYOUT_all(
	KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS,  KC_TRNS,
	DSKT_TOGGLE, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_F13, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, AP_GLOB, KC_TRNS, KC_TRNS, KC_TRNS, LAYER, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

// Second Layer (Currently Unused)
[2] = LAYOUT_all(
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
	KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};
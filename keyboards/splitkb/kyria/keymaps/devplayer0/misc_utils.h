#pragma once

#include QMK_KEYBOARD_H

typedef void (*td_triple_tap_fn_t)(void);
typedef struct td_triple_tap_action {
    uint16_t kc;
    td_triple_tap_fn_t action;
} td_triple_tap_action_t;

void triple_tap_handle_dance_finished(qk_tap_dance_state_t *state, void *user_data);

#define ACTION_TAP_DANCE_TRIPLE_TAP(kc, action) \
    { .fn = {NULL, triple_tap_handle_dance_finished, NULL}, .user_data = (void*)&((td_triple_tap_action_t){kc, action}), }

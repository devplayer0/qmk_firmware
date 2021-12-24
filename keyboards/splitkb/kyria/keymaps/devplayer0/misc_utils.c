#include "misc_utils.h"

void triple_tap_handle_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_triple_tap_action_t *config = (td_triple_tap_action_t*)user_data;
    if (state->count == 1) {
        tap_code(config->kc);
    } else if (state->count == 3) {
        config->action();
    } else {
        reset_tap_dance(state);
    }
}

#pragma once

void emotes_finished(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [TD_EMOTES] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, emotes_finished, NULL),
};

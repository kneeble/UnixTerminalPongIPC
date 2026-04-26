#include "game_state.h"

void init_game(GameState *state) {
    state->ball_x = 512;
    state->ball_y = 384;
    state->ball_dx = 1;
    state->ball_dy = 1;

    state->paddle1_y = 300;
    state->paddle2_y = 300;

    state->score1 = 0;
    state->score2 = 0;
}

void update_game(GameState *state) {
    // TODO: ball movement, collisions
}

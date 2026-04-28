#include "game.h"

#define BALL_SPEED 4

void init_game(GameState *state) {
    state->ball_x = SCREEN_WIDTH / 2;
    state->ball_y = SCREEN_HEIGHT / 2;
    state->ball_dx = BALL_SPEED;
    state->ball_dy = BALL_SPEED;

    state->paddle1_y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    state->paddle2_y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;

    state->score1 = 0;
    state->score2 = 0;
}

static void reset_ball(GameState *state, int dx) {
    state->ball_x = SCREEN_WIDTH / 2;
    state->ball_y = SCREEN_HEIGHT / 2;
    state->ball_dx = dx;
    state->ball_dy = BALL_SPEED;
}

void update_game(GameState *state) {
    state->ball_x += state->ball_dx;
    state->ball_y += state->ball_dy;

    if (state->ball_y <= 0) {
        state->ball_y = 0;
        state->ball_dy = -state->ball_dy;
    }
    if (state->ball_y + BALL_SIZE >= SCREEN_HEIGHT) {
        state->ball_y = SCREEN_HEIGHT - BALL_SIZE;
        state->ball_dy = -state->ball_dy;
    }

    int p1_x = PADDLE_X_OFFSET;
    if (state->ball_dx < 0 &&
        state->ball_x <= p1_x + PADDLE_WIDTH &&
        state->ball_x + BALL_SIZE >= p1_x &&
        state->ball_y + BALL_SIZE >= state->paddle1_y &&
        state->ball_y <= state->paddle1_y + PADDLE_HEIGHT) {
        state->ball_x = p1_x + PADDLE_WIDTH;
        state->ball_dx = -state->ball_dx;
    }

    int p2_x = SCREEN_WIDTH - PADDLE_X_OFFSET - PADDLE_WIDTH;
    if (state->ball_dx > 0 &&
        state->ball_x + BALL_SIZE >= p2_x &&
        state->ball_x <= p2_x + PADDLE_WIDTH &&
        state->ball_y + BALL_SIZE >= state->paddle2_y &&
        state->ball_y <= state->paddle2_y + PADDLE_HEIGHT) {
        state->ball_x = p2_x - BALL_SIZE;
        state->ball_dx = -state->ball_dx;
    }

    if (state->ball_x < 0) {
        state->score2++;
        reset_ball(state, BALL_SPEED);
    }
    if (state->ball_x + BALL_SIZE > SCREEN_WIDTH) {
        state->score1++;
        reset_ball(state, -BALL_SPEED);
    }
}

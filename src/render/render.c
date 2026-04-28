#include "render.h"

extern void drawPixel(int x, int y, int color);

void render(GameState *state) {
    int p1_x = PADDLE_X_OFFSET;
    int p2_x = SCREEN_WIDTH - PADDLE_X_OFFSET - PADDLE_WIDTH;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int color = COLOR_BG;
            if (x >= p1_x && x < p1_x + PADDLE_WIDTH &&
                y >= state->paddle1_y && y < state->paddle1_y + PADDLE_HEIGHT) {
                color = COLOR_PADDLE1;
            } else if (x >= p2_x && x < p2_x + PADDLE_WIDTH &&
                       y >= state->paddle2_y && y < state->paddle2_y + PADDLE_HEIGHT) {
                color = COLOR_PADDLE2;
            } else if (x >= state->ball_x && x < state->ball_x + BALL_SIZE &&
                       y >= state->ball_y && y < state->ball_y + BALL_SIZE) {
                color = COLOR_BALL;
            }
            drawPixel(x, y, color);
        }
    }
}

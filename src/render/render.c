#include "render.h"

extern void drawPixel(int x, int y, int color);

static void fill_rect(int x, int y, int w, int h, int color) {
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            drawPixel(i, j, color);
        }
    }
}

void render(GameState *state) {
    fill_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BG);

    int p1_x = PADDLE_X_OFFSET;
    fill_rect(p1_x, state->paddle1_y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_FG);

    int p2_x = SCREEN_WIDTH - PADDLE_X_OFFSET - PADDLE_WIDTH;
    fill_rect(p2_x, state->paddle2_y, PADDLE_WIDTH, PADDLE_HEIGHT, COLOR_FG);

    fill_rect(state->ball_x, state->ball_y, BALL_SIZE, BALL_SIZE, COLOR_FG);
}

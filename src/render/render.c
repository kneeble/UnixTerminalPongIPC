#include "render.h"
#include "logo.h"

extern void drawPixel(int x, int y, int color);

#define LOGO_X ((SCREEN_WIDTH - LOGO_WIDTH) / 2)
#define LOGO_Y ((SCREEN_HEIGHT - LOGO_HEIGHT) / 2)

void render(GameState *state) {
    int p1_x = PADDLE_X_OFFSET;
    int p2_x = SCREEN_WIDTH - PADDLE_X_OFFSET - PADDLE_WIDTH;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int color = COLOR_BG;

            if (x >= LOGO_X && x < LOGO_X + LOGO_WIDTH &&
                y >= LOGO_Y && y < LOGO_Y + LOGO_HEIGHT) {
                int pixel = luc_logo[(y - LOGO_Y) * LOGO_WIDTH + (x - LOGO_X)];
                if (pixel != LOGO_TRANSPARENT) {
                    color = pixel;
                }
            }

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

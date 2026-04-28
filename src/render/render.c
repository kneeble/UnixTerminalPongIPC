#include "render.h"
#include "logo.h"
#include "font.h"

extern void drawPixel(int x, int y, int color);

#define LOGO_X ((SCREEN_WIDTH - LOGO_WIDTH) / 2)
#define LOGO_Y ((SCREEN_HEIGHT - LOGO_HEIGHT) / 2)

void int_to_str(int num, char *str) {
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    int temp = num;

    // count digits
    while (temp > 0) {
        temp /= 10;
        i++;
    }

    str[i] = '\0';

    // fill backwards
    while (num > 0) {
        str[--i] = '0' + (num % 10);
        num /= 10;
    }
}

void draw_char(int x, int y, char c, int color) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (font[(int)c][row] & (1 << (7 - col))) {
                drawPixel(x + col, y + row, color);
            }
        }
    }
}

void draw_string(int x, int y, const char *str, int color) {
    int i = 0;
    while (str[i]) {
        draw_char(x + i * 8, y, str[i], color);
        i++;
    }
}

void render(GameState *state) {
    int p1_x = PADDLE_X_OFFSET;
    int p2_x = SCREEN_WIDTH - PADDLE_X_OFFSET - PADDLE_WIDTH;

    // Draws game (backgrund, paddles, ball)
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
    // Score string build
    char s1[4];
    char s2[4];
    int_to_str(state->score1, s1);
    int_to_str(state->score2, s2);

    char score_text[16];
    int i = 0;

    for (int j = 0; s1[j]; j++) score_text[i++] = s1[j];
    score_text[i++] = ' ';
    score_text[i++] = ':';
    score_text[i++] = ' ';
    for (int j = 0; s2[j]; j++) score_text[i++] = s2[j];
    score_text[i] = '\0';

    // Draw score (top center)
    draw_string(SCREEN_WIDTH / 2 - 40, 10, score_text, 0x000000);

    // Draw joke (bottom left)
    draw_string(20, SCREEN_HEIGHT - 30, state->current_joke, 0x000000);
}

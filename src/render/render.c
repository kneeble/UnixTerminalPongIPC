#include "render.h"
#include "logo.h"
#include "font.h"

extern void drawPixel(int x, int y, int color);

#define LOGO_X ((SCREEN_WIDTH - LOGO_WIDTH) / 2)
#define LOGO_Y ((SCREEN_HEIGHT - LOGO_HEIGHT) / 2)
#define COLOR_TEXT 0x000000

static void int_to_str(int num, char *str) {
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    int temp = num;
    while (temp > 0) {
        temp /= 10;
        i++;
    }

    str[i] = '\0';

    while (num > 0) {
        str[--i] = '0' + (num % 10);
        num /= 10;
    }
}

static int str_len(const char *s) {
    int n = 0;
    while (s[n]) n++;
    return n;
}

void render(GameState *state) {
    int p1_x = PADDLE_X_OFFSET;
    int p2_x = SCREEN_WIDTH - PADDLE_X_OFFSET - PADDLE_WIDTH;

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

    int score_len = str_len(score_text);
    int joke_len = str_len(state->current_joke);

    int score_x = SCREEN_WIDTH / 2 - score_len * 4;
    int score_y = 10;
    int joke_x = 20;
    int joke_y = SCREEN_HEIGHT - 30;

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        int in_logo_row = (y >= LOGO_Y && y < LOGO_Y + LOGO_HEIGHT);
        int logo_row_base = (y - LOGO_Y) * LOGO_WIDTH;

        int in_p1_row = (y >= state->paddle1_y && y < state->paddle1_y + PADDLE_HEIGHT);
        int in_p2_row = (y >= state->paddle2_y && y < state->paddle2_y + PADDLE_HEIGHT);
        int in_ball_row = (y >= state->ball_y && y < state->ball_y + BALL_SIZE);

        int in_score_row = (y >= score_y && y < score_y + 8);
        int score_row = y - score_y;
        int in_joke_row = (y >= joke_y && y < joke_y + 8);
        int joke_row = y - joke_y;

        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int color = COLOR_BG;

            if (in_logo_row && x >= LOGO_X && x < LOGO_X + LOGO_WIDTH) {
                int pixel = luc_logo[logo_row_base + (x - LOGO_X)];
                if (pixel != LOGO_TRANSPARENT) {
                    color = pixel;
                }
            }

            if (in_p1_row && x >= p1_x && x < p1_x + PADDLE_WIDTH) {
                color = COLOR_PADDLE1;
            } else if (in_p2_row && x >= p2_x && x < p2_x + PADDLE_WIDTH) {
                color = COLOR_PADDLE2;
            } else if (in_ball_row && x >= state->ball_x && x < state->ball_x + BALL_SIZE) {
                color = COLOR_BALL;
            }

            if (in_score_row && x >= score_x && x < score_x + score_len * 8) {
                int idx = (x - score_x) / 8;
                int col = (x - score_x) % 8;
                unsigned char ch = (unsigned char)score_text[idx] & 0x7f;
                if ((font[ch][score_row] >> (7 - col)) & 1) {
                    color = COLOR_TEXT;
                }
            }
            if (in_joke_row && x >= joke_x && x < joke_x + joke_len * 8) {
                int idx = (x - joke_x) / 8;
                int col = (x - joke_x) % 8;
                unsigned char ch = (unsigned char)state->current_joke[idx] & 0x7f;
                if ((font[ch][joke_row] >> (7 - col)) & 1) {
                    color = COLOR_TEXT;
                }
            }

            drawPixel(x, y, color);
        }
    }
}

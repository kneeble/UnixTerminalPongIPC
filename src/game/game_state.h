#ifndef GAME_STATE_H
#define GAME_STATE_H

#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   768

#define PADDLE_WIDTH    24
#define PADDLE_HEIGHT   80
#define PADDLE_X_OFFSET 32

#define BALL_SIZE       12

#define COLOR_BG        0xffffff
#define COLOR_PADDLE1   0x862633
#define COLOR_PADDLE2   0xffc72c
#define COLOR_BALL      0x000000

typedef struct {
    int ball_x;
    int ball_y;
    int ball_dx;
    int ball_dy;

    int paddle1_y;
    int paddle2_y;

    int score1;
    int score2;

} GameState;

#endif

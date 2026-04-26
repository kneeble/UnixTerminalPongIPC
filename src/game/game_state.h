#ifndef GAME_STATE_H
#define GAME_STATE_H

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

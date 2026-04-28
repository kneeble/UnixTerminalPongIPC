#include "game.h"

#define BALL_SPEED 4

static const char *jokes[] = {
    "I would tell you a UDP joke, but you got some latency on the line.",
    "How many computer programmers does it take to change a light bulb? None, that is a hardware problem.",
    "Why do number jokes not work in Octal? Because 7 10 11!",
    "What do you call 8 Hobbits? A Hobbyte.",
    "How much money do I owe you, said ProgammerA. 500 dollars, said ProgrammerB. Shall I reound it to 512?",
    "Why do mathematicians always confuse Halloween and Christmas? Because 31 Oct equals 25 Dec.",
    "Why did c++ decide to not go out with c? Because quite frankly, c just has no class",
    "And on the seventh day, He exited from append mode.",
    "Why is the number 237 magical? Because it is Hex ED",
    "How do robots eat pizza? One byte at a time.",
    "How do dolphins compute? They use a Central Porpoising Unit.",
    "I have a CS joke but it does not compute.",
    "I have a joke about my work as a software engineer, but it only works for me.",
    "What do you get if you cross a computer with an elephant? Lots of memory",
};

void copy_string(char *dest, const char *src, int max_len) {
    int i = 0;
    while (i < max_len - 1 && src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

#define NUM_JOKES (sizeof(jokes) / sizeof(jokes[0]))

static int pseudo_rand = 0;

int get_random_index() {
    pseudo_rand = (pseudo_rand + 1) % NUM_JOKES;
    return pseudo_rand;
}

void set_random_joke(GameState *state) {
    int idx = get_random_index();
    copy_string(state->current_joke, jokes[idx], MAX_JOKE_LEN);
}

void init_game(GameState *state) {
    state->ball_x = SCREEN_WIDTH / 2;
    state->ball_y = SCREEN_HEIGHT / 2;
    state->ball_dx = BALL_SPEED;
    state->ball_dy = BALL_SPEED;

    state->paddle1_y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    state->paddle2_y = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;

    state->score1 = 0;
    state->score2 = 0;

    set_random_joke(state);
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
    	set_random_joke(state);
    }
    if (state->ball_x + BALL_SIZE > SCREEN_WIDTH) {
        state->score1++;
        reset_ball(state, -BALL_SPEED);
        set_random_joke(state);
    }
}

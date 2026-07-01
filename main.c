#include <stdio.h>
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 48

#define PADDLE_WIDTH_0 12

#define BRICK_ROWS 3
#define BRICK_COLUMNS 8
#define BRICK_WIDTH 6
#define BRICK_HEIGHT 3


typedef struct{ //ball
    float x, y;
    float vx, vy;
}Ball;
Ball ball;

typedef struct{ //bricks
    int health;
}Brick;
Brick brick[BRICK_ROWS][BRICK_COLUMNS];

typedef struct{ //paddle
    int x;
    int size;
}Paddle;
Paddle paddle;


void set_ball();
void set_bricks();
void set_paddle();
void gameInicialization();
void set_blank_screen();
void set_borders();
void draw_all();
const char* screen[SCREEN_HEIGHT][SCREEN_WIDTH];

int main () {
    draw_all();
    return 0;
}

//Initial values for game objects

void gameInicialization() {
    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.vx = 0.1f;
    ball.vy = -0.1f;


    paddle.x = (int) (SCREEN_WIDTH / 2);
    paddle.size = PADDLE_WIDTH_0;
}

void set_blank_screen() {
    int i, j;
    for (i = 0; i < SCREEN_HEIGHT; i++) {
        for (j = 0; j < SCREEN_WIDTH ; j++) {
            screen[i][j] = " ";
        }
    }
}

void set_borders() {

    //set roof
    int i;
    for (i = 1; (i + 1) < SCREEN_WIDTH; i++) {
        screen[0][i] = "═";
    }

    //set upper corners
    screen[0][0] = "╔";
    screen[0][SCREEN_WIDTH-1] = "╗";

    //set sides
    int k;
    for (k = 1; k < SCREEN_HEIGHT; k++) {
        screen[k][0] = "║";
        screen[k][SCREEN_WIDTH - 1] = "║";
    }

    //Bottom will remain uncovered
}

void set_paddle() {
    int i;
    for (i = 0; i < paddle.size; i++) {
        int px = paddle.x + i;
        screen[SCREEN_HEIGHT - 2][px] = "▀";
    }
}

void set_ball () {
    screen[(int)ball.y][(int)ball.x] = "●";
}


//Everything is good until here



void set_bricks () {
    //generate all bricks with their health
    int i, j;
    for (i = 0; i < BRICK_ROWS; i++) {
        for (j = 0; j < BRICK_COLUMNS; j++) {
            brick[i][j].health = 1;

            int start_y = 1 + i * BRICK_HEIGHT;
            int start_x = 1 + j * BRICK_WIDTH;

            int k, l;

            for (k = 0; k < BRICK_HEIGHT; k++) {
                for (l = 0; l < BRICK_WIDTH; l++) {
                    screen[start_y + k][start_x + l] = "#";
                }
            }
            //draw the bricks
        }
    }
}

void draw_all() {
    //set screen
    gameInicialization();
    set_blank_screen();
    set_borders();
    set_paddle();
    set_ball();
    set_bricks();

    //print screen
    int i, j;
    for (i=0; i < SCREEN_HEIGHT; i++) {
        for (j=0; j < SCREEN_WIDTH; j++) {
            printf("%s", screen[i][j]);
        }
        printf("\n");
    }
}

#include <stdio.h>
#define SCREEN_WIDTH 48
#define SCREEN_HEIGHT 48

#define PADDLE_WIDTH_0 6

#define BRICK_ROWS 3
#define BRICK_COLUMNS 6


void set_blank_screen();
void set_borders();
void draw_all();
const char* screen[SCREEN_WIDTH][SCREEN_HEIGHT];
int main () {
    draw_all();
    return 0;
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

void draw_all() {
    //set screen
    set_blank_screen();
    set_borders();

    //print screen
    int i, j;
    for (i=0; i < SCREEN_HEIGHT; i++) {
        for (j=0; j < SCREEN_WIDTH; j++) {
            printf("%s", screen[i][j]);
        }
        printf("\n");
    }
}

// to test in windows 
#ifdef _WIN32
    #include <windows.h>
#endif

#include <stdio.h>
#include <unistd.h>
#ifdef _WIN32
#include <pdcurses.h> //used to render and get inputs whitout stoping the program execution 
#endif
#ifndef _WIN32
#include <ncurses.h> //used to render and get inputs whitout stoping the program execution 
#endif
//FOR A WIN USER 
#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 48

#define PADDLE_WIDTH_0 12

#define BRICK_ROWS 3
#define BRICK_COLUMNS 8
#define BRICK_WIDTH 6
#define BRICK_HEIGHT 2

short int game_active = 1;

//------- STRUCTURES -------

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


//------- FUNCTION DECLARATIONS -------

void set_ball();
void set_bricks();
void set_paddle();
void gameInicialization();
void set_blank_screen();
void set_borders();
void draw_all();
void ball_update();
void paddle_update(int c);
const char* screen[SCREEN_HEIGHT][SCREEN_WIDTH];

int main () {
    //maybe it's not necessary if I use ncurses
  //  #ifdef _WIN32 // to import the simbols used into windows console
  //      SetConsoleOutputCP(CP_UTF8);
   // #endif


    //------inicialization of ncurses-----
    initscr();
    cbreak(); 
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    gameInicialization();

    while (game_active == 1) {
        int c= getch();
        draw_all();
        ball_update();
        paddle_update(c);
        usleep(640000);
    }
    endwin();
    printf("Game Over!\n");
    // should go to the menu (pause state)
}

//Initial values for game objects

void gameInicialization() {
    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.vx = 1.0f;
    ball.vy = 1.0f;

    paddle.x = (int) (SCREEN_WIDTH / 2);
    paddle.size = PADDLE_WIDTH_0;
    
    //BRICKS health
    int i,j;
    for (i = 0; i < BRICK_ROWS; i++) {
        for (j = 0; j < BRICK_COLUMNS; j++) {
            brick[i][j].health = 1;
        }
    } 

}




//------- RENDERS -------

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
    for (i = 1; i <= SCREEN_WIDTH; i++) {
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



void set_bricks () {
    int i, j;
    for (i = 0; i < BRICK_ROWS; i++) {
        for (j = 0; j < BRICK_COLUMNS; j++) {
           
            int start_y = 1 + i * BRICK_HEIGHT;
            int start_x = 1 + j * BRICK_WIDTH;

            int k, l;
            //draws a brick
            for (k = 0; k < BRICK_HEIGHT; k++) {
                for (l = 0; l < BRICK_WIDTH; l++) {
                    screen[start_y + k][start_x + l] = "─";
                }
            }
            screen[start_y][start_x] = "┌";
            screen[start_y][start_x + BRICK_WIDTH - 1] = "┐";
            screen[start_y + BRICK_HEIGHT - 1][start_x] = "└";
            screen[start_y + BRICK_HEIGHT - 1][start_x + BRICK_WIDTH - 1] = "┘";
        }
    }
}

void draw_all() {
    //set screen
    set_blank_screen();
    set_borders();
    set_paddle();
    set_ball();
    set_bricks();

    //print screen
    int i, j;
    for (i=0; i < SCREEN_HEIGHT; i++) {
        for (j=0; j < SCREEN_WIDTH; j++) {
            mvprintw(i, j, "%s", screen[i][j]);
        }
    }
    refresh();//updates what's shown on console
}

//------- END RENDER -------


//------- GAME UPDATES -------

void ball_update() {

    //position update
    ball.x += ball.vx;
    ball.y += ball.vy;

    if ((int)ball.x <= 1 || (int)ball.x >= SCREEN_WIDTH - 2) {
        ball.vx *= -1;
    }
    if ((int)ball.y <= 1) {
        ball.vy *= -1;
    }
    if ((int)ball.y >= SCREEN_HEIGHT - 1) {
        game_active = 0;
    }
    //missing collision update with paddle
    //missing collision update with bricks

}

void paddle_update(int c) 
    {
      if ((c == 'a'|| c == 'A' || c== KEY_LEFT) && paddle.x > 1) 
      {
        paddle.x -= 1; // Move paddle left
        } else if ((c == 'd'||c=='D'|| c== KEY_RIGHT) && paddle.x < SCREEN_WIDTH - paddle.size - 1) 
        {
        paddle.x += 1; // Move paddle right
        }
    }




//missing input for paddle

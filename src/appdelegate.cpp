#include "appdelegate.h"

#include <ncurses.h>

#include <cstdlib>
#include <ctime>

// -------------------------- INTERNAL --------------------------
void onWindowResize(uint32_t* _w, uint32_t* _h) {
    *_w = COLS;
    *_h = LINES;
}

void updateFoodPosition(Food* food) {
    food->x = rand() % COLS;
    food->y = rand() % LINES;
}

// --------------------------- PUBLIC ---------------------------
AppDelegate::AppDelegate() {
    initscr();
    cbreak();
    keypad(stdscr, true);
    scrollok(stdscr, true);
    nodelay(stdscr, true);
    noecho();
    curs_set(0);
    srand(time(nullptr));    // rand() seed.

    onWindowResize(&WINDOW_W, &WINDOW_H);

    onSetup();
    onRender();
    onDestroy();

    endwin();
}

// --------------------------- PRIVATE --------------------------
void AppDelegate::onSetup() {
    food = new Food('0');
    updateFoodPosition(food);

    snake = new Snake('#', this);
    snake->x = WINDOW_W / 2;
    snake->y = WINDOW_H / 2;

    currentState = RUN;
}

void AppDelegate::onRender() {
    while (currentState == RUN) {
        clear();

        // render single snake
        mvaddch(snake->y, snake->x, snake->getCharacter());
        if (snake->onEat(*food)) {
            deltaTime -= 25;
            updateFoodPosition(food);
        }
        snake->onTick();

        // Render food
        mvaddch(food->y, food->x, food->getCharacter());
        refresh();

        napms(125);
        onKeyPressed();
    }
}

void AppDelegate::onKeyPressed() {
    switch (getch()) {
        case KEY_F(1): currentState = STOP; break;
        case KEY_RESIZE: onWindowResize(&WINDOW_W, &WINDOW_H); break;
        case 'W':
        case 'w':
        case KEY_UP: snake->updateDirection(Snake::NORTH); break;
        case 'D':
        case 'd':
        case KEY_RIGHT: snake->updateDirection(Snake::EAST); break;
        case 'S':
        case 's':
        case KEY_DOWN: snake->updateDirection(Snake::SOUTH); break;
        case 'A':
        case 'a':
        case KEY_LEFT: snake->updateDirection(Snake::WEST); break;
    }
}

void AppDelegate::onDestroy() {
    // TODO: Fix virtual destructor is not implemented yet.
    delete food;
    delete snake;
}
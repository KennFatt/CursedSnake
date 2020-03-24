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
    /** Randomize: 0 ... COLS */
    food->x = rand() % COLS;
    /** Randomize: 1 ... LINES - 1 */
    food->y = rand() % (LINES - 1) + 1;
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
    // Set default point to 0
    points = 0;

    // spawn new food object
    food = new Food('0');
    updateFoodPosition(food);

    // spawn the snake
    snake = new Snake('#', this);
    snake->x = WINDOW_W / 2;
    snake->y = WINDOW_H / 2;

    // change state to run
    currentState = RUN;
}

void AppDelegate::onRender() {
    while (currentState == RUN) {
        // Clear previous screen.
        clear();

        // render single snake
        if (snake->onEat(*food)) {
            points++;
            updateFoodPosition(food);
        }
        snake->onTick();
        for (auto& tail : snake->getTail()) {
            mvprintw(2, 0, "Rendering tail at: %lf, %lf", tail.x, tail.y);
            mvaddch(tail.y, tail.x, snake->getCharacter());
        }
        mvaddch(snake->y, snake->x, snake->getCharacter());

        // render snake tail
        // for (int i = 0; i < snake->getTail().size(); i++) {
        //     auto& currentTail = snake->getTail()[i];
        //     mvaddch(currentTail.y, currentTail.x, snake->getCharacter());
        // }

        // Render food
        mvaddch(food->y, food->x, food->getCharacter());

        // Render points
        mvprintw(0, 0, "Points: %d", points);
        // debug
        mvprintw(1, 0, "Total tail: %d", snake->getTail().size());

        refresh();
        if (snake->getDirection() == FacingDirection::NORTH
            || snake->getDirection() == FacingDirection::SOUTH) {
            napms(DELTA_TIME_VERTICAL);
        } else {
            napms(DELTA_TIME_HORIZONTAL);
        }
        onKeyPressed();
    }
}

void AppDelegate::onKeyPressed() {
    switch (getch()) {
        case KEY_F(1): currentState = STOP; break;
        case KEY_RESIZE:
            onWindowResize(&WINDOW_W, &WINDOW_H);
            updateFoodPosition(food);
            break;
        case 'W':
        case 'w':
        case KEY_UP: snake->updateDirection(FacingDirection::NORTH); break;
        case 'D':
        case 'd':
        case KEY_RIGHT: snake->updateDirection(FacingDirection::EAST); break;
        case 'S':
        case 's':
        case KEY_DOWN: snake->updateDirection(FacingDirection::SOUTH); break;
        case 'A':
        case 'a':
        case KEY_LEFT: snake->updateDirection(FacingDirection::WEST); break;
    }
}

void AppDelegate::onDestroy() {
    // TODO: Fix virtual destructor is not implemented yet.
    delete food;
    delete snake;
}
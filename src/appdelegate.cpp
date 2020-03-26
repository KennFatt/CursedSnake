#include "appdelegate.h"

#include <ncurses.h>
#include <unistd.h>

#include <array>
#include <cstdlib>
#include <ctime>

/** Re-define KEY_ENTER to an actual ENTER signal */
#ifdef KEY_ENTER
#undef KEY_ENTER
#define KEY_ENTER 0x0a
#endif

// -------------------------- INTERNAL --------------------------
/**
 * Update value of AppDelegate::WINDOW_W and AppDelegate::WINDOW_H
 * everytime the screen being resized by the user.
 */
void onWindowResize(AppDelegate* app) {
    app->WINDOW_W = COLS;
    app->WINDOW_H = LINES;
    app->WINDOW_W_CENTER = COLS / 2;
    app->WINDOW_H_CENTER = LINES / 2;
}

/**
 * Find new food's position
 *
 * @param food Pointer of food object.
 */
void updateFoodPosition(Food* food) {
    /** Randomize: 0 ... COLS */
    food->x = rand() % COLS;
    /** Randomize: 1 ... LINES - 1 */
    food->y = rand() % (LINES - 1) + 1;
}

// --------------------------- PUBLIC ---------------------------
AppDelegate::AppDelegate() {
    /** Let's start the ncruses mode */
    initscr();

    /**
     * Start ncurses color system
     * then use default color.
     */
    start_color();
    use_default_colors();

    /** Disable line buffering */
    cbreak();
    /** Enable and allow keypad signal (ENTER_KEY, ARROW, etc.) */
    keypad(stdscr, true);

    scrollok(stdscr, true);    // ?
    nodelay(stdscr, true);    // ?

    /** Set noecho mode */
    noecho();
    /** Set cursor mode to invisible */
    curs_set(0);
    /** Set random seed based on current execution time */
    srand(time(nullptr));

    /** Initialize color pairs */
    init_pair(1, COLOR_CYAN, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_YELLOW, -1);

    /** Update Window's size for the first time */
    onWindowResize(this);

    /** Start the game flow! */
    onSetup();
    onRender();
    onDestroy();

    endwin();
}

// --------------------------- PRIVATE --------------------------
void AppDelegate::onSetup() {
    /** Set start points = 0 */
    points = 0;

    /** Initialize food object and randomize its position */
    food = new Food('0');
    updateFoodPosition(food);

    /** Initialize snake object */
    snake = new Snake('#', &WINDOW_W, &WINDOW_H);

    /** Preparing to show the banner (entry interface) */
    isBannerShown = false;

    /** Continue to run the game! */
    currentState = RUN;
}

void AppDelegate::onRender() {
    while (currentState == RUN) {
        /** ALWAYS erase previous frame buffer */
        erase();

        /** Show banner (game entry interface) */
        if (!isBannerShown) {
            onShowBanner();
            /** Skip next frame */
            continue;
        }

        /** Get snake body parts */
        auto& snakeParts = snake->getParts();
        /**
         * Check whether snake is eating the food or keep moving forward.
         *
         * If the condition is FALSE, pop snake's body parts.
         * Because it will always generate (insert) new part each tick.
         */
        if (snake->onEat(*food)) {
            points++;
            updateFoodPosition(food);
        } else {
            /** Pop snake's latest body part */
            snake->getParts().pop_back();
        }

        /** Update snake's body part and control its movement */
        snake->onTick();

        /**
         * Render each body parts to the screen
         * and also check if the head collided with its own body.
         */
        for (unsigned i = 0; i < snakeParts.size(); i++) {
            /** Check if there is any collision occured */
            if (snake->hasCollisionWith(i)) {
                return onGameOver();
            }

            /** Rendering */
            attron(A_BOLD | COLOR_PAIR(4));
            mvaddch(snakeParts[i].y, snakeParts[i].x, snake->getCharacter());
            attroff(A_BOLD | COLOR_PAIR(4));
        }

        /** Render the food */
        attron(A_BOLD | COLOR_PAIR(3));
        mvaddch(food->y, food->x, food->getCharacter());
        attroff(A_BOLD | COLOR_PAIR(3));

        /** Render the GUI */
        mvprintw(0, 0, "Points: %d", points);

        /** Flushing current buffer to the screen */
        refresh();

        /** Listen to keyboard / keypad signal */
        onKeyPressed();

        /** Give it a time! */
        usleep(RENDER_DELTA_TIME);
    }
}

void AppDelegate::onKeyPressed() {
    switch (getch()) {
        /** DEBUG: F1 to force the game over */
        case KEY_F(1): return onGameOver();
        /** KEY_RESIZE triggered on every time screen got resized */
        case KEY_RESIZE:
            onWindowResize(this);
            updateFoodPosition(food);
            break;
        /** Update snake's direction */
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

void AppDelegate::onShowBanner() {
    // TODO: Move it somewhere else to prevent being instantiate every time
    const std::array<const char*, 3> authors = {
       "Arvito Putra", "Kennan Fattahillah", "Sahla Dzulfika"};
    const std::array<const char*, 6> ascii = {
       "   ___                        _   __             _        ",
       "  / __\\   _ _ __ ___  ___  __| | / _\\_ __   __ _| | _____ ",
       " / / | | | | \'__/ __|/ _ \\/ _` | \\ \\| \'_ \\ / _` | |/ / _ \\",
       "/ /__| |_| | |  \\__ \\  __/ (_| | _\\ \\ | | | (_| |   <  __/",
       "\\____/\\__,_|_|  |___/\\___|\\__,_| \\__/_| "
       "|_|\\__,_|_|\\_\\___|",
       "                                                          "};

    // TODO: What would happend if there is no more space to print ASCII?
    if (WINDOW_W >= 60) {
        for (unsigned i = 0; i < ascii.size(); i++) {
            attron(A_BOLD | COLOR_PAIR(1));
            mvprintw((WINDOW_H_CENTER - 6) + i, WINDOW_W_CENTER - 30, ascii[i]);
            attroff(A_BOLD | COLOR_PAIR(1));
        }
    }
    attron(A_BLINK | COLOR_PAIR(2));
    mvprintw(WINDOW_H_CENTER, WINDOW_W_CENTER - 14,
             "Please enter to continue...");
    attroff(A_BLINK | COLOR_PAIR(2));

    attron(A_UNDERLINE);
    mvprintw(WINDOW_H_CENTER + 3, WINDOW_W_CENTER - 6, "Developed by:");
    attroff(A_UNDERLINE);
    mvprintw(WINDOW_H_CENTER + 5, WINDOW_W_CENTER - 6, authors[0]);
    mvprintw(WINDOW_H_CENTER + 6, WINDOW_W_CENTER - 9, authors[1]);
    mvprintw(WINDOW_H_CENTER + 7, WINDOW_W_CENTER - 7, authors[2]);
    refresh();

    if (getch() == KEY_ENTER) {
        /** Update the flag */
        isBannerShown = true;
    }
}

void AppDelegate::onGameOver() {
    const std::array<const char*, 6> ascii = {
       "                                          __ ",
       " _____                  _____            |  |",
       "|   __|___ _____ ___   |     |_ _ ___ ___|  |",
       "|  |  | .'|     | -_|  |  |  | | | -_|  _|__|",
       "|_____|__,|_|_|_|___|  |_____|\\_/|___|_| |__|",
       "                                             "};

    while (currentState != STOP) {
        /** Don't forget to erase previous frame buffer */
        erase();

        if (WINDOW_W >= 46) {
            for (unsigned i = 0; i < ascii.size(); i++) {
                attron(A_BOLD | A_BLINK | COLOR_PAIR(3));
                mvprintw((WINDOW_H_CENTER - 6) + i, WINDOW_W_CENTER - 23,
                         ascii[i]);
                attroff(A_BOLD | A_BLINK | COLOR_PAIR(3));
            }
        }
        // TODO: What would happend if there is no more space to print ASCII?

        attron(COLOR_PAIR(4));
        mvprintw(WINDOW_H_CENTER + 2, WINDOW_W_CENTER - 12,
                 "Total points earned: %ld", points);
        attroff(COLOR_PAIR(4));

        attron(COLOR_PAIR(2));
        mvprintw(WINDOW_H_CENTER + 4, WINDOW_W_CENTER - 12,
                 "Please enter to exit...");
        attroff(COLOR_PAIR(2));
        refresh();

        if (getch() == KEY_ENTER) {
            /** End the game flow and exit */
            currentState = STOP;
        }

        usleep(RENDER_DELTA_TIME);
    }
}

void AppDelegate::onDestroy() {
    delete food;
    delete snake;
}
#include "appdelegate.h"

#include <ncurses.h>
#include <unistd.h>

#include <array>
#include <cstdlib>
#include <ctime>

#undef KEY_ENTER
#define KEY_ENTER 0x0a

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
    initscr();    // Init ncurses stdscr
    start_color();
    use_default_colors();
    cbreak();    // Disable line buffering
    keypad(stdscr, true);    // Allow keypad signal
    scrollok(stdscr, true);    // ?
    nodelay(stdscr, true);    // ?
    noecho();    // Disable keyboard input being printted on the screen
    curs_set(0);    // Set cursor to invisible
    srand(time(nullptr));    // rand() seed.

    init_pair(1, COLOR_CYAN, -1);
    init_pair(2, COLOR_GREEN, -1);
    init_pair(3, COLOR_RED, -1);
    init_pair(4, COLOR_YELLOW, -1);

    onWindowResize(this);

    onSetup();
    onRender();
    onDestroy();

    endwin();
}

// --------------------------- PRIVATE --------------------------
void AppDelegate::showBanner() {
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

    for (unsigned i = 0; i < ascii.size(); i++) {
        attron(A_BOLD | COLOR_PAIR(1));
        mvprintw((WINDOW_H_CENTER - 6) + i, WINDOW_W_CENTER - 30, ascii[i]);
        attroff(A_BOLD | COLOR_PAIR(1));
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
        currentState = RUN;
        isBannerShown = true;
    }
}

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

    // Set isBannerShown to false
    isBannerShown = false;

    // change state to run
    currentState = RUN;
}

void AppDelegate::onRender() {
    while (currentState == RUN) {
        erase();

        // Show banner
        // TODO: What would happend if there is no more space to print ASCII?
        if (!isBannerShown) {
            showBanner();
            continue;
        }

        // Getting snake's body parts to local variable.
        auto& snakeParts = snake->getParts();

        // Check whether snake is eating the food or keep moving
        if (snake->onEat(*food)) {
            points++;
            updateFoodPosition(food);
        } else {
            // Remove snake's last body parts when it keep moving
            snake->getParts().pop_back();
        }

        // Update snake movement
        snake->onTick();

        // Rendering snake whole body parts
        // and check if there any collision occured
        for (unsigned i = 0; i < snakeParts.size(); i++) {
            if (snake->hasCollisionWith(i)) {
                onGameOver();
            }
            attron(A_BOLD | COLOR_PAIR(4));
            mvaddch(snakeParts[i].y, snakeParts[i].x, snake->getCharacter());
            attroff(A_BOLD | COLOR_PAIR(4));
        }

        // Render food
        attron(A_BOLD | COLOR_PAIR(3));
        mvaddch(food->y, food->x, food->getCharacter());
        attroff(A_BOLD | COLOR_PAIR(3));

        // Render points
        mvprintw(0, 0, "Points: %d", points);
        refresh();
        onKeyPressed();

        // Halt the render process
        usleep(RENDER_DELTA_TIME);
    }
}

void AppDelegate::onKeyPressed() {
    switch (getch()) {
        case KEY_F(1): onGameOver(); break;
        case KEY_RESIZE:
            onWindowResize(this);
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

void AppDelegate::onGameOver() {
    erase();
    const std::array<const char*, 6> ascii = {
       "                                          __ ",
       " _____                  _____            |  |",
       "|   __|___ _____ ___   |     |_ _ ___ ___|  |",
       "|  |  | .'|     | -_|  |  |  | | | -_|  _|__|",
       "|_____|__,|_|_|_|___|  |_____| \\_/|___|_| |__|",
       "                                             "};

    currentState = HALT;
    while (currentState == HALT) {
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

        if (getch() == KEY_ENTER) {
            currentState = STOP;
        }

        refresh();
        usleep(RENDER_DELTA_TIME);
    }
}

void AppDelegate::onDestroy() {
    // TODO: Fix virtual destructor is not implemented yet.
    delete food;
    delete snake;
}
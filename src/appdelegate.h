#ifndef __APPDELEGATE_H
#define __APPDELEGATE_H

#include <cstdint>

#include "entity/food.h"
#include "entity/snake.h"

/**
 * Class AppDelegate
 *
 * This class would control and handle all of game system.
 */
class AppDelegate {
public:
    /** WINDOW_W is a console Width */
    uint32_t WINDOW_W;
    /** WINDOW_H is a console Height */
    uint32_t WINDOW_H;

    /**
     * Constructor will build and initialize `stdscr` from ncurses,
     * then continue the game flow.
     *
     * Game flow:
     *  1. onSetup()
     *  2. onRender()
     *      2.a onKeyPressed()
     *  3. onDestroy()
     */
    AppDelegate();

private:
    /**
     * GameState is our state indicator value.
     *
     * @type uint16_t
     */
    enum GameState : uint16_t { LOAD, RUN, STOP };

    /** State indicator */
    GameState currentState = LOAD;

    /** Food object */
    Food *food;

    /** Snake object */
    Snake *snake;

    /**
     * Delta time for renderer to render next buffer.
     * This value represented as milisecond (ms).
     *
     * The rendering system scenario would be look like this:
     *  Buffer -> flush -> pause deltaTime -> buffer -> flush -> pause ...
     * Till exit signal is interrupted.
     */
    const uint16_t DELTA_TIME_HORIZONTAL = 200;
    const uint16_t DELTA_TIME_VERTICAL = 225;

    /**
     * Setup all used object before it got rendered to the main screen.
     */
    void onSetup();

    /**
     * Render everything on main screen.
     * Currently we're using `stdscr` as our main window.
     */
    void onRender();

    /**
     * Handle every keyboard input from the user.
     * This function triggered when AppDelegate::onRender() got called.
     */
    void onKeyPressed();

    /**
     * Finally, clean-up all the mess or garbage.
     */
    void onDestroy();
};

#endif    // __APPDELEGATE_H
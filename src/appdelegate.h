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
    /** X Center */
    uint32_t WINDOW_W_CENTER;
    /** Y Center */
    uint32_t WINDOW_H_CENTER;

    /**
     * Constructor will build and initialize `stdscr` from ncurses,
     * then continue the game flow.
     *
     * Game flow:
     *  1. onSetup()
     *  2. onRender()
     *      2.a onKeyPressed()
     *      2.b onGameOver()
     *  3. onDestroy()
     */
    AppDelegate();

private:
    /**
     * GameState is our state indicator value.
     *
     * @type uint16_t
     */
    enum GameState : uint16_t { LOAD, RUN, STOP, HALT };

    /** State indicator */
    GameState currentState = LOAD;

    /** Food object */
    Food *food;

    /** Snake object */
    Snake *snake;

    /** Total points achived by the player */
    uint32_t points;

    /** Banner flag */
    bool isBannerShown;

    /**
     * Delta time for renderer to render next buffer (frame).
     * This value represented as microsecond (usec).
     *
     * The rendering system scenario would be look like this:
     *  Buffer -> flush -> pause deltaTime -> buffer -> flush -> pause ...
     * Till exit signal is interrupted.
     */
    const uint32_t RENDER_DELTA_TIME = 110000;

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
     * Trigerring a game over state and stop the game.
     */
    void onGameOver();

    /**
     * Show game first interface
     */
    void onShowBanner();

    /**
     * Finally, clean-up all the mess or garbage.
     */
    void onDestroy();
};

#endif    // __APPDELEGATE_H
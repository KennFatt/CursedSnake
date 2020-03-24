#ifndef __SNAKE_H
#define __SNAKE_H

#include <cstdint>
#include <vector>

#include "../math/facingdirection.h"
#include "../math/vector2.h"
#include "entity.h"
#include "food.h"

/**
 * Empty class to prevent circular dependencies.
 * @link https://stackoverflow.com/q/625799/6569706
 */
class AppDelegate;

/**
 * Snake class
 */
class Snake : public Entity {
private:
    /** Current snake's direction */
    FacingDirection::WindDirection currentDirection = FacingDirection::NORTH;

    /** Total length of its body */
    uint32_t length;

    /** Store its body (parts) as a dynamic array of Vector2 */
    std::vector<Vector2> parts;

    /** Pointer of application */
    const AppDelegate* application;

public:
    /**
     * Create new snake instance.
     *
     * @param ch Food character
     */
    Snake(const char ch, const AppDelegate* app);

    /**
     * Get class's character.
     *
     * @return const char*
     */
    const char getCharacter() const;

    /**
     * Handle snake's movement.
     */
    void onTick();

    /**
     * Check whether the snake is eating a food.
     *
     * @param food Food object
     *
     * @return bool
     */
    bool onEat(const Food& food);

    std::vector<Vector2>& getParts();

    /**
     * Get current snake's facing direction.
     *
     * @return FacingDirection::WindDirection&
     */
    FacingDirection::WindDirection getDirection() const;

    /**
     * Update snake's facing direction.
     */
    void updateDirection(const FacingDirection::WindDirection& newDirection);
};

#endif    // __SNAKE_H
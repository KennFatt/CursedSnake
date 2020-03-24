#ifndef __SNAKE_H
#define __SNAKE_H

#include <cstdint>
#include <vector>

#include "../appdelegate.h"
#include "../math/vector2.h"
#include "entity.h"
#include "food.h"

/**
 * Snake class
 */
class Snake : public Entity {
private:
    /** Enum of Facing Direction */
    enum FacingDirection : uint16_t { NORTH, EAST, SOUTH, WEST };

    /** Current snake's direction */
    FacingDirection currentDirection = NORTH;

    /** Total length of its body */
    uint32_t length;

    /** Store its body (tail) as a dynamic array of Vector2 */
    std::vector<Vector2> tail;

    /** Pointer to main application */
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
};

#endif    // __SNAKE_H
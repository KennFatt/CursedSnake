#ifndef __SNAKE_H
#define __SNAKE_H

#include <cstdint>
#include <vector>

#include "../math/vector2.h"
#include "entity.h"
#include "food.h"

/**
 * Snake class
 */
class Snake : public Entity {
public:
    /** Enum of Facing Direction */
    enum FacingDirection : uint16_t { NORTH, EAST, SOUTH, WEST };

private:
    /** Current snake's direction */
    FacingDirection currentDirection = NORTH;

    /** Total length of its body */
    uint32_t length;

    /** Store its body (tail) as a dynamic array of Vector2 */
    std::vector<Vector2> tail;

    uint32_t* WINDOW_W;
    uint32_t* WINDOW_H;

public:
    /**
     * Create new snake instance.
     *
     * @param ch Food character
     */
    Snake(const char ch, uint32_t* _window_w, uint32_t* _window_h);

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

    /**
     * Update snake's facing direction.
     */
    void updateDirection(const FacingDirection& newDirection);
};

#endif    // __SNAKE_H
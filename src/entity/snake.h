#ifndef __SNAKE_H
#define __SNAKE_H

#include <cstdint>
#include <vector>

#include "../math/facingdirection.h"
#include "../math/vector2.h"
#include "entity.h"
#include "food.h"

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

    /** Main screen window's width and height */
    const uint32_t* WINDOW_W;
    const uint32_t* WINDOW_H;

public:
    /**
     * Create new snake instance.
     * TODO: Remove param app
     *
     * @param ch Food character
     */
    Snake(const char ch, const uint32_t* _w, const uint32_t* _h);

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
     * Check if its head had collision with its body parts.
     *
     * @param partsIndex Index of body parts.
     *
     * @return bool
     */
    bool hasCollisionWith(const unsigned& partsIndex);

    /**
     * Get snake body parts.
     *
     * @return std::vector<Vector2>&
     */
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

    /**
     * Class destructor.
     */
    ~Snake();
};

#endif    // __SNAKE_H
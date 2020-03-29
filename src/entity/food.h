#ifndef __FOOD_H
#define __FOOD_H

#include "entity.h"

/**
 * Food class
 */
class Food : public Entity {
public:
    /**
     * Create new food instance.
     *
     * @param ch Food character
     */
    Food(const char ch)
        : Entity(ch, -1.0, -1.0) {}

    /**
     * Get class's character.
     *
     * @return const char*
     */
    const char getCharacter() const {
        return character;
    }

    /**
     * TODO: Interactively change its color every tick.
     */
    void onTick() {}

    /**
     * Class destructor.
     */
    ~Food() {}
};

#endif    // __FOOD_H
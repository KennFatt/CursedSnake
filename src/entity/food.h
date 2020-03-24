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
    Food(const char ch);

    /**
     * Get class's character.
     *
     * @return const char*
     */
    const char getCharacter() const;

    /**
     * TODO: Interactively change its color every tick.
     */
    void onTick();
};

#endif    // __FOOD_H
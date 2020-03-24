#ifndef __ENTITY_H
#define __ENTITY_H

#include "../math/vector2.h"

/**
 * Entity class
 */
class Entity : public Vector2 {
protected:
    /** Character that would indicate an entity */
    const char character;

public:
    /** Disable default constructor */
    Entity() = delete;

    /**
     * Create new entity instance with X and Y co-ordinate.
     *
     * @param ch Single character
     * @param _X X value
     * @param _Y Y value
     */
    explicit Entity(const char ch, const double& _X, const double& _Y)
        : Vector2(_X, _Y)
        , character(ch) {}

    /**
     * Get entity character.
     *
     * @return const char*
     */
    virtual const char getCharacter() const = 0;

    /**
     * Tick entity instance for each buffer.
     */
    virtual void onTick() = 0;
};

#endif    // __ENTITY_H
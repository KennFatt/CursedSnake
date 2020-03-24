#include "snake.h"

Snake::Snake(const char ch, uint32_t* _window_w, uint32_t* _window_h)
    : Entity(ch, -1.0, -1.0) {
    length = 0;
    WINDOW_W = _window_w;
    WINDOW_H = _window_h;
}

const char Snake::getCharacter() const {
    return character;
}

void Snake::onTick() {
    /** Update its position */
    switch (currentDirection) {
        case NORTH: y--; break;
        case EAST: x++; break;
        case SOUTH: y++; break;
        case WEST: x--; break;
    }

    /** Border validation */
    if (x > *WINDOW_W) {
        x = 0;
    } else if (x < 0) {
        x = *WINDOW_W - 1;
    }

    if (y > *WINDOW_H) {
        y = 0;
    } else if (y < 0) {
        y = *WINDOW_H - 1;
    }
}

bool Snake::onEat(const Food& food) {
    if (distance(food) <= 0) {
        length++;
        return true;
    }

    return false;
}

void Snake::updateDirection(const FacingDirection& newDirection) {
    if (currentDirection != newDirection) {
        currentDirection = newDirection;
    }
}
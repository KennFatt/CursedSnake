#include "snake.h"

Snake::Snake(const char ch, const AppDelegate* app)
    : Entity(ch, -1.0, -1.0) {
    length = 0;
    application = app;
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
    if (x > application->WINDOW_W) {
        x = 0;
    } else if (x < 0) {
        x = application->WINDOW_W - 1;
    }

    if (y > application->WINDOW_H) {
        y = 0;
    } else if (y < 0) {
        y = application->WINDOW_H - 1;
    }
}

bool Snake::onEat(const Food& food) {
    if (distance(food) <= 0) {
        length++;
        return true;
    }

    return false;
}

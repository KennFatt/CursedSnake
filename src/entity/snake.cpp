#include "snake.h"

#include "../appdelegate.h"

Snake::Snake(const char ch, const AppDelegate* app)
    : Entity(ch, -1.0, -1.0) {
    length = 0;
    application = app;
}

const char Snake::getCharacter() const {
    return character;
}

void Snake::onTick() {
    /** Preparing for its tail */
    if (tail.size() > 0) {
        for (int i = 0; i < tail.size() - 1; i++) {
            tail[i] = tail[i + 1];
        }
    }

    /** Update its position */
    switch (currentDirection) {
        case FacingDirection::NORTH: y--; break;
        case FacingDirection::EAST: x++; break;
        case FacingDirection::SOUTH: y++; break;
        case FacingDirection::WEST: x--; break;
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
        tail.emplace_back(x, y);
        return true;
    }

    return false;
}

std::vector<Vector2>& Snake::getTail() {
    return tail;
}

FacingDirection::WindDirection Snake::getDirection() const {
    return currentDirection;
}

void Snake::updateDirection(
   const FacingDirection::WindDirection& newDirection) {
    if (currentDirection == FacingDirection::NORTH
        && newDirection != FacingDirection::SOUTH) {
        currentDirection = newDirection;
    } else if (currentDirection == FacingDirection::SOUTH
               && newDirection != FacingDirection::NORTH) {
        currentDirection = newDirection;
    } else if (currentDirection == FacingDirection::EAST
               && newDirection != FacingDirection::WEST) {
        currentDirection = newDirection;
    } else if (currentDirection == FacingDirection::WEST
               && newDirection != FacingDirection::EAST) {
        currentDirection = newDirection;
    }
}
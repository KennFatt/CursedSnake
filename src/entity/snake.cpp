#include "snake.h"

#include "../appdelegate.h"

Snake::Snake(const char ch, const AppDelegate* app)
    : Entity(ch, -1.0, -1.0) {
    length = 0;
    application = app;
    parts.push_back(Vector2(app->WINDOW_W_CENTER, app->WINDOW_H_CENTER));
}

const char Snake::getCharacter() const {
    return character;
}

void Snake::onTick() {
    /** Update its position */
    switch (currentDirection) {
        case FacingDirection::NORTH:
            parts.insert(parts.begin(), Vector2(parts[0].x, parts[0].y - 1));
            break;
        case FacingDirection::EAST:
            parts.insert(parts.begin(), Vector2(parts[0].x + 1, parts[0].y));
            break;
        case FacingDirection::SOUTH:
            parts.insert(parts.begin(), Vector2(parts[0].x, parts[0].y + 1));
            break;
        case FacingDirection::WEST:
            parts.insert(parts.begin(), Vector2(parts[0].x - 1, parts[0].y));
            break;
    }

    /** Border validation */
    if (parts[0].x > application->WINDOW_W) {
        parts[0].x = 0;
    } else if (parts[0].x < 0) {
        parts[0].x = application->WINDOW_W - 1;
    }

    if (parts[0].y > application->WINDOW_H) {
        parts[0].y = 0;
    } else if (parts[0].y < 0) {
        parts[0].y = application->WINDOW_H - 1;
    }
}

bool Snake::onEat(const Food& food) {
    if (parts[0].distance(food) <= 0) {
        length++;
        return true;
    }

    return false;
}

bool Snake::hasCollisionWith(const unsigned& partsIndex) {
    return partsIndex != 0 && parts[0].distance(parts[partsIndex]) <= 0;
}

std::vector<Vector2>& Snake::getParts() {
    return parts;
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
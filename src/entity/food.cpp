#include "food.h"

Food::Food(const char ch)
    : Entity(ch, -1.0, -1.0) {}

const char Food::getCharacter() const {
    return character;
}

void Food::onTick() {
    // TODO:
}
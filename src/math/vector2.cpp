#include "vector2.h"

#include <cmath>

Vector2::Vector2()
    : x(0.0)
    , y(0.0) {}

Vector2::Vector2(const double& _X, const double& _Y)
    : x(_X)
    , y(_Y) {}

double Vector2::getX() {
    return x;
}

double Vector2::getY() {
    return y;
}

int Vector2::getFloorX() {
    return static_cast<int>(floorf64(x));
}

int Vector2::getFloorY() {
    return static_cast<int>(floorf64(y));
}

Vector2 Vector2::add(const Vector2& vec) {
    return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::subtract(const Vector2& vec) {
    return add(Vector2(-vec.x, -vec.y));
}

Vector2 Vector2::ceil() {
    return Vector2(ceilf64(x), ceilf64(y));
}

Vector2 Vector2::floor() {
    return Vector2(floorf64(x), floorf64(y));
}

Vector2 Vector2::round() {
    return Vector2(roundf64(x), roundf64(y));
}

Vector2 Vector2::absolute() {
    return Vector2(static_cast<double>(static_cast<int>(x)),
                   static_cast<double>(static_cast<int>(y)));
}

Vector2 Vector2::multiply(const double& n) {
    return Vector2(x * n, y * n);
}

Vector2 Vector2::divide(const double& n) {
    return Vector2(x / n, y / n);
}

double Vector2::distance(const Vector2& vec) {
    return sqrt(powf64(x - vec.x, 2.0) + powf64(y - vec.y, 2.0));
}

double Vector2::length() {
    return sqrt((x * x) + (y * y));
}

double Vector2::dot(const Vector2& vec) {
    return (x * vec.x) + (y * vec.y);
}
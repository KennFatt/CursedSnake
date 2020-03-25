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
    return static_cast<int>(std::floor(x));
}

int Vector2::getFloorY() {
    return static_cast<int>(std::floor(y));
}

Vector2 Vector2::add(const Vector2& vec) {
    return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::subtract(const Vector2& vec) {
    return add(Vector2(-vec.x, -vec.y));
}

Vector2 Vector2::ceil() {
    return Vector2(std::ceil(x), std::ceil(y));
}

Vector2 Vector2::floor() {
    return Vector2(std::floor(x), std::floor(y));
}

Vector2 Vector2::round() {
    return Vector2(std::round(x), std::round(y));
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
    return std::sqrt(std::pow(x - vec.x, 2.0) + std::pow(y - vec.y, 2.0));
}

double Vector2::length() {
    return std::sqrt((x * x) + (y * y));
}

double Vector2::dot(const Vector2& vec) {
    return (x * vec.x) + (y * vec.y);
}
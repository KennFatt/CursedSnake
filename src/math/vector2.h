#ifndef __VECTOR2_H
#define __VECTOR2_H

class Vector2 {
public:
    double x, y;

    explicit Vector2();
    explicit Vector2(const double& _X, const double& _Y);

    double getX();
    double getY();

    int getFloorX();
    int getFloorY();

    Vector2 add(const Vector2& vec);
    Vector2 subtract(const Vector2& vec);

    Vector2 ceil();
    Vector2 floor();
    Vector2 round();
    Vector2 absolute();
    Vector2 multiply(const double& n);
    Vector2 divide(const double& n);

    double distance(const Vector2& vec);

    double length();
    double dot(const Vector2& vec);
};

#endif    // __VECTOR2_H
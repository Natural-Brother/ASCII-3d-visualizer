#pragma once
#include <cmath>
#include <iostream>
class Vector2{
    public:
    double x;
    double y;
    Vector2();    
    Vector2(double x, double y);

    double magnitude();
    Vector2 unit();
    Vector2 rotate(double degrees);
    Vector2 round();


    Vector2 operator+(Vector2 vec2);
    Vector2 operator-(Vector2 vec2);
    Vector2 operator*(double factor);
    Vector2 operator*(Vector2 factor);
    Vector2 operator/(int quotient);
    static double dotproduct(Vector2 a, Vector2 b);
};

std::ostream& operator<<(std::ostream &os, Vector2 const &m);
#pragma once
#include <cmath>
#include <iostream>
class Vector3{
    public:
    double x;
    double y;
    double z;

    Vector3();
    Vector3(double x, double y, double z);
    Vector3(int i);
    Vector3(double d);

    double magnitude();
    Vector3 unit();
    Vector3 rotatedOf(double angleX,double angleY,double angleZ);
    Vector3 rotation(Vector3 u, double angle);
    Vector3 operator+(Vector3 vec2);
    Vector3 operator-(Vector3 vec2);
    Vector3 operator*(double factor);
    Vector3 operator*(int factor);
    Vector3 operator/(double quotient);
    bool operator==(Vector3 vec2);
    static Vector3 crossproduct(Vector3 a, Vector3 b);
    static double dotproduct(Vector3 a, Vector3 b);
};

std::ostream& operator<<(std::ostream &os, Vector3 const &m);
#pragma once
#include "Vector3.h"
#include <iostream>
class triangle{
    public:
    Vector3 normal = Vector3(0.0,0.0,0.0);
    Vector3 ** vertex = new Vector3 * [3];
    Vector3 color = Vector3(0.0,1.0,0.0);
    Vector3 getVertex(int index);
    Vector3 getNormal();
    Vector3 getCenter();
    void setVertex(int index, Vector3* newVertex);
    
};
std::ostream& operator<<(std::ostream &os, triangle const &m);
#pragma once
#include "Vector2.h"
class GObject{
    public:
    int NPoints;
    Vector2* shape;
    Vector2 position;
    Vector2 velocity;
    int size=1;
    void defineShape(int ** shp);
    void UpdatePos();

    
};
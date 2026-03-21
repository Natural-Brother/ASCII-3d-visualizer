#pragma once
#include "Model3D.h"
#include <iostream>
class GObject3D{
    public:
    Model3D Model;
    Vector3 position;
    Vector3 velocity;
    int size=1;
    void UpdatePos();

    
};
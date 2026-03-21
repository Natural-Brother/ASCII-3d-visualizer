#pragma once
#include "Model3D.h"
#include <iostream>

namespace ModelsUtils{
    enum ModelType{
        CUBE
    };

    Model3D returnModels(ModelType Model);
    Model3D returnCube(int size);

    Vector3 * returnVertex(int vertexC, Vector3 * argVertex);

    
}
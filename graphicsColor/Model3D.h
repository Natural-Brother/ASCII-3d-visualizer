#pragma once
#include "triangle.h"
#include <iostream>
class Model3D{
    public:

    int NVertex;
    int NFaces;
    int * adressOfVertex;

    Vector3 * Vertex;
    triangle * faces;

    //Model3D(Model3D& other);
    Model3D();
    //~Model3D();

    void defineVertex(Vector3 * argVertex);
    void defineFaces(triangle * argFaces);

    void setFaces(int index,triangle argFaces);
    void setFacesMaterial(int index,Vector3 color);
    Vector3 getVertex(int index) const ;
    triangle getFace(int index);
    void setVertex(int index,Vector3 argVertex);
    void setFaces(int facesC, int * argIndexFaces);
    void setFaces(int facesC, int * argIndexFaces, Vector3 argColor);

    Model3D rotatedModel(Vector3 axis, double angle);
    Model3D offset(Vector3 offset);

    Model3D& operator=(const Model3D& other);
    
    /*Model3D(int numberofVertex,int numberofFaces,){
        Vertex;
        faces;
    }
    */
};
std::ostream& operator<<(std::ostream &os, Model3D const &m);
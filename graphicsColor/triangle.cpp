#include "triangle.h"


    Vector3 triangle::getVertex(int index){
        return *(vertex[index]);
    }
    Vector3 triangle::getNormal(){
        return normal == Vector3(0.0,0.0,0.0)?Vector3::crossproduct((*this).getVertex(2) - (*this).getVertex(0),(*this).getVertex(1) - (*this).getVertex(2)):normal;
    }
    Vector3 triangle::getCenter(){
        return ((*this).getVertex(0)+(*this).getVertex(1)+(*this).getVertex(2))/3.0;
    }
    void triangle::setVertex(int index, Vector3* newVertex){
        vertex[index] = newVertex;
    }

    std::ostream& operator<<(std::ostream &os, triangle const &m){
        return os<<"face"<<*(m.vertex[0]) << "||" << *(m.vertex[1]) << "||" << *(m.vertex[2]);
    }
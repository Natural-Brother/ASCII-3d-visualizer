#include "Vector2.h"
#include "GObject2D.h"
#include <iostream>
using namespace std;
    int NPoints;
    int size;
    Vector2 * shape;
    Vector2 position;
    void GObject::defineShape(int ** shp){
        shape =  new Vector2[NPoints];
        for(int i = 0; i< NPoints; i++){
            cout << "size: "<< NPoints<< " index: "<< i<< " x: "<< shp[i][0]<<" y: "<< shp[i][1]<< endl;
            shape[i].x = (double)shp[i][0];
            shape[i].y = (double)shp[i][1];;
        }
    
    }
    void GObject::UpdatePos(){
        position.x += velocity.x;
        position.y += velocity.y;
    }
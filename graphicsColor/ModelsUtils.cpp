#include "ModelsUtils.h"

    Model3D ModelsUtils::returnCube(int size){

      Model3D newCube;
      
      newCube.Vertex = new Vector3[8];
      
      for(int z=0;z<2;z++){
        for(int y=0;y<2;y++){
          for(int x=0;x<2;x++){
            newCube.Vertex[z*4+y*2+x].x = -size+2*size*x;
            newCube.Vertex[z*4+y*2+x].y = -size+2*size*y;
            newCube.Vertex[z*4+y*2+x].z = -size+2*size*z;
         }
       }
     }
     
     
    int newCubeFaces[36] = {
      1,2,3,
      2,4,3,
      1,5,6,
      1,6,2,
      7,6,5,
      7,8,6,
      8,7,3,
      3,4,8,
      7,5,1,
      1,3,7,
      8,2,6,
      4,2,8
    };
    
    newCube.NFaces = 12;
    newCube.NVertex = 8;
    std::cout << "newCubes " << newCubeFaces[0] << std::endl;
    newCube.setFaces(12,newCubeFaces);

    return newCube;
  }
    
    Model3D returnModels(ModelsUtils::ModelType Model){
        Model3D result;
        switch(Model){
            case ModelsUtils::CUBE :

              Model3D Cube = ModelsUtils::returnCube(1);
              result = Cube;

            break;
        }
      return result;
    }

    Vector3 * ModelsUtils::returnVertex(int vertexC, Vector3 * argVertex){
        Vector3 * c = new Vector3[vertexC];
        for(int i = 0; i< vertexC; i++){
            c[i] = argVertex[i];
        }
        return c;
    }


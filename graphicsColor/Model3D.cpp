#include "Model3D.h"
using namespace std;

    /*Model3D :: ~Model3D(){
        delete adressOfVertex;
        delete Vertex;
        delete faces;
    }*/

    void Model3D::defineVertex(Vector3 * argVertex){
        Vertex = argVertex;
    }

    void Model3D::defineFaces(triangle * argFaces){
            faces = argFaces;
    }

    Vector3 Model3D::getVertex(int index) const {
        return Vertex[index];
    }

    triangle Model3D::getFace(int index){
        return faces[index];
    }

    void Model3D::setVertex(int index,Vector3 argVertex){
        Vertex[index] = argVertex;
    }

    void Model3D::setFaces(int index,triangle argFaces){
        faces[index] = argFaces;
    }

    void Model3D::setFacesMaterial(int index,Vector3 color){
        faces[index].color = color;
    }

    void Model3D::setFaces(int facesC,int * argIndexFaces){
        (*this).adressOfVertex = new int[facesC*3];
        for(int i = 0; i< facesC*3;i++){
            (*this).adressOfVertex[i] = argIndexFaces[i];
        }

        (*this).faces = new triangle[facesC];
        for(int i = 0; i< facesC; i++){
            for(int j = 0; j< 3; j++){
            (*this).faces[i].setVertex(j ,&((*this).Vertex[argIndexFaces[i*3+j]-1]));
            }
        }
    }

    void Model3D::setFaces(int facesC,int * argIndexFaces, Vector3 argColor){
        (*this).adressOfVertex = new int[facesC*3];
        for(int i = 0; i< facesC*3;i++){
            (*this).adressOfVertex[i] = argIndexFaces[i];
        }

        (*this).faces = new triangle[facesC];
        for(int i = 0; i< facesC; i++){
            for(int j = 0; j< 3; j++){
            (*this).faces[i].setVertex(j ,&((*this).Vertex[argIndexFaces[i*3+j]-1]));
            (*this).faces[i].color = argColor;
            }
        }
    }

    Model3D Model3D::rotatedModel(Vector3 axis, double angle){
        //std::cout << "ROTATING " << (*this).adressOfVertex[0] << std::endl;
        Model3D rModel;
        rModel = *this;
        
        for(int i = 0 ; i < rModel.NVertex; i++){
            rModel.Vertex[i] = rModel.Vertex[i].rotation(axis,angle);
        }
        //cout << "is okay? "<< rModel.getVertex(0)<<  endl;
        return rModel;
    }

    Model3D Model3D::offset(Vector3 offset){
        Model3D oModel;
        oModel = *this;
        for(int i = 0 ; i < oModel.NVertex; i++){
            oModel.Vertex[i] = oModel.Vertex[i] + offset;
        }
        return oModel;
    }

    /*Model3D::Model3D(Model3D& other){
     NVertex = other.NVertex;
     NFaces = other.NFaces;
     Vertex = new Vector3[other.NVertex];
    for(int i =0; i < other.NVertex; i++){
        Vertex[i] = other.Vertex[i];
    }
    Model3D::setFaces(other.NFaces,other.adressOfVertex);
    }*/

    Model3D::Model3D(){
     NVertex = 0;
     NFaces = 0;
     Vertex = new Vector3;
    }

    Model3D& Model3D::operator=(const Model3D& other){
     (*this).NVertex = other.NVertex;
     (*this).NFaces = other.NFaces;
     (*this).Vertex = new Vector3[(*this).NVertex];
    for(int i =0; i < (*this).NVertex; i++){
        (*this).Vertex[i] = other.getVertex(i);
    }
    Model3D::setFaces((*this).NFaces,other.adressOfVertex);

    for(int i =0; i < (*this).NFaces; i++){
        (*this).faces[i].color = other.faces[i].color;
    }
    return *this;
    }
    

    std::ostream& operator<<(std::ostream &os, Model3D const &m){
        os<<"Model[\n";
        for(int i = 0; i< m.NFaces; i++){
            os<<"\t"<<m.faces[i]<<"\n";
        }
        return os << "]";
    }
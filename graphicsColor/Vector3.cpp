
#include "Vector3.h"
using namespace std;

    Vector3::Vector3(){
        Vector3::x = 0.0;
        Vector3::y = 0.0;
        Vector3::z = 0.0;
    }

    Vector3::Vector3(double x,double y,double z){
        Vector3::x = x;
        Vector3::y = y;
        Vector3::z = z;
    }

    Vector3::Vector3(int i){
        Vector3::x = i;
        Vector3::y = i;
        Vector3::z = i;
    }

    Vector3::Vector3(double d){
        Vector3::x = d;
        Vector3::y = d;
        Vector3::z = d;
    }

    Vector3 Vector3::unit(){
        double m = Vector3::magnitude() == 0.0 ? 0.001 : Vector3::magnitude();
        return Vector3{Vector3::x/m,Vector3::y/m,Vector3::z/m};
    }

    Vector3 Vector3::rotatedOf(double angleX,double angleY,double angleZ){
        //degrees to radians
        angleX *= 0.01745329251;
        angleY *= 0.01745329251;
        angleZ *= 0.01745329251;    
        double rx = x * cos(angleX + angleZ) + z*-sin(angleX) + y*-sin(angleZ) ;
        double rz = x * sin(angleX) + z*cos(angleX+angleY) + y*-sin(angleY);
        double ry = z * sin(angleY) + y*cos(angleY+angleZ) + x * sin(angleZ);

        /*double rx = x * cos(angleY) + x * cos(angleZ) + y * -sin(angleZ) + z * sin(angleY);
        double ry = x * sin(angleZ) + y * cos(angleZ) + y * cos(angleX) + z * -sin(angleX);
        double rz = x * -sin(angleY) + z * cos(angleY) + z * cos(angleX) + y * sin(angleX);*/
        return Vector3{rx,ry,rz};
    }

    Vector3 Vector3::rotation(Vector3 u, double angle){
        Vector3 p = (*this);
        return p + (Vector3::crossproduct(u,p)) * 2.0*cos(angle/2.0)*sin(angle/2.0) 
        +(Vector3::crossproduct(u,Vector3::crossproduct(u,p))) * 2.0*(sin(angle/2.0)*sin(angle/2.0));
    }

    double Vector3::magnitude(){
        return sqrt(Vector3::z*Vector3::z+Vector3::y*Vector3::y+Vector3::x*Vector3::x);
    }

    Vector3 Vector3::operator+(Vector3 vec2){
        return Vector3(Vector3::x+vec2.x,Vector3::y+vec2.y,Vector3::z+vec2.z);
    }
    Vector3 Vector3::operator-(Vector3 vec2){
        return Vector3(Vector3::x-vec2.x,Vector3::y-vec2.y,Vector3::z-vec2.z);
    }
    Vector3 Vector3::operator*(double factor){
        return Vector3(Vector3::x*factor,Vector3::y*factor,Vector3::z*factor);
    }

    Vector3 Vector3::operator*(int factor){
        return Vector3(Vector3::x*(double)factor,Vector3::y*(double)factor,Vector3::z*(double)factor);
    }
    Vector3 Vector3::operator/(double quotient){
        return Vector3(Vector3::x/quotient,Vector3::y/quotient,Vector3::z/quotient);
    }
    bool Vector3::operator==(Vector3 vec2){
        return Vector3::x==vec2.x and Vector3::y==vec2.y and Vector3::z==vec2.z;
    }

    Vector3 Vector3::crossproduct(Vector3 a, Vector3 b){
        return Vector3(a.y * b.z - a.z * b.y,a.z * b.x - a.x * b.z,a.x * b.y - b.x * a.y);
    }

    double Vector3::dotproduct(Vector3 a, Vector3 b){
        return (a.x*b.x + a.y * b.y + a.z * b.z) / (a.magnitude()*b.magnitude());
    }
    std::ostream& operator<<(std::ostream &os, Vector3 const &m) { 
        
    return os << "["<<m.x<<","<<m.y<<","<<m.z<<"]";
}
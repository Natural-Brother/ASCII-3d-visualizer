#include "Vector2.h"
using namespace std;

    Vector2::Vector2(){
        Vector2::x = 0.0;
        Vector2::y = 0.0;
    }

    Vector2::Vector2(double x,double y){
        Vector2::x = x;
        Vector2::y = y;
    }



    Vector2 Vector2::rotate(double degrees){
        double rx =  x*cos(degrees*0.01745329251) + y*-sin(degrees*0.01745329251);
        double ry =  x*sin(degrees*0.01745329251) + y*cos(degrees*0.01745329251);

        return Vector2{rx,ry};
    }

    Vector2 Vector2::round(){
        return Vector2(std::round(Vector2::x),std::round(Vector2::y));
    }

    double Vector2::dotproduct(Vector2 a, Vector2 b){
        return (a.x*b.x + a.y * b.y) / (a.magnitude()*b.magnitude());
    }

    double Vector2::magnitude(){
        return sqrt(Vector2::y*Vector2::y+Vector2::x*Vector2::x);
    }
    Vector2 Vector2::unit(){
     return Vector2{Vector2::x/Vector2::magnitude(),Vector2::y/Vector2::magnitude()};
    }

    Vector2 Vector2::operator+(Vector2 vec2){
        return  Vector2{Vector2::x+vec2.x,Vector2::y+vec2.y};
    }

    Vector2 Vector2::operator-(Vector2 vec2){
        return Vector2{Vector2::x-vec2.x,Vector2::y-vec2.y};
    }
    Vector2 Vector2::operator*(double factor){
        return Vector2{Vector2::x*factor,Vector2::y*factor};
    }
    Vector2 Vector2::operator*(Vector2 factor){
        return Vector2{Vector2::x*factor.x,Vector2::y*factor.y};
    }

    Vector2 Vector2::operator/(int quotient){
        return Vector2{Vector2::x/quotient,Vector2::y/quotient};
    }

    std::ostream& operator<<(std::ostream &os, Vector2 const &m) { 
        
    return os << "["<<m.x<<","<<m.y<<"]";
}
#include <format>
#include <iostream>
#include "canvas.h"
#include <cmath>
#include <string>


using namespace std;

  double canvas::myMath::gaussian(double x,double a,double b){
    return ((1/(a*sqrt(2*M_PI)))*pow(M_E,-0.5*pow(((x-b)/a),2)))/10;
  }

  double canvas::myMath::normalizedDistance(int a,int b){
    return sqrt(abs(pow(a,2))+abs(pow(b,2)));
  }

  double canvas::myMath::max(double a, double b)
{
    return (a < b) ? b : a;
}

double canvas::myMath::getTriangleArea(triangle v)
{
    Vector3 v1 = v.getVertex(0);
    Vector3 v2 = v.getVertex(1);
    Vector3 v3 = v.getVertex(2);
    return abs(v1.x*(v2.y-v3.y) + v2.x*(v3.y-v1.y) + v3.x*(v1.y-v2.y))/2.0;
}

double canvas::myMath::getTriangleArea(Vector2 * v)
{
  Vector2 v1 = v[0];
  Vector2 v2 = v[1];
  Vector2 v3 = v[2];
    return abs(v1.x*(v2.y-v3.y) + v2.x*(v3.y-v1.y) + v3.x*(v1.y-v2.y))/2.0;
}

double canvas::myMath::getTriangleArea(Vector2 v1,Vector2 v2,Vector2 v3)
{
    return abs(v1.x*(v2.y-v3.y) + v2.x*(v3.y-v1.y) + v3.x*(v1.y-v2.y))/2.0;
}

Vector2 canvas::myMath::dotesque(int argc,Vector2 * vs,Vector2 v){
  int h = 0;
  double vh = Vector2::dotproduct(v,vs[0]) * (v.magnitude() * vs[0].magnitude());
  double vi;
  for(int i = 0; i<argc; i++){
    vi = Vector2::dotproduct(v,vs[i]) * (v.magnitude() * vs[i].magnitude());
    if(vi > vh){
      h = i;
      vh = vi;
    }
  }
  return vs[h];
}

Vector2 canvas::myMath::perspective(Vector3 v){
   return Vector2(v.x/(v.z == 0.0 ? 0.001 : v.z),v.y/(v.z == 0.0 ? 0.001 : v.z))*20; 
   }

Vector2 canvas::myMath::vectorRatio(Vector2 v){return Vector2(v.x,v.y/2.0);}

double canvas::myMath::colorMean(Vector3 c){return (c.x+c.y+c.z)/3.0;}
  int width;
  int midwidth;
  int height;
  int midheight;



  string alph = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
  int resolution= alph.length()-1;
  Vector3 ** map;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD resetpos = {0, 0};


  void canvas::Update(){
  string sheet = "";
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int m = (int)Draw3D.colorMean(map[y][x]);
      sheet+=formatColor(map[y][x])+alph.at(clamps(m,0,alph.length()-1));
    }
  sheet+='\n';
  }

SetConsoleCursorPosition(hConsole, resetpos);
std::cout << sheet;
}

void canvas::clearAll(){
  system("cls");
}

void canvas::newMap(){

  for(int y = 0; y<height; y++){
      for(int x = 0; x<width; x++){
    map[y][x] = Vector3((int)((y*width+x)/resolution));
  }
  }
}

double canvas::perlinNoise(double x,int seed){
  srand(floor(x)*seed);
  double base = ((double) rand() / (RAND_MAX));
  double ceal = ((double) rand() / (RAND_MAX));
  double mx = fmod(x,1.0);
return (base+(3.0*(mx*mx)-2.0*(mx*mx*mx))*(ceal-base) )*2.0-1.0;
}

void canvas::shuffleMap(int intensity){
map = new Vector3 * [height];
for (int i = 0; i< height; i++){
  map[i] = new Vector3[width];
}
  for(int y = 0; y<height; y++){
      for(int x = 0; x<width; x++){
    map[y][x] = Vector3(rand() % intensity,rand() % intensity,rand() % intensity);
  }
  }
}

int canvas::ansiColor(double c){
  if(c<3.8){
    return 0;
  }else{
    return clamps((int)(c/1.6),0,5);
  }
}

string canvas::formatColor(Vector3 c){
  return ((string)"\033[38;5;"+to_string(16 + ansiColor(c.x)*36 + ansiColor(c.y)*6 + ansiColor(c.z))+(string)"m");
}

int canvas::clamps(int n,int min,int max){
  return n > max?max:(n<min?min:n);
}

int canvas::scaledColor(int color,double scale){
  return (int)round((double)color * (canvas::alph.length()/scale));
}

void canvas::fillMap(Vector3 color){
  for(int y = 0; y<height; y++){
      for(int x = 0; x<width; x++){
    map[y][x] = color;
  }
  }
}

void canvas::dot(int xPos, int yPos,int intensity){
  intensity = clamps(intensity,0,91);
for(int y= 0; y< intensity*2;y++){
  for(int x= 0; x< intensity*2;x++){
    map[clamps(yPos-intensity + y,0,height-1)][clamps(xPos +x-intensity,0,width-1)] = Vector3(1.0,1.0,1.0)*(intensity-clamps(round(dist.normalizedDistance((yPos-intensity+y*2)- yPos,(xPos-intensity+x)- xPos)),0,intensity));
  }
}

}

void canvas::rect(int xPos, int yPos, int widthSize, int heightSize,int intensity){
  for(int y= 0; y< heightSize;y++){
  for(int x= 0; x< widthSize*2;x++){
    map[clamps(yPos + y,0,height-1)][clamps(xPos + x,0,width-1)] = Vector3(clamps(intensity,0,resolution));
  }
}

}

void canvas::drawLine(int x1,int y1, int x2, int y2, int intensity){
  float distancy = abs(dist.max((x2-x1),(y2-y1)))*10;
  for(float i = 0; i < distancy; i++){
    map[y1 + (int)((float)(y2-y1)/distancy * i)][x1 + (int)((float)(x2-x1)/distancy * i)] = Vector3(intensity);
  }
}

void canvas::drawLine(Vector2 a, Vector2 b, int intensity){
  double distancy = 20;
  int penX;
  int penY;
  for(double i = 0.0; i < 1.0; i+=1.0/distancy){
    penY = (int)(a.y + ((b.y-a.y)* i));
    penX = (int)(a.x+ ((b.x-a.x) * i));
    
    if(!(penX>=width || penY>=height ||penX<0||penY<0)){
      map[penY][penX] = Vector3(intensity);
    } 
  }
}

void canvas::drawLine(Vector2 a, Vector2 b, int intensity,int intensityend){
  float distance = 20;
  
  int penX;
  int penY;
  for(float i = 0; i < distance; i++){
    penY = (int)clamps(a.y,0,height) + (int)((b.y-a.y)/distance * i);
    penX = (int)clamps(a.x,0,width) + (int)((b.x-a.x)/distance * i);
    
    if(!(penX>=width || penY>=height ||penX<0||penY<0 )){
      map[penY][penX] = Vector3(clamps((int)(intensity - (intensityend / distance * i)),1,30));
    } 
  }
}

void canvas::drawVertice(Vector3 a, Vector3 b,int intensity){
  //perspective vertex: 3d to 2d
  Vector2 a2 = Vector2(midwidth,midheight)+Draw3D.vectorRatio(Draw3D.perspective(a)).round();
  Vector2 b2 = Vector2(midwidth,midheight)+Draw3D.vectorRatio(Draw3D.perspective(b)).round();
  drawLine(a2,b2,1);
}

void canvas::rasterizeTriangle(Vector2 *  v,Vector3 * colors){
  
  int hl = (int)round((myMath::dotesque(3,v,Vector2(0,-1))).y);
  int hu = (int)round((myMath::dotesque(3,v,Vector2(0,1))).y);
  int wl = (int)round((myMath::dotesque(3,v,Vector2(-1,0))).x);
  int wu = (int)round((myMath::dotesque(3,v,Vector2(1,0))).x);

  fragmentBox([&](int x , int y, Vector3 i){
    Vector2 vo(x,y);
    Vector2 v1 = v[0];
    Vector2 v2 = v[1];
    Vector2 v3 = v[2];
    double vertexarea1 = canvas::myMath::getTriangleArea(vo,v1,v2);
    double vertexarea2 = canvas::myMath::getTriangleArea(vo,v2,v3);
    double vertexarea3 = canvas::myMath::getTriangleArea(vo,v3,v1);
    double area = canvas::myMath::getTriangleArea(v1,v2,v3);


    if( (vertexarea1+vertexarea2+vertexarea3) - area> 0.0){
      return i;
    }else{
      Vector3 tcolor = (colors[2]*(vertexarea1/area) + colors[0]*(vertexarea2/area) + colors[1]*(vertexarea3/area));
      return tcolor;
    }

  },wl,hl,wu,hu);

}

void canvas::drawShape(GObject bj,int intensity){
for(int i = 0; i < bj.NPoints; i++){
  canvas::drawLine(bj.position.x + bj.shape[i].x ,bj.position.y + bj.shape[i].y, bj.position.x + bj.shape[(i+1)%(bj.NPoints)].x, bj.position.y + bj.shape[(i+1)%(bj.NPoints)].y, intensity);
}
}


  void canvas::drawTriangle(triangle face,Vector3 pos){
    for(int i =0; i<3 ; i++){
      Vector3 c = face.getVertex(i)+ pos;
      Vector3 cNext =  (face.getVertex((i+1)%3)+ pos);
      canvas::drawVertice(c,cNext,91);
    }
  }


  void canvas::drawModel(Model3D Model,Vector3 pos){
    for(int i = 0; i<Model.NFaces; i++){
      drawTriangle(Model.getFace(i),pos);
    }
  }

  void canvas::vertexShader(vector<triangle> faceBuffer){
    Vector2 * v = new Vector2[3];
    //color
    Vector3 * c = new Vector3[3];

    std::sort(faceBuffer.begin(), faceBuffer.end(), [&](triangle a,triangle b){return a.getCenter().z > b.getCenter().z;});
    int bufferc = faceBuffer.size();
    for(int i = 0; i<bufferc; i++){
      
      if(Vector3::dotproduct(Vector3(0,0,1),faceBuffer.at(i).getNormal()) >= 0.0){
      Vector3 vertex1 = faceBuffer.at(i).getVertex(0);
      Vector3 vertex2 = faceBuffer.at(i).getVertex(1);
      Vector3 vertex3 = faceBuffer.at(i).getVertex(2);

      Vector3 light = Vector3(0.5,1,1);
      float illumination = (1+Vector3::dotproduct(light,faceBuffer.at(i).getNormal()))/2.0;
      c[0] = faceBuffer.at(i).color*illumination*20.0;
      c[1] = faceBuffer.at(i).color*illumination*20.0;
      c[2] = faceBuffer.at(i).color*illumination*20.0;

      v[0] = (Draw3D.vectorRatio(Draw3D.perspective(vertex1)) + Vector2(midwidth,midheight)).round();
      v[1] = (Draw3D.vectorRatio(Draw3D.perspective(vertex2)) + Vector2(midwidth,midheight)).round();
      v[2] = (Draw3D.vectorRatio(Draw3D.perspective(vertex3)) + Vector2(midwidth,midheight)).round();
      rasterizeTriangle(v,c);
    }
    }
  }

  void canvas::addModel(vector<triangle> &faceBuffer, Model3D Model){
    for(int i = 0; i<Model.NFaces; i++){
      faceBuffer.push_back(Model.getFace(i));
      faceBuffer[faceBuffer.size()-1].color = Model.getFace(i).color;
    }
  }

  void canvas::rasterizeModel(Model3D Model,Vector3 pos){
    //2d vertex
    Vector2 * v = new Vector2[3];
    //color
    Vector3 * c = new Vector3[3];

    
    for(int i = 0; i<Model.NFaces; i++){
      if(Vector3::dotproduct(Vector3(0,0,1),Model.getFace(i).getNormal()) >= 0.0){
      Vector3 vertex1 = Model.getFace(i).getVertex(0)+pos;
      Vector3 vertex2 = Model.getFace(i).getVertex(1)+pos;
      Vector3 vertex3 = Model.getFace(i).getVertex(2)+pos;

      c[0] = Model.getFace(i).color*scaledColor(255.0-vertex1.magnitude() * 20.0,255);
      c[1] = Model.getFace(i).color*scaledColor(255.0-vertex2.magnitude() * 20.0,255);
      c[2] = Model.getFace(i).color*scaledColor(255.0-vertex3.magnitude() * 20.0,255);

      v[0] = (Draw3D.vectorRatio(Draw3D.perspective(vertex1)) + Vector2(midwidth,midheight)).round();
      v[1] = (Draw3D.vectorRatio(Draw3D.perspective(vertex2)) + Vector2(midwidth,midheight)).round();
      v[2] = (Draw3D.vectorRatio(Draw3D.perspective(vertex3)) + Vector2(midwidth,midheight)).round();
      rasterizeTriangle(v,c);
    }
    }
  }



  void canvas::initiate(){


    std::cout << "width: \n";
   std::cin >> width;
    std::cout << "height: \n";
    std::cin >> height;

  midwidth = width/2;
  midheight = height/2;

  map = new Vector3* [height];
        for (int i = 0; i< height; i++){
            map[i] = new Vector3[width];
        }
    fillMap(0);
  }

  canvas::canvas(){
    
    canvas::height = 100, canvas::width = 100;
    canvas::midwidth = canvas::width/2, canvas::midheight = canvas::height/2;



    canvas::map = new Vector3* [canvas::height];
        for (int i = 0; i< canvas::height; i++){
            canvas::map[i] = new Vector3[canvas::width];
        }
    canvas::fillMap(0);
    
  } 


    canvas::canvas(int argheight, int argwidth){
    
    canvas::height = argheight, canvas::width = argwidth;
    canvas::midwidth = canvas::width/2, canvas::midheight = canvas::height/2;



    canvas::map = new Vector3* [canvas::height];
        for (int i = 0; i< canvas::height; i++){
            canvas::map[i] = new Vector3[canvas::width];
        }
    canvas::fillMap(0);
  } 

    canvas::canvas(int argheight, int argwidth, int intensity){
    
    canvas::height = argheight, canvas::width = argwidth;
    canvas::midwidth = canvas::width/2, canvas::midheight = canvas::height/2;



    canvas::map = new Vector3* [canvas::height];
        for (int i = 0; i< canvas::height; i++){
            canvas::map[i] = new Vector3[canvas::width];
        }
    canvas::fillMap(intensity);
  } 
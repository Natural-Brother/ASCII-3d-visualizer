#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <vector>
#include <bits/stdc++.h>

#include "canvas.h"
#include "GObject2D.h"
#include "Model3D.h"

using namespace std;

 class canvas{
        
        public:
        
        int width;
        int midwidth;
        int height;
        int midheight;

        
        std::string alph = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
        Vector3 ** map;

struct myMath{

  double gaussian(double x,double a,double b);
  double normalizedDistance(int a,int b);
  static double getTriangleArea(triangle v);
  static double getTriangleArea(Vector2 * v);
  static double getTriangleArea(Vector2 v1,Vector2 v2,Vector2 v3);
  static Vector2 dotesque(int argc,Vector2 * vs,Vector2 v);
  double max(double a, double b);

  static Vector2 perspective(Vector3 vertex);
  static Vector2 vectorRatio(Vector2 v);
  static double colorMean(Vector3 c);
}dist, Draw3D;
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = {1, 1};
        
canvas();
canvas(int argheight, int argwidth);
canvas(int argheight, int argwidth, int intensity);
void initiate();
void Update();
void clearAll();

void newMap();
void shuffleMap(int intensity);
void fillMap(Vector3 intensity);

int ansiColor(double c);
string formatColor(Vector3 c);
int clamps(int n,int min,int max);
int scaledColor(int color,double scale);
void pause(int dur);
double perlinNoise(double x,int seed);

template <typename Func>
void fragment(Func lambda){
  for(int y = 0; y<height; y++){
      for(int x = 0; x<width; x++){
    map[y][x] = lambda(x,y,map[y][x]);
    }
  }
}

template <typename Func>
void fragmentBox(Func lambda,int x0,int y0,int x1,int y1){
  for(int y = y0 > 0? y0 : 0; y<y1 and y < height; y++){
      for(int x = x0 > 0? x0 : 0; x<x1 and x<width; x++){
    map[y][x] = lambda(x,y,map[y][x]);
    }
  }
}
void dot(int xPos, int yPos,int intensity);
void rect(int xPos, int yPos, int widthSize, int heightSize,int intensity);
void drawLine(int x1,int y1, int x2, int y2, int intensity);
void drawLine(Vector2 a, Vector2 b, int intensity);
void drawLine(Vector2 a, Vector2 b, int intensity,int intensityend);
void drawVertice(Vector3 a, Vector3 b, int intensity);
void rasterizeTriangle(Vector2 * v,Vector3 * colors);
void drawShape(GObject bj,int intensity);

void vertexShader(std::vector<triangle> faceBuffer);
void addModel(std::vector<triangle> &faceBuffer,Model3D Model);
void drawTriangle(triangle face, Vector3 pos);
void drawModel(Model3D Model,Vector3 pos);
void rasterizeModel(Model3D Model,Vector3 pos);

};
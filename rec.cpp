#include "rec.h"
#include <iostream>
#include<GL/glut.h>
#include <math.h>
#define PI 3.14

Retangulo::Retangulo(float x1, float x2, float y1, float y2)
{
  this->x1 = x1;
  this->x2 = x2;
  this->y1 = y1;
  this->y2 = y2;
};

float Retangulo::getx1(){//Ajusta a coordenada X do Centro
    return this->x1;
}

void Retangulo::setx1(float r){//Ajusta a coordenada X do Centro
    this->x1 = r;
}

float Retangulo::getx2(){//Ajusta a coordenada X do Centro
    return this->x2;
}

void Retangulo::setx2(float r){//Ajusta a coordenada X do Centro
    this->x2 = r;
}

float Retangulo::gety1(){//Ajusta a coordenada X do Centro
    return this->y1;
}

void Retangulo::sety1(float r){//Ajusta a coordenada X do Centro
    this->y1 = r;
}

float Retangulo::gety2(){//Ajusta a coordenada X do Centro
    return this->y2;
}

void Retangulo::sety2(float r){//Ajusta a coordenada X do Centro
    this->y2 = r;
}




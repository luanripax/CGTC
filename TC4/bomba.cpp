#include "bomba.h"
#include <iostream>
#include<GL/glut.h>
#include <math.h>
#define PI 3.14

Bomba::Bomba(float vel,float raio, float x, float y, float R, float G, float B, float deltax, float deltay, float px1, float px2, float py1, float py2, int tipo, int enemy)
{
  this->raio = raio;
  this->corR = R;
  this->corG = G;
  this->corB = B;
  this->x = x;
  this->y = y;
  this->deltax = deltax;
  this->deltay = deltay;
  this->px1 = px1;
  this->px2 = px2;
  this->py1 = py1;
  this->py2 = py2;
  this->xInicial = x;
  this->yInicial = y;
  this->vel = vel;
  this->raioOriginal = raio;
  this->ajuste = false;
  this->tipo = tipo;
  this->enemy = enemy;
  this->bug = 0;
};

bool Bomba::getajuste() {
  return this->ajuste;
}

void Bomba::setajuste() {
    this->ajuste = true;
}

float Bomba::getRaio(){//Ajusta a coordenada X do Centro
    return this->raio;
}

void Bomba::setRaio(float r){//Ajusta a coordenada X do Centro
    this->raio = r;
}

float Bomba::getR(){//Ajusta a coordenada X do Centro
    return this->corR;
}

void Bomba::setR(float r){//Ajusta a coordenada X do Centro
    this->corR = r;
}
float Bomba::getG(){//Ajusta a coordenada X do Centro
    return this->corG;
}

void Bomba::setG(float r){//Ajusta a coordenada X do Centro
    this->corG = r;
}
float Bomba::getB(){//Ajusta a coordenada X do Centro
    return this->corB;
}

void Bomba::setB(float r){//Ajusta a coordenada X do Centro
    this->corB = r;
}

float Bomba::getx(){//Ajusta a coordenada X do Centro
    return this->x;
}

void Bomba::setx(float r){//Ajusta a coordenada X do Centro
    this->x = r;
}

float Bomba::gety(){//Ajusta a coordenada X do Centro
    return this->y;
}

void Bomba::sety(float r){//Ajusta a coordenada X do Centro
    this->y = r;
}

float Bomba::getdeltax(){//Ajusta a coordenada X do Centro
    return this->deltax;
}

void Bomba::setdeltax(float r){//Ajusta a coordenada X do Centro
    this->deltax = r;
}

float Bomba::getdeltay(){//Ajusta a coordenada X do Centro
    return this->deltay;
}

void Bomba::setdeltay(float r){//Ajusta a coordenada X do Centro
    this->deltay = r;
}

float Bomba::getpx1(){//Ajusta a coordenada X do Centro
    return this->px1;
}

void Bomba::setpx1(float r){//Ajusta a coordenada X do Centro
    this->px1 = r;
}

float Bomba::getpx2(){//Ajusta a coordenada X do Centro
    return this->px2;
}

void Bomba::setpx2(float r){//Ajusta a coordenada X do Centro
    this->px2 = r;
}

float Bomba::getpy1(){//Ajusta a coordenada X do Centro
    return this->py1;
}

void Bomba::setpy1(float r){//Ajusta a coordenada X do Centro
    this->py1 = r;
}

float Bomba::getpy2(){//Ajusta a coordenada X do Centro
    return this->py2;
}

void Bomba::setpy2(float r){//Ajusta a coordenada X do Centro
    this->py2 = r;
}

float Bomba::getxInicial(){//Ajusta a coordenada X do Centro
    return this->xInicial;
}

float Bomba::getyInicial(){//Ajusta a coordenada X do Centro
    return this->yInicial;
}

float Bomba::getVel(){//Ajusta a coordenada X do Centro
    return this->vel;
}



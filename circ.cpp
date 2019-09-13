#include "circ.h"
#include <iostream>
#include<GL/glut.h>
#include <math.h>
#define PI 3.14

Circulo::Circulo(float x, float y, float R, float G, float B)
{
  this->raio = 51;
  this->corR = R;
  this->corG = G;
  this->corB = B;
  this->x = x;
  this->y = y;
};


float Circulo::getRaio(){//Ajusta a coordenada X do Centro
    return this->raio;
}

void Circulo::setRaio(float r){//Ajusta a coordenada X do Centro
    this->raio = r;
}

float Circulo::getR(){//Ajusta a coordenada X do Centro
    return this->corR;
}

void Circulo::setR(float r){//Ajusta a coordenada X do Centro
    this->corR = r;
}
float Circulo::getG(){//Ajusta a coordenada X do Centro
    return this->corG;
}

void Circulo::setG(float r){//Ajusta a coordenada X do Centro
    this->corG = r;
}
float Circulo::getB(){//Ajusta a coordenada X do Centro
    return this->corB;
}

void Circulo::setB(float r){//Ajusta a coordenada X do Centro
    this->corB = r;
}

void Circulo::draw(Circulo *sqr)
{
    // draw square fill
  float angulo;
//int num_linhas;
glColor3f(this->corR, this->corG, this->corB);
glBegin(GL_LINE_LOOP);
for(int i = 0; i < 1000; i++) {
   angulo = i * 2 * PI / 1000; 
   glVertex2f(x + (cos(angulo) * 51), y + (sin(angulo) * 51)); 
}
glEnd();
}

Circulo* Circulo::drag(Circulo *sqr, float x, float y)
{
    sqr->x = x - 0.1;
    sqr->y = y - 0.1;
    return sqr;
}

float Circulo::getx(){//Ajusta a coordenada X do Centro
    return this->x;
}

void Circulo::setx(float r){//Ajusta a coordenada X do Centro
    this->x = r;
}

float Circulo::gety(){//Ajusta a coordenada X do Centro
    return this->y;
}

void Circulo::sety(float r){//Ajusta a coordenada X do Centro
    this->y = r;
}
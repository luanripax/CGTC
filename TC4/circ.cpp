#include "circ.h"
#include <iostream>
#include<GL/glut.h>
#include <cmath>
#define PI 3.14

#define deltaX 4.0
#define deltaY -0.5

#define deltaX2 4.0
#define deltaY2 8.9

#define deltaX3 1.0
#define deltaY3 9.8

#define deltaX4 3
#define deltaY4 1

#define x5 -4.8
#define y5 4.26

Circulo::Circulo(float raio, float x, float y, float R, float G, float B, int tipo)
{
  this->raio = raio;
  this->corR = R;
  this->corG = G;
  this->corB = B;
  this->x = x;
  this->y = y;
  this->tipo = tipo;
  if(tipo == 2) {
    int a, b, signal;
    signal = rand() % 2; 
    a = rand() % 3 + 1;
    if(signal == 0)
      a = -a;
    signal = rand() % 2;
    b = rand() % 3 + 1; 
    if(signal == 0)
      b = -b;
    printf("a: %d b: %d\n", a, b);
    this->xAnt = this->x - a;
    this->yAnt = this->y - b;
    this->deltax = abs(this->x - this->xAnt);
    this->deltay = abs(this->y - this->yAnt);
    this->deltax2 = this->x - this->xAnt;
    this->deltay2 = this->y - this->yAnt;
    this->theta = atan2(this->deltay2, this->deltax2)*180/M_PI;
    this->quadros = rand() % 60;
    this->rodar = false;
    this->z = this->theta*1000;
    this->tiros = 0;
    this->xini= x;
    this->yini = y;
  }
  this->xAnt = 0;
  this->yAnt = 0;
};

//void Circulo::setTheta() {
 // float valor;
//}
void Circulo::update() {

  this->deltax = abs(this->x - this->xAnt);
  this->deltay = abs(this->y - this->yAnt);
  this->deltax2 = this->x - this->xAnt;
  this->deltay2 = this->y - this->yAnt;
  this->theta = atan2(this->deltay2, this->deltax2)*180/M_PI;
  //this->z = this->theta*1000;

}
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
float Circulo::getTheta(){//Ajusta a coordenada X do Centro
    return this->theta;
}

void Circulo::setTheta(float r){//Ajusta a coordenada X do Centro
    this->theta = r;
}
float Circulo::getScale(){//Ajusta a coordenada X do Centro
    return this->scale;
}

void Circulo::setScale(float r){//Ajusta a coordenada X do Centro
    this->scale = r;
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

void Circulo::Desenha(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat scale, GLfloat thetaC, GLfloat theta3, GLfloat Raio, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

        glTranslatef(x, y, 0); // vai ate o centro do circulo
        glRotatef(thetaWheel, 0,0,1);
        glScaled(scale,scale,0);

              // SUPORTE HELICE 1

              glColor3f(0,0,0);
              glBegin(GL_POLYGON);
              glVertex3f(2.0-deltaX, 4.0-deltaY, 0.0);
              glVertex3f(5.0-deltaX, 4.0-deltaY, 0.0);
              glVertex3f(5.0-deltaX, 4.5-deltaY, 0.0);
              glVertex3f(2.0-deltaX, 4.5-deltaY, 0.0);
              glEnd();

              //SUPORTE HELICE 2
              glColor3f(0,0,0);
              glBegin(GL_POLYGON);
              glVertex3f(2.0-deltaX2, 4.0-deltaY2, 0.0);
              glVertex3f(5.0-deltaX2, 4.0-deltaY2, 0.0);
              glVertex3f(5.0-deltaX2, 4.5-deltaY2, 0.0);
              glVertex3f(2.0-deltaX2, 4.5-deltaY2, 0.0);
              glEnd();

            //ASA
            glColor3f(0,0,0);
            glBegin(GL_POLYGON);
            glVertex3f(-2, -7, 0.0);
            glVertex3f(3, 0, 0.0);
            glVertex3f(-2, 7, 0.0);
            glEnd();

            // CORPO
            glColor3f(R,G,B);
            float x1,y1,z1;
            int t;
            glBegin(GL_POLYGON);
            for(t = 0; t <= 360; t +=1)
            {
               x1 = 7*sin(t);
               y1 = 2*cos(t);
               z1 = 0;
             glVertex3f(x1,y1,z1);
            }
            glEnd();

            //CAUDA
            glColor3f(0,0,0);
            glBegin(GL_POLYGON);
            glVertex3f(2.0-8.5, 4.0-4.44, 0.0);
            glVertex3f(6.0-8.5, 4.0-4.44, 0.0);
            glVertex3f(6.0-8.5, 5.0-4.44, 0.0);
            glVertex3f(2.0-8.5, 5.0-4.44, 0.0);
            glEnd();

            glPushMatrix();

              glTranslatef(3, 0, 0);
              glColor3f(0,0,0);
              glBegin(GL_POLYGON);
              for(t = 0; t <= 360; t +=1)
              {
                x1 = 2*sin(t);
                y1 = 0.8*cos(t);
                z1 = 0;
                glVertex3f(x1,y1,z1);
                }
              glEnd();


            glPopMatrix();

          // CANHAO
          glPushMatrix();
               glTranslatef(7, 0, 0); 
               glRotatef(theta3, 0,0,1);

               glColor3f(0,0,0);
               glBegin(GL_POLYGON);
               glVertex3f(0, 0.4, 0.0);
               glVertex3f(3,0.4, 0.0);
               glVertex3f(3, -0.4, 0.0);
               glVertex3f(0,-0.4, 0.0);
               glEnd();
               

          glPopMatrix();

          glPushMatrix();

                glTranslatef(1, -4.65, 0); 
                glRotatef(40*thetaC, 1,0,0);
       
                glColor3f(1,1,0);
                glBegin(GL_POLYGON);
                glVertex3f(5.1 - deltaX2-1, 4.25 - deltaY2 + 4.55, 0.0);
                glVertex3f(4.6 - deltaX2-1, 5.5 - deltaY2+4.55, 0.0);
                glVertex3f(5.6 - deltaX2-1, 5.5 - deltaY2+4.55, 0.0);
                glEnd();

          glPopMatrix();

          glPushMatrix();

                glTranslatef(1, -4.65, 0); 
                glRotatef(40*thetaC, 1,0,0);
    
                glColor3f(1,1,0);
                glBegin(GL_POLYGON);
                glVertex3f(5.1 - deltaX2-1, 4.25 - deltaY2 +4.55, 0.0);
                glVertex3f(4.6 - deltaX2-1, 3 - deltaY2+4.55, 0.0);
                glVertex3f(5.6 - deltaX2-1, 3 - deltaY2+4.55, 0.0);
                glEnd();

          glPopMatrix();


          glPushMatrix();

                glTranslatef(1, 4.72, 0); 
                glRotatef(40*thetaC, 1,0,0);
          
                 glColor3f(1,1,0);
                glBegin(GL_POLYGON);
                glVertex3f(5.1 - deltaX2 -1, 4.25 + deltaY2 - 13.2, 0.0);
                glVertex3f(4.6 - deltaX2-1, 5.5 + deltaY2 - 13.2, 0.0);
                glVertex3f(5.6 - deltaX2-1, 5.5 + deltaY2 - 13.2, 0.0);
                glEnd();

          glPopMatrix();


              glPushMatrix();

                glTranslatef(1, 4.72, 0); 
                glRotatef(40*thetaC, 1,0,0);
      
                
              glColor3f(1,1,0);
              glBegin(GL_POLYGON);
              glVertex3f(5.1 - deltaX2-1, 4.25 + deltaY2 - 13.2, 0.0);
              glVertex3f(4.6 - deltaX2-1, 3 + deltaY2 - 13.2, 0.0);
              glVertex3f(5.6 - deltaX2-1, 3 + deltaY2 - 13.2, 0.0);
              glEnd();

          glPopMatrix();
        
    glPopMatrix();
 
}

void Circulo::DesenhaInimigo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat scale, GLfloat thetaC, GLfloat theta3, GLfloat Raio, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

        glTranslatef(x, y, 0); // vai ate o centro do circulo
        glRotatef(thetaWheel, 0,0,1);
        glScaled(scale,scale,0);

              // SUPORTE HELICE 1

              glColor3f(0,0,0);
              glBegin(GL_POLYGON);
              glVertex3f(2.0-deltaX, 4.0-deltaY, 0.0);
              glVertex3f(5.0-deltaX, 4.0-deltaY, 0.0);
              glVertex3f(5.0-deltaX, 4.5-deltaY, 0.0);
              glVertex3f(2.0-deltaX, 4.5-deltaY, 0.0);
              glEnd();

              //SUPORTE HELICE 2
              glColor3f(0,0,0);
              glBegin(GL_POLYGON);
              glVertex3f(2.0-deltaX2, 4.0-deltaY2, 0.0);
              glVertex3f(5.0-deltaX2, 4.0-deltaY2, 0.0);
              glVertex3f(5.0-deltaX2, 4.5-deltaY2, 0.0);
              glVertex3f(2.0-deltaX2, 4.5-deltaY2, 0.0);
              glEnd();

            //ASA
            glColor3f(0,0,0);
            glBegin(GL_POLYGON);
            glVertex3f(-2, -7, 0.0);
            glVertex3f(3, 0, 0.0);
            glVertex3f(-2, 7, 0.0);
            glEnd();

            // CORPO
            glColor3f(R,G,B);
            float x1,y1,z1;
            int t;
            glBegin(GL_POLYGON);
            for(t = 0; t <= 360; t +=1)
            {
               x1 = 7*sin(t);
               y1 = 2*cos(t);
               z1 = 0;
             glVertex3f(x1,y1,z1);
            }
            glEnd();

            //CAUDA
            glColor3f(0,0,0);
            glBegin(GL_POLYGON);
            glVertex3f(2.0-8.5, 4.0-4.44, 0.0);
            glVertex3f(6.0-8.5, 4.0-4.44, 0.0);
            glVertex3f(6.0-8.5, 5.0-4.44, 0.0);
            glVertex3f(2.0-8.5, 5.0-4.44, 0.0);
            glEnd();

            glPushMatrix();

              glTranslatef(3, 0, 0);
              glColor3f(0,0,0);
              glBegin(GL_POLYGON);
              for(t = 0; t <= 360; t +=1)
              {
                x1 = 2*sin(t);
                y1 = 0.8*cos(t);
                z1 = 0;
                glVertex3f(x1,y1,z1);
                }
              glEnd();


            glPopMatrix();

          // CANHAO
          glPushMatrix();
               glTranslatef(7, 0, 0); 
               glRotatef(theta3, 0,0,1);

               glColor3f(0,0,0);
               glBegin(GL_POLYGON);
               glVertex3f(0, 0.4, 0.0);
               glVertex3f(3,0.4, 0.0);
               glVertex3f(3, -0.4, 0.0);
               glVertex3f(0,-0.4, 0.0);
               glEnd();
               

          glPopMatrix();

          glPushMatrix();

                glTranslatef(1, -4.65, 0); 
                glRotatef(40*thetaC, 1,0,0);
       
                glColor3f(1,1,0);
                glBegin(GL_POLYGON);
                glVertex3f(5.1 - deltaX2-1, 4.25 - deltaY2 + 4.55, 0.0);
                glVertex3f(4.6 - deltaX2-1, 5.5 - deltaY2+4.55, 0.0);
                glVertex3f(5.6 - deltaX2-1, 5.5 - deltaY2+4.55, 0.0);
                glEnd();

          glPopMatrix();

          glPushMatrix();

                glTranslatef(1, -4.65, 0); 
                glRotatef(40*thetaC, 1,0,0);
    
                glColor3f(1,1,0);
                glBegin(GL_POLYGON);
                glVertex3f(5.1 - deltaX2-1, 4.25 - deltaY2 +4.55, 0.0);
                glVertex3f(4.6 - deltaX2-1, 3 - deltaY2+4.55, 0.0);
                glVertex3f(5.6 - deltaX2-1, 3 - deltaY2+4.55, 0.0);
                glEnd();

          glPopMatrix();


          glPushMatrix();

                glTranslatef(1, 4.72, 0); 
                glRotatef(40*thetaC, 1,0,0);
          
                 glColor3f(1,1,0);
                glBegin(GL_POLYGON);
                glVertex3f(5.1 - deltaX2 -1, 4.25 + deltaY2 - 13.2, 0.0);
                glVertex3f(4.6 - deltaX2-1, 5.5 + deltaY2 - 13.2, 0.0);
                glVertex3f(5.6 - deltaX2-1, 5.5 + deltaY2 - 13.2, 0.0);
                glEnd();

          glPopMatrix();


              glPushMatrix();

                glTranslatef(1, 4.72, 0); 
                glRotatef(40*thetaC, 1,0,0);
      
                
              glColor3f(1,1,0);
              glBegin(GL_POLYGON);
              glVertex3f(5.1 - deltaX2-1, 4.25 + deltaY2 - 13.2, 0.0);
              glVertex3f(4.6 - deltaX2-1, 3 + deltaY2 - 13.2, 0.0);
              glVertex3f(5.6 - deltaX2-1, 3 + deltaY2 - 13.2, 0.0);
              glEnd();

          glPopMatrix();
        
    glPopMatrix();
 
}

float Circulo::getx(){//Ajusta a coordenada X do Centro
    return this->x;
}

void Circulo::setx(float r){//Ajusta a coordenada X do Centro
    this->xAnt = this->x;
    this->x = r;
}

float Circulo::gety(){//Ajusta a coordenada X do Centro
    return this->y;
}

void Circulo::sety(float r){//Ajusta a coordenada X do Centro
    this->yAnt = this->y;
    this->y = r;
}
float Circulo::getxAnt(){//Ajusta a coordenada X do Centro
    return this->xAnt;
}

void Circulo::setxAnt(float r){//Ajusta a coordenada X do Centro
    this->xAnt = r;
}

float Circulo::getyAnt(){//Ajusta a coordenada X do Centro
    return this->yAnt;
}

void Circulo::setyAnt(float r){//Ajusta a coordenada X do Centro
    this->yAnt = r;
}

int Circulo::getTipo(){//Ajusta a coordenada X do Centro
    return this->tipo;
}

void Circulo::setTipo(int r){//Ajusta a coordenada X do Centro
    this->tipo = r;
}

void Circulo::DesenhaAviao(float x, float y)
{
    glPushMatrix();
        glTranslatef(x, y, 0);
        //Desenha base
        float angulo;
  //int num_linhas;
        glColor3f(0.0, 0.0, 0.5);
        glBegin(GL_POLYGON);
         for (int i = 0; i < 1000; i++)
        {
          angulo = i * 2 * 3.14 / 1000;
         glVertex2f(x + (cos(angulo) * this->raio), y + (sin(angulo) * this->raio));
        }
        glEnd();
        
    glPopMatrix();
 
}
#include "aviao.h"
#include <math.h>
#include <stdio.h>
//#define deltaX 8.5
//#define deltaY 

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

Robo::Robo(GLfloat raio, GLfloat gX, GLfloat gY, GLfloat R, GLfloat G, GLfloat B) {
 
    this->raio = raio;
    this->gX = gX;
    this->gY = gY;
    this->R = R;
    this->G = G;
    this->B = B;
}

void Robo::DesenhaRect(GLint height, GLint width, GLfloat Raio, GLfloat R, GLfloat G, GLfloat B)
{
  float angulo;
  //int num_linhas;
  glColor3f(R,G,B);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 1000; i++)
  {
    angulo = i * 2 * M_PI / 1000;
    glVertex2f(height + (cos(angulo) * Raio), width + (sin(angulo) * Raio));
  }
  glEnd();

}

void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    /*
    int i;
    GLfloat x, y;
    glColor3f(R,G,B);
    glPointSize(3);
    glBegin(GL_POINTS);
        for (i = 0; i < 360; i+=20)
        {
            x = radius * cos(M_PI*i/180);
            y = radius * sin(M_PI*i/180);
            glVertex3f(x, y, 0);
        }
    glEnd();
     */


    /*


      // SUPORTE HELICE 1

    glColor3f(0.5,0.5,0);
    glBegin(GL_POLYGON);
    glVertex3f(2.0-deltaX, 4.0-deltaY, 0.0);
    glVertex3f(5.0-deltaX, 4.0-deltaY, 0.0);
    glVertex3f(5.0-deltaX, 4.5-deltaY, 0.0);
    glVertex3f(2.0-deltaX, 4.5-deltaY, 0.0);
    glEnd();

    //SUPORTE HELICE 2
    glColor3f(0.5,0.5,0);
    glBegin(GL_POLYGON);
    glVertex3f(2.0-deltaX2, 4.0-deltaY2, 0.0);
    glVertex3f(5.0-deltaX2, 4.0-deltaY2, 0.0);
    glVertex3f(5.0-deltaX2, 4.5-deltaY2, 0.0);
    glVertex3f(2.0-deltaX2, 4.5-deltaY2, 0.0);
    glEnd();

    // ASA
    glColor3f(0.5,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(-2, -7, 0.0);
    glVertex3f(3, 0, 0.0);
    glVertex3f(-2, 7, 0.0);
    glEnd();

   
    // CORPO AVIAO
    glColor3f(0,0,0);
	  float x,y,z;
	  int t;
    glBegin(GL_POLYGON);
    for(t = 0; t <= 360; t +=1)
	  {
        x = 7*sin(t);
	      y = 3*cos(t);
	      z = 0;
	      glVertex3f(x,y,z);
    }
    glEnd();
       
    
     // CABINE
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    for(t = 0; t <= 360; t +=1)
	  {
        x = 2*sin(t);
	      y = 0.8*cos(t);
	      z = 0;
	      glVertex3f(x+4.0,y,z);
    }
    glEnd();
       
    // CAUDA               
    glColor3f(0.5,0,0);
    glBegin(GL_POLYGON);
   glVertex3f(2.0-8.5, 4.0-4.44, 0.0);
   glVertex3f(6.0-8.5, 4.0-4.44, 0.0);
   glVertex3f(6.0-8.5, 5.0-4.44, 0.0);
   glVertex3f(2.0-8.5, 5.0-4.44, 0.0);
    glEnd();

    //CANHAO
    glPushMatrix();
    //glRotatef(-20*radius, 0,1,0);
    glColor3f(0,1,1);
    glBegin(GL_POLYGON);
    glVertex3f(2.0-x5, 4.0-y5, 0.0);
    glVertex3f(4.0-x5, 4.0-y5, 0.0);
    glVertex3f(4.0-x5, 4.6-y5, 0.0);
    glVertex3f(2.0-x5, 4.6-y5, 0.0);
    glEnd();
    glPopMatrix();



    glPushMatrix();

    //glTranslatef(5.1-deltaX2, 4.25-deltaY2, 0);
    glRotatef(-20*radius, 0,1,0);

    // HELICE1
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    glVertex3f(5.1 - deltaX2, 4.25 - deltaY2, 0.0);
    glVertex3f(4.6 - deltaX2, 5.5 - deltaY2, 0.0);
    glVertex3f(5.6 - deltaX2, 5.5 - deltaY2, 0.0);
    glEnd();

    glPopMatrix();

    
    glPushMatrix();
    // HELICE2
    glRotatef(-20*radius, 0,1,0);
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    glVertex3f(5.1 - deltaX2, 4.25 - deltaY2, 0.0);
    glVertex3f(4.6 - deltaX2, 3 - deltaY2, 0.0);
    glVertex3f(5.6 - deltaX2, 3 - deltaY2, 0.0);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    // HELICE3
    glRotatef(-20*radius, 0,1,0);
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    glVertex3f(5.1 - deltaX2, 4.25 + deltaY2 - 8.5, 0.0);
    glVertex3f(4.6 - deltaX2, 5.5 + deltaY2 - 8.5, 0.0);
    glVertex3f(5.6 - deltaX2, 5.5 + deltaY2 - 8.5, 0.0);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    // HELICE4 
    glRotatef(-20*radius, 0,1,0);
    glColor3f(1,1,0);
    glBegin(GL_POLYGON);
    glVertex3f(5.1 - deltaX2, 4.25 + deltaY2 - 8.5, 0.0);
    glVertex3f(4.6 - deltaX2, 3 + deltaY2 - 8.5, 0.0);
    glVertex3f(5.6 - deltaX2, 3 + deltaY2 - 8.5, 0.0);
    glEnd();

    glPopMatrix();

    /*
    glPushMatrix();
    glTranslatef(5.1-deltaX2, 4.25-deltaY2, 0);
    glRotatef(-20*radius, 1,0,0);
    glColor3f(0,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex3f(2.0-deltaX3, 4.0-deltaY3, 0.0);
    glVertex3f(2.5-deltaX3, 4.0-deltaY3, 0.0);
    glVertex3f(2.5-deltaX3, 6.5-deltaY3, 0.0);
    glVertex3f(2.0-deltaX3, 6.5-deltaY3, 0.0);
    glEnd();
    glPopMatrix();
    */
     /*
     */
    
}
/*
void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3)
{
    glPushMatrix();
        //Desenha braco da base
        glTranslatef(x, y, 0);
        glRotatef(theta1, 0,0,1);
        DesenhaRect(paddleHeight, paddleWidth, 0, 0, 1); 

        //Desenha braco do meio
        glTranslatef(0.0, paddleHeight, 0);
        glRotatef(theta2, 0,0,1);
        DesenhaRect(paddleHeight, paddleWidth, 1, 1, 0); 
    
        //Desenha braco do fim
        glTranslatef(0.0, paddleHeight, 0);
        glRotatef(theta3, 0,0,1);
        DesenhaRect(paddleHeight, paddleWidth, 0, 1, 0); 

    glPopMatrix();
 
}
*/
float angulo;

void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat scale, GLfloat thetaC, GLfloat theta3, GLfloat Raio, GLfloat R, GLfloat G, GLfloat B)
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
            glColor3f(0,0.7,0);
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

                    /*
                    glColor3f(1,1,1);
                    glBegin(GL_POLYGON);
                    for (int i = 0; i < 1000; i++)
                      {
                       angulo = i * 2 * M_PI / 1000;
                      glVertex2f(0 + (cos(angulo) * 0.25), 0 + (sin(angulo) * 0.25));
                    }
                    glEnd();
                    */
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
                  /*
                  glColor3f(1,1,1);
                    glBegin(GL_POLYGON);
                    for (int i = 0; i < 1000; i++)
                      {
                       angulo = i * 2 * M_PI / 1000;
                      glVertex2f(0 + (cos(angulo) * 0.25), 0 + (sin(angulo) * 0.25));
                    }
                    glEnd();
                  */
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
                  /*
                  glColor3f(1,1,1);
                    glBegin(GL_POLYGON);
                    for (int i = 0; i < 1000; i++)
                      {
                       angulo = i * 2 * M_PI / 1000;
                      glVertex2f(0 + (cos(angulo) * 0.25), 0 + (sin(angulo) * 0.25));
                    }
                    glEnd();
                  */
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
                  /*
                  glColor3f(1,1,1);
                    glBegin(GL_POLYGON);
                    for (int i = 0; i < 1000; i++)
                      {
                       angulo = i * 2 * M_PI / 1000;
                      glVertex2f(0 + (cos(angulo) * 0.25), 0 + (sin(angulo) * 0.25));
                    }
                    glEnd();
                  */
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
                  /*
                  glColor3f(1,1,1);
                    glBegin(GL_POLYGON);
                    for (int i = 0; i < 1000; i++)
                      {
                       angulo = i * 2 * M_PI / 1000;
                      glVertex2f(0 + (cos(angulo) * 0.25), 0 + (sin(angulo) * 0.25));
                    }
                    glEnd();
                  */
                
              glColor3f(1,1,0);
              glBegin(GL_POLYGON);
              glVertex3f(5.1 - deltaX2-1, 4.25 + deltaY2 - 13.2, 0.0);
              glVertex3f(4.6 - deltaX2-1, 3 + deltaY2 - 13.2, 0.0);
              glVertex3f(5.6 - deltaX2-1, 3 + deltaY2 - 13.2, 0.0);
              glEnd();

          glPopMatrix();

        //glTranslatef(x, y, 0); // a base irase mecher
        //printf("%f %f\n",x, y);
         //glRotatef(thetaWheel, 0,0,1);
        //Desenha base
        //DesenhaRect(x, y, Raio, R, G, B); 
        
        //Desenha roda 1
        //glPushMatrix();
           //glTranslatef(x, y, 0); // coordenada presa a base
           //glRotatef(thetaWheel, 0,0,1);
           //glScaled(scale,scale,0);
           //DesenhaCirc(thetaWheel, x, y, thetaC); 
        //glPopMatrix();
       // //Desenha roda 2
      //  glPushMatrix();
       //     glTranslatef(baseWidth/2.0, 0, 0);
       //     glRotatef(thetaWheel, 0,0,1);
       //     DesenhaCirc(radiusWheel, 1, 1, 1);
       // glPopMatrix();

        //Desenha bracos
        //DesenhaBraco(0.0, baseHeight, theta1, theta2, theta3);
        
    glPopMatrix();
 
}

void Robo::RodaBraco1(GLfloat inc)
{
    gTheta1 += inc;
}

void Robo::RodaBraco2(GLfloat inc)
{
    gTheta2 += inc;
}

void Robo::RodaBraco3(GLfloat inc)
{
    gTheta3 += inc;
}

void Robo::MoveEmX(GLfloat dx)
{
    gX += dx;
    gThetaWheel -= dx*360/(2*M_PI*radiusWheel); 
}

void Robo::MoveEmY(GLfloat dy)
{
    gY += dy;
}

void Robo::MoveEmXDir(GLfloat dx){
    MoveEmX(direction*dx); 
}

GLfloat Robo::ObtemX(){
    return gX;
}

GLfloat Robo::ObtemY(){
    return gY;
}
    
void Robo::ChangeDirection()
{
    direction *= -1.0; 
}

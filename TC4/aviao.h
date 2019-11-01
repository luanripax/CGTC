#ifndef ROBO_H
#define	ROBO_H
#include <GL/gl.h>
#include <GL/glu.h>
// Dimensions
#define paddleHeight 80
#define paddleWidth 10
#define baseHeight 40
#define baseWidth 100
#define radiusWheel 30

class Robo {
    GLfloat raio;
    GLfloat gX; 
    GLfloat gY; 
    GLfloat gTheta1; 
    GLfloat gTheta2; 
    GLfloat gTheta3; 
    GLfloat gThetaWheel; 
    GLfloat direction;
    GLfloat R;
    GLfloat G;
    GLfloat B;
private:
    void DesenhaRect(  GLint height, GLint width,GLfloat Raio, 
                    GLfloat R, GLfloat G, GLfloat B);
    void DesenhaCirc(  GLint radius, GLfloat R, 
                    GLfloat G, GLfloat B);
    void DesenhaBraco(   GLfloat x, GLfloat y, GLfloat theta1, 
                    GLfloat theta2, GLfloat theta3);
   

public:
    Robo(GLfloat raio, GLfloat gX, GLfloat gY, GLfloat R, GLfloat G, GLfloat B);
    //DesenhaRobo(gX, gY, gThetaWheel, gTheta1, 
                //gTheta2, gTheta3);
     void DesenhaRobo( GLfloat x, GLfloat y, GLfloat thetaWheel, 
                    GLfloat theta1, GLfloat theta2, GLfloat theta3, GLfloat raio, GLfloat R, GLfloat G, GLfloat B);
  
    void RodaBraco1(GLfloat inc);
    void RodaBraco2(GLfloat inc);
    void RodaBraco3(GLfloat inc);
    void MoveEmX(GLfloat dx);
    void MoveEmY(GLfloat dy);
    GLfloat ObtemX();
    GLfloat ObtemY();

    void MoveEmXDir(GLfloat dx);
    void ChangeDirection();
};

#endif	/* ROBO_H */


#include <GL/glu.h>

class Circulo
{
  private:
  float raio, corR, corG, corB, x, y, xAnt, yAnt, theta, scale, deltax, deltay, deltax2, deltay2;
  int tipo;
  public:
    Circulo(float raio, float x, float y, float R, float G, float B, int tipo);
    float getRaio();
    void setRaio(float raio);
    float getR();
    void setR(float r);
    float getG();
    void setG(float g);
    float getB();
    void setB(float b);
     float getx();
    void setx(float b);
     float gety();
    void sety(float b);
    float getxAnt();
    void setxAnt(float b);
     float getyAnt();
    void setyAnt(float b);
    int getTipo();
    void setTheta(float a);
    float getTheta();
    void setScale(float a);
    float getScale();
    void setTipo(int r);
    void draw(Circulo *circ);
    void Desenha(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat scale, GLfloat thetaC, GLfloat theta3, GLfloat Raio, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaInimigo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat scale, GLfloat thetaC, GLfloat theta3, GLfloat Raio, GLfloat R, GLfloat G, GLfloat B);
    //Circulo* drag(Circulo *sqr, float x, float y);
    void DesenhaAviao( float x, float y);
};
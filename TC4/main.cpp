#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <list>
#include "tinyxml.h"
#include "circ.h"
#include "rec.h"
#include "aviao.h"
#include "bomba.h"
#define FPS 60
#define LAMBDA 111.11
#define LAMBDA2 6.66666667
#define LAMBDA3 1.5057
using namespace std;
 
//Key status
int keyStatus[256];

// Window dimensions
const GLint Width = 700;
const GLint Height = 700;

// Viewing dimensions
const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;
 
int animate = 0;

Robo *robo;

// ----------------------------------------------

int estado;
int botao;
// prototipos das funcoes
float delta;
float delta2;

//config do fundo
float largura;
float altura;

bool w = false;
bool a = false;
bool s = false;
bool d = false;

bool colisao = false;

long int inicial = time(NULL);
long int final, quadros = 0;
float vel;
bool fimDecolagem = false;

// titulo
//std::string titulo;
const char *titulo;

Circulo *circ;

Circulo *Arena;
Circulo *Aviao;
Bomba *bomba;
Retangulo *Pista;
Retangulo *Pista2;

float deslocamentox = 0;
float deslocamentoy = 0;

// 0 - Arena 1 - Aviao 2 - Inimigo Aereo 3 - Inimigo terrestre

std::list<Circulo *> inimigos;
std::list<Circulo *> inimigosOriginal;
std::list<Bomba *> bombas;

bool startGame = false;
bool primeiroDesenho = false;
float tamPista;
float distLimite;
float raioVoador;
float distAux;
float RaioAux;
const char *nome;
const char *tipo;
const char *caminho;
float velocidade;
float velocidadeIdeal;
float aceleracaoIdeal;
float deltax, deltay;
float deltax2, deltay2;
float raioOriginal;
float xOriginal, yOriginal;
float pistax1Original, pistax2Original, pistay1Original, pistay2Original;
float deltaxOriginal, deltayOriginal;
float thetaOriginal;
bool jaPassou = false;
bool curvando;

float curva;
float fator=0;
int z=0;

float theta = 0;
float tangente=0;
float scale = 0;
float thetaCanhao=0;
int m=0;
float thetaHelice = 0;
bool aApertado = false;
bool dApertado = false;
float velTiro;

float alberto, jadir;
static char str[2000];
void * font = GLUT_BITMAP_8_BY_13;
int destruidas=0;
int restantes=0;
float velInimigo=0;
float scaleInimigo;
float thetaHeliceInimigo=0;
bool gameover = false;
bool lose = false;
int restanteOriginal;

void PrintScore(GLfloat x, GLfloat y)
{
    //Create a string to be printed
    char *tmpStr;
    sprintf(str, "Bases destruidas: %d", destruidas);
    //Define the position to start printing
    glColor3f(1, 1, 1);
    glRasterPos2f(x, y);
    //Print  the first Char with a certain font
    //glutBitmapLength(font,(unsigned char*)str);
    tmpStr = str;
    //Print each of the other Char at time
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }
}

void PrintScore2(GLfloat x, GLfloat y)
{
    //Create a string to be printed
    char *tmpStr;
    sprintf(str, "Bases restantes:  %d", restantes);
    //Define the position to start printing
    glColor3f(1, 1, 1);
    glRasterPos2f(x, y);
    //Print  the first Char with a certain font
    //glutBitmapLength(font,(unsigned char*)str);
    tmpStr = str;
    //Print each of the other Char at time
    while( *tmpStr ){
        glutBitmapCharacter(font, *tmpStr);
        tmpStr++;
    }

}

void gameOverLoose(GLfloat x, GLfloat y)
{
    //Create a string to be printed
    char *tmpStr;
    glColor3f(1, 0, 0);
    sprintf(str, "Game Over - Voce perdeu!");
    //Define the position to start printing
    glColor3f(1, 0, 0);
    glRasterPos2f(x, y);
    //Print  the first Char with a certain font
    //glutBitmapLength(font,(unsigned char*)str);
    tmpStr = str;
    //Print each of the other Char at time
    while( *tmpStr ){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *tmpStr);
        tmpStr++;
    }
    lose = true;
}

void gameOverWin(GLfloat x, GLfloat y)
{
    //Create a string to be printed
    char *tmpStr;
    glColor3f(0, 1, 0);
    sprintf(str, "Game Over - Voce venceu!");
    //Define the position to start printing
    glColor3f(0, 1, 0);
    glRasterPos2f(x, y);
    //Print  the first Char with a certain font
    //glutBitmapLength(font,(unsigned char*)str);
    tmpStr = str;
    //Print each of the other Char at time
    while( *tmpStr ){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *tmpStr);
        tmpStr++;
    }
    

}

void desenhaPista() {

  glColor3f(0, 0, 0);
  glBegin(GL_LINES);
      glVertex2f(Pista2->getx1(), Pista2->gety1());
      glVertex2f(Pista2->getx2(), Pista2->gety2());
  glEnd();

}
bool ajuste = false;
 float aux;

bool colisaoBomba(Bomba* bomba) {

  colisao = false;
  float distancia;
  for (std::list<Circulo *>::iterator it = inimigos.begin(); it != inimigos.end(); it++)
  {
    distancia = sqrt(pow((*it)->getx() - bomba->getx(), 2) + pow((*it)->gety() - bomba->gety(), 2));
    if (distancia < ((*it)->getRaio() + bomba->getRaio()) && (*it)->getTipo() == 3)
    {
      inimigos.erase(it++);;
      destruidas++;
      restantes--;
      if(restantes==0) {
        startGame = false;  //Without keyStatus trick
        fimDecolagem = false;
        jaPassou = false;
        gameover = true;
      }
      
      break;
    }
  }
  return colisao;
}

bool morteInimigo(Bomba* bomba) {

  colisao = false;
  float distancia;
  for (std::list<Circulo *>::iterator it = inimigos.begin(); it != inimigos.end(); it++)
  {
    distancia = sqrt(pow((*it)->getx() - bomba->getx(), 2) + pow((*it)->gety() - bomba->gety(), 2));
    if (distancia < ((*it)->getRaio() + bomba->getRaio()) && (*it)->getTipo() == 2)
    {
      inimigos.erase(it++);;
      //destruidas++;
      //restantes--;
      break;
    }
  }
  return colisao;
}

bool morteJogador(Bomba* bomba) {

  colisao = false;
  float distancia;

    distancia = sqrt(pow(Aviao->getx() - bomba->getx(), 2) + pow(Aviao->gety() - bomba->gety(), 2));
    if (distancia < (Aviao->getRaio() + bomba->getRaio()))
    {
        
       colisao = true;
    }
  
  return colisao;
}


void desenhaBombas() {

  float distancia;
  for (std::list<Bomba *>::iterator it = bombas.begin(); it != bombas.end(); it++) {

  if((*it)->enemy) {

      distancia = sqrt(pow((*it)->getxInicial() - (*it)->getx(), 2) + pow((*it)->getyInicial() - (*it)->gety(), 2));
    //if(distancia < 240*(*it)->getVel()) {

    if((*it)->bug == 0) {
    float angulo;
    //int num_linhas;
    glColor3f((*it)->getR(), (*it)->getG(), (*it)->getB());
    glBegin(GL_POLYGON);
    for (int i = 0; i < 1000; i++)
    {
    angulo = i * 2 * M_PI / 1000;
    glVertex2f((*it)->getx() + (cos(angulo) * (*it)->getRaio()), (*it)->gety() + (sin(angulo) * (*it)->getRaio()));
    }
    glEnd();
    }
   
    //aux = (*it)->raioOriginal/2;
    //(*it)->setRaio((*it)->getRaio() - aux/240);


    if((*it)->deltax > 0 && (*it)->deltay == 0) { // Pista reta horizontalmente

          if((*it)->getpx2() - (*it)->getpx1() > 0)
            (*it)->setx((*it)->getx() + (*it)->vel);
          if((*it)->getpx2() - (*it)->getpx1() < 0)
            (*it)->setx((*it)->getx() - (*it)->vel);
    }
    if((*it)->deltay > 0 && (*it)->deltax == 0) { // Pista reta verticalmente
          if((*it)->getpy2() - (*it)->getpy1() > 0)
            (*it)->sety((*it)->gety() + (*it)->vel);
          if((*it)->getpy2() - (*it)->getpy1() < 0)
            (*it)->sety((*it)->gety() - (*it)->vel);                 
    }

    if((*it)->deltax > 0 && (*it)->deltay > 0) { // Pista inclinada

          if((*it)->deltax > (*it)->deltay) {
            if((*it)->getpx2() - (*it)->getpx1() > 0)
              (*it)->setx((*it)->getx() + (*it)->vel);
            if((*it)->getpx2() - (*it)->getpx1() < 0)
              (*it)->setx((*it)->getx() - (*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() > 0) 
               (*it)->sety((*it)->gety() + (*it)->vel/((*it)->deltax/(*it)->deltay));
            if((*it)->getpy2() - (*it)->getpy1() < 0) 
              (*it)->sety((*it)->gety() - (*it)->vel/((*it)->deltax/(*it)->deltay));
          }
          if((*it)->deltay > (*it)->deltax) {
 
            if((*it)->getpy2() - (*it)->getpy1() > 0)
              (*it)->sety((*it)->gety() + (*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() < 0)
              (*it)->sety((*it)->gety() - (*it)->vel);
            if((*it)->getpx2() - (*it)->getpx1() > 0) 
               (*it)->setx((*it)->getx() + (*it)->vel/((*it)->deltay/(*it)->deltax));
            if((*it)->getpx2() - (*it)->getpx1() < 0) 
              (*it)->setx((*it)->getx() - (*it)->vel/((*it)->deltay/(*it)->deltax));
          }
          if((*it)->deltay == (*it)->deltax) {

            if((*it)->getpx2() - (*it)->getpx1() > 0)
              (*it)->setx((*it)->getx() + (*it)->vel);
            if((*it)->getpx2() - (*it)->getpx1() < 0)
              (*it)->setx((*it)->getx() - (*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() > 0)
              (*it)->sety((*it)->gety() + (*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() < 0)
              (*it)->sety((*it)->gety() - (*it)->vel);
          }
          
    }
    if(morteJogador(*it) && fimDecolagem) {
      (*it)->bug = 1;
      fimDecolagem = false;
      startGame = false;  //Without keyStatus trick
             //fimDecolagem = false;
             jaPassou = false;
             gameover = true;
      //printf("morreu!\n");
    }
      
      //printf("lenght: %d, pos:%d\n", bombas.size(), bombas[bombas.size()]);
      
  }

  if((*it)->tipo == 0 && !(*it)->enemy) { //BOMBA     

  distancia = sqrt(pow((*it)->getxInicial() - (*it)->getx(), 2) + pow((*it)->getyInicial() - (*it)->gety(), 2));
  if(distancia < 120*(*it)->getVel()) {

    float angulo;
    //int num_linhas;
    glColor3f((*it)->getR(), (*it)->getG(), (*it)->getB());
    glBegin(GL_POLYGON);
    for (int i = 0; i < 1000; i++)
    {
    angulo = i * 2 * M_PI / 1000;
    glVertex2f((*it)->getx() + (cos(angulo) * (*it)->getRaio()), (*it)->gety() + (sin(angulo) * (*it)->getRaio()));
    }
    glEnd();

   
    aux = (*it)->raioOriginal/2;
    (*it)->setRaio((*it)->getRaio() - aux/120);


    if((*it)->deltax > 0 && (*it)->deltay == 0) { // Pista reta horizontalmente

          if((*it)->getpx2() - (*it)->getpx1() > 0)
            (*it)->setx((*it)->getx() + (*it)->vel);
          if((*it)->getpx2() - (*it)->getpx1() < 0)
            (*it)->setx((*it)->getx() - (*it)->vel);
    }
    if((*it)->deltay > 0 && (*it)->deltax == 0) { // Pista reta verticalmente
          if((*it)->getpy2() - (*it)->getpy1() > 0)
            (*it)->sety((*it)->gety() + (*it)->vel);
          if((*it)->getpy2() - (*it)->getpy1() < 0)
            (*it)->sety((*it)->gety() - (*it)->vel);                 
    }

    if((*it)->deltax > 0 && (*it)->deltay > 0) { // Pista inclinada

          if((*it)->deltax > (*it)->deltay) {
            if((*it)->getpx2() - (*it)->getpx1() > 0)
              (*it)->setx((*it)->getx() + (*it)->vel);
            if((*it)->getpx2() - (*it)->getpx1() < 0)
              (*it)->setx((*it)->getx() - (*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() > 0) 
               (*it)->sety((*it)->gety() + (*it)->vel/((*it)->deltax/(*it)->deltay));
            if((*it)->getpy2() - (*it)->getpy1() < 0) 
              (*it)->sety((*it)->gety() - (*it)->vel/((*it)->deltax/(*it)->deltay));
          }
          if((*it)->deltay > (*it)->deltax) {
 
            if((*it)->getpy2() - (*it)->getpy1() > 0)
              (*it)->sety((*it)->gety() + (*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() < 0)
              (*it)->sety((*it)->gety() - (*it)->vel);
            if((*it)->getpx2() - (*it)->getpx1() > 0) 
               (*it)->setx((*it)->getx() + (*it)->vel/((*it)->deltay/(*it)->deltax));
            if((*it)->getpx2() - (*it)->getpx1() < 0) 
              (*it)->setx((*it)->getx() - (*it)->vel/((*it)->deltay/(*it)->deltax));
          }
          if((*it)->deltay == (*it)->deltax) {

            if((*it)->getpx2() - (*it)->getpx1() > 0)
              (*it)->setx((*it)->getx() + (*it)->vel);
            if((*it)->getpx2() - (*it)->getpx1() < 0)
              (*it)->setx((*it)->getx() - (*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() > 0)
              (*it)->sety((*it)->gety() + (*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() < 0)
              (*it)->sety((*it)->gety() - (*it)->vel);
          }
          
    }


  } else {
      colisaoBomba(*it);
      bombas.erase(it++);
      //printf("bomba explodiu\n");
  }
      
  } else if((*it)->tipo == 1 && !(*it)->enemy) { // TIRO

    morteInimigo(*it);

    distancia = sqrt(pow(Arena->getx() - (*it)->getx(), 2) + pow(Arena->gety() - (*it)->gety(), 2));
    if(distancia < Arena->getRaio() + (*it)->getRaio()) {

    float angulo;
    //int num_linhas;
    glColor3f((*it)->getR(), (*it)->getG(), (*it)->getB());
    glBegin(GL_POLYGON);
    for (int i = 0; i < 1000; i++)
    {
    angulo = i * 2 * M_PI / 1000;
    glVertex2f((*it)->getx() + (cos(angulo) * (*it)->getRaio()), (*it)->gety() + (sin(angulo) * (*it)->getRaio()));
    }
    glEnd();

    if((*it)->deltax > 0 && (*it)->deltay == 0) { // Pista reta horizontalmente

            if(!(*it)->getajuste()) {
            if((*it)->getpx2() - (*it)->getpx1() > 0)
              (*it)->setx((*it)->getx() + Aviao->getRaio()*1.2);
            if((*it)->getpx2() - (*it)->getpx1() < 0)
              (*it)->setx((*it)->getx() - Aviao->getRaio()*1.2);
              (*it)->setajuste();
            }

          if((*it)->getpx2() - (*it)->getpx1() > 0)
            (*it)->setx((*it)->getx() + velTiro*(*it)->vel);
          if((*it)->getpx2() - (*it)->getpx1() < 0)
            (*it)->setx((*it)->getx() - velTiro*(*it)->vel);
    }
    if((*it)->deltay > 0 && (*it)->deltax == 0) { // Pista reta verticalmente

            if(!(*it)->getajuste()) {
            if((*it)->getpy2() - (*it)->getpy1() > 0) 
               (*it)->sety((*it)->gety() + Aviao->getRaio()*1.2);
            if((*it)->getpy2() - (*it)->getpy1() < 0) 
              (*it)->sety((*it)->gety() - Aviao->getRaio()*1.2);
              (*it)->setajuste();
            }

          if((*it)->getpy2() - (*it)->getpy1() > 0)
            (*it)->sety((*it)->gety() + velTiro*(*it)->vel);
          if((*it)->getpy2() - (*it)->getpy1() < 0)
            (*it)->sety((*it)->gety() - velTiro*(*it)->vel);                 
    }

    if((*it)->deltax > 0 && (*it)->deltay > 0) { // Pista inclinada


          if((*it)->deltax > (*it)->deltay) {

            if(!(*it)->getajuste()) {
            if((*it)->getpx2() - (*it)->getpx1() > 0)
              (*it)->setx((*it)->getx() + Aviao->getRaio()*1.2);
            if((*it)->getpx2() - (*it)->getpx1() < 0)
              (*it)->setx((*it)->getx() - Aviao->getRaio()*1.2);
            if((*it)->getpy2() - (*it)->getpy1() > 0) 
               (*it)->sety((*it)->gety() + (Aviao->getRaio()*1.2)/((*it)->deltax/(*it)->deltay));
            if((*it)->getpy2() - (*it)->getpy1() < 0) 
              (*it)->sety((*it)->gety() - (Aviao->getRaio()*1.2)/((*it)->deltax/(*it)->deltay));
              (*it)->setajuste();
            }
            if((*it)->getpx2() - (*it)->getpx1() > 0)
              (*it)->setx((*it)->getx() + velTiro*vel);
            if((*it)->getpx2() - (*it)->getpx1() < 0)
              (*it)->setx((*it)->getx() - velTiro*vel);
            if((*it)->getpy2() - (*it)->getpy1() > 0) 
               (*it)->sety((*it)->gety() + velTiro* ((*it)->vel/((*it)->deltax/(*it)->deltay)));
            if((*it)->getpy2() - (*it)->getpy1() < 0) 
              (*it)->sety((*it)->gety() - velTiro* ((*it)->vel/((*it)->deltax/(*it)->deltay)));
          }
          if((*it)->deltay > (*it)->deltax) {

            
            if(!(*it)->getajuste()) {
            if((*it)->getpy2() - (*it)->getpy1() > 0)
              (*it)->sety((*it)->gety() + Aviao->getRaio()*1.2);
            if((*it)->getpy2() - (*it)->getpy1() < 0)
              (*it)->sety((*it)->gety() - Aviao->getRaio()*1.2);
            if((*it)->getpx2() - (*it)->getpx1() > 0) 
               (*it)->setx((*it)->getx() + (Aviao->getRaio()*1.2)/((*it)->deltay/(*it)->deltax));
            if((*it)->getpx2() - (*it)->getpx1() < 0) 
              (*it)->setx((*it)->getx() - (Aviao->getRaio()*1.2)/((*it)->deltay/(*it)->deltax));
              (*it)->setajuste();
            }
 
            if((*it)->getpy2() - (*it)->getpy1() > 0)
              (*it)->sety((*it)->gety() + velTiro*(*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() < 0)
              (*it)->sety((*it)->gety() - velTiro*(*it)->vel);
            if((*it)->getpx2() - (*it)->getpx1() > 0) 
               (*it)->setx((*it)->getx() + velTiro*((*it)->vel/((*it)->deltay/(*it)->deltax)));
            if((*it)->getpx2() - (*it)->getpx1() < 0) 
               (*it)->setx((*it)->getx() - velTiro*((*it)->vel/((*it)->deltay/(*it)->deltax)));
          }
          if((*it)->deltay == (*it)->deltax) {

            if(!(*it)->getajuste()) {
            if((*it)->getpx2() - (*it)->getpx1() > 0)
              (*it)->setx((*it)->getx() + Aviao->getRaio()*1.2);
            if((*it)->getpx2() - (*it)->getpx1() < 0)
              (*it)->setx((*it)->getx() - Aviao->getRaio()*1.2);
            if((*it)->getpy2() - (*it)->getpy1() > 0)
              (*it)->sety((*it)->gety() + Aviao->getRaio()*1.2);
            if((*it)->getpy2() - (*it)->getpy1() < 0)
              (*it)->sety((*it)->gety() - Aviao->getRaio()*1.2);
              (*it)->setajuste();
            }

            if((*it)->getpx2() - (*it)->getpx1() > 0)
              (*it)->setx((*it)->getx() + velTiro*(*it)->vel);
            if((*it)->getpx2() - (*it)->getpx1() < 0)
              (*it)->setx((*it)->getx() - velTiro*(*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() > 0)
              (*it)->sety((*it)->gety() + velTiro*(*it)->vel);
            if((*it)->getpy2() - (*it)->getpy1() < 0)
              (*it)->sety((*it)->gety() - velTiro*(*it)->vel);
          }
          
    }


  } else {

      bombas.erase(it++);

      //printf("bomba explodiu\n");
  }




  }

 }

}

void desenhaAviao() {

  float angulo;
  //int num_linhas;
  glColor3f(Aviao->getR(), Aviao->getG(), Aviao->getB());
  glBegin(GL_POLYGON);
  for (int i = 0; i < 1000; i++)
  {
    angulo = i * 2 * M_PI / 1000;
    glVertex2f(Aviao->getx() + (cos(angulo) * Aviao->getRaio()), Aviao->gety() + (sin(angulo) * Aviao->getRaio()));
  }
  glEnd();

}

void desenhaInimigosTerrestres()
{

  for (std::list<Circulo *>::iterator it = inimigos.begin(); it != inimigos.end(); it++)
  {
    if((*it)->getTipo() == 3) {
    float angulo;
    //int num_linhas;
    glColor3f((*it)->getR(), (*it)->getG(), (*it)->getB());
    glBegin(GL_POLYGON);
    for (int i = 0; i < 1000; i++)
    {
      angulo = i * 2 * M_PI / 1000;
      glVertex2f((*it)->getx() + (cos(angulo) * (*it)->getRaio()), (*it)->gety() + (sin(angulo) * (*it)->getRaio()));
    }
    glEnd();
        //(*it)->setx((*it)->getx() + 1);
  } 
}
  
  //glutPostRedisplay();
}

void desenhaInimigosAereos()
{

  for (std::list<Circulo *>::iterator it = inimigos.begin(); it != inimigos.end(); it++)
  {
    if((*it)->getTipo() == 2)
        (*it)->DesenhaInimigo((*it)->getx(), (*it)->gety(), (*it)->getTheta(), (*it)->getScale(),thetaHeliceInimigo,0, (*it)->getRaio(), (*it)->getR(), (*it)->getG(), (*it)->getB());
        //(*it)->setx((*it)->getx() + 1);
  } 
  
  //glutPostRedisplay();
}

float ang;
void desenhaTeste() {

      //if(keyStatus[(int)('d')] ) {
                  //Aviao->sety(Aviao->gety() + curva);
  float angulo;
             glColor3f(1, 1, 1);
            glBegin(GL_POLYGON);
        for (int i = 0; i < 1000; i++)
        {
          angulo = i * 2 * M_PI / 1000;
          glVertex2f(Aviao->getx() + (cos(angulo) * 2*Aviao->getRaio()), Aviao->gety() + (sin(angulo) * 2*Aviao->getRaio()));
        }
        glEnd();
      //}          //theta= 0;
//

}

void ClicarMouse(int button, int state, int x, int y) 
{ 
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        //thetaCanhao = m;
       // m++;
      float xc, yc, deltx, delty, fator;
      xc = Pista->getx2() - Pista->getx1();
      yc = xc + 5*thetaHelice;//* tan(thetaHelice*M_PI/180);
      //printf("%f\n", tan(-30*M_PI/180));
      deltx = abs(xc - Pista->getx1());
      delty = abs(yc - Pista->gety1());

      if(thetaHelice > 0)
            fator = (thetaHelice*3.3)/45;
      if(thetaHelice < 0)
            fator = (thetaHelice*-14)/-45;
      if(thetaHelice == 0)
            fator = 0;


      if(fimDecolagem) {
      //printf("theta:%f y1:%f x2:%f y2:%f xc:%f yc:%f theta:%f delx:%f dely:%f\n", thetaHelice, Pista->gety1(), Pista->getx2(),Pista->gety2(), xc, yc, thetaHelice, deltx, delty);
      /*
        float x1, x2, y1, y2, mid1, mid2;
      float x1a, x2a, y1a, y2a;
      float angle = 2*180/M_PI;
      float fator = 20;
      mid1 = (Pista->getx1() + Pista->getx2())/2;
      mid2 = (Pista->gety1() + Pista->gety2())/2;

      x1a = Pista->getx1() - mid1;
      y1a = Pista->gety1() - mid2;

      x2a = Pista->getx2() - mid1;
      y2a = Pista->gety2() - mid2;

      x1 = cos(fator*thetaHelice)*x1a - sin(fator*thetaHelice)*y1a;
      y1 = sin(fator*thetaHelice)*x1a + cos(fator*thetaHelice)*y1a;

      x2 = cos(fator*thetaHelice)*x2a - sin(fator*thetaHelice)*y2a;
      y2 = sin(fator*thetaHelice)*x2a + cos(fator*thetaHelice)*y2a;

      x1 += mid1;
      y1 += mid2;
      x2 += mid1;
      y2 += mid2;
      */
      bomba = new Bomba(vel, Aviao->getRaio()/12, Aviao->getx(), Aviao->gety(), 1,1,1, deltax, deltay, Pista->getx1(), Pista->getx2(), Pista->gety1(), Pista->gety2(), 1, 0);
      bombas.push_front(bomba);
      }

    } 
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP)
    {
        //momento que se solta 
        //thetaCanhao = m;
        //m--; 
      
    }
    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
     
        if(fimDecolagem) {
        bomba = new Bomba(vel, Aviao->getRaio(), Aviao->getx(), Aviao->gety(), 0,0,0, deltax, deltay, Pista->getx1(), Pista->getx2(), Pista->gety1(), Pista->gety2(), 0, 0);
        bombas.push_front(bomba);
        //printf("bomba!\n");
        }

    }
}

float xant, count = 0;
bool first = false;
void MouseAndandoNaoPressionado (int x, int y)
{
    //printf("Mouse ANDANDO solto na janela. Posição: (%d, %d)\n", x,y);
    float valor;
    valor = xant - x;
    //printf("%f\n", valor);
    valor = - valor;
    if(valor > 45)
        thetaHelice = 45;
    if(valor <-45)
        thetaHelice= -45;
    if(valor > 0 && valor < 45) {
        if(valor + thetaHelice > 45)
          thetaHelice = 45;
        else if(valor + thetaHelice < 45)
          thetaHelice += valor;
    }
    if(valor < 0 && valor > -45) {
        if(valor + thetaHelice < -45)
          thetaHelice = -45;
        else if(valor + thetaHelice > -45)
          thetaHelice +=valor;

    }                 
    xant = x;
}

int tecla =0;
void display(void)
{
    //cout << "entrou\n";
     // Clear the screen.
  
     glClear(GL_COLOR_BUFFER_BIT);
 
     PrintScore(440, 15);
     PrintScore2(440, 30);
     
     float angulo;
  //int num_linhas;
    glColor3f(Arena->getR(), Arena->getG(), Arena->getB());
    glBegin(GL_POLYGON);
        for (int i = 0; i < 1000; i++)
        {
            angulo = i * 2 * M_PI / 1000;
            glVertex2f(largura + (cos(angulo) * Arena->getRaio()), largura + (sin(angulo) * Arena->getRaio()));
        }
        glEnd();


    desenhaPista();

    desenhaInimigosTerrestres();

    desenhaBombas();

    //desenhaTeste();

    //desenhaAviao();

    //theta = tangente*180/M_PI;
        
    Aviao->Desenha(Aviao->getx(), Aviao->gety(), theta, scale,thetaCanhao,thetaHelice, Aviao->getRaio(), Aviao->getR(), Aviao->getG(), Aviao->getB());

    desenhaInimigosAereos();

    //gameOverWin(180,300);

    if(gameover && restantes !=0)
        gameOverLoose(Arena->getx()-120, Arena->gety());
    else if(gameover && restantes == 0 && !lose)
        gameOverWin(Arena->getx()-120, Arena->gety());
    
     glutSwapBuffers(); 
}


float k;
void keyPress(unsigned char key, int x, int y)
{
    switch (key) {
    
        case 'a':
        case 'A':
             //if(keyStatus[(int)('d')] != 1)
             keyStatus[(int)('a')] = 1; //Using keyStatus trick
             if(fimDecolagem)
             curvando = true;
             //printf("curvando: %d\n", curvando);
             break;
        case 'd':
        case 'D':
             //if(keyStatus[(int)('a')] != 1)
             keyStatus[(int)('d')] = 1; //Using keyStatus trick
             if(fimDecolagem)
             curvando = true;
             //printf("curvando: %d\n", curvando);
             break;
        case 'u':
        case 'U':
             robo->RodaBraco1(-1);   //Without keyStatus trick
             if(!gameover)
             startGame = true;
             break;
        case 'r':
        case 'R':
             startGame = false;
             Aviao->setx(xOriginal);
             Aviao->sety(yOriginal);   //Without keyStatus trick
             fimDecolagem = false;
             vel = aceleracaoIdeal;
             Aviao->setRaio(raioOriginal);
             scale = raioOriginal/LAMBDA2;
             jaPassou = false;
             Pista->setx1(pistax1Original);
             Pista->sety1(pistay1Original);
             Pista->setx2(pistax2Original);
             Pista->sety2(pistay2Original);
             deltax = abs(deltaxOriginal);
             deltay = abs(deltayOriginal);
             deltax2 = deltaxOriginal;
             deltay2 = deltayOriginal;
             theta = thetaOriginal;
             z=0;
             bombas.clear();
             gameover = false;
             lose = false;
             destruidas = 0;
             restantes = restanteOriginal;
             inimigos.clear();
             for (std::list<Circulo *>::iterator it = inimigosOriginal.begin(); it != inimigosOriginal.end(); it++) {

                  if((*it)->getTipo() == 2) {
                  (*it)->setx((*it)->xini);
                  (*it)->sety((*it)->yini);
                  }
                  inimigos.push_front(*it);
             }
             // retirar todas as bombas da lista de bombas
             break;
        case '+':
             vel = vel +0.5;  //Without keyStatus trick
             break;
        case '-':
             k = vel - 0.5;
             if(k < 0)
                vel = 0;
             else
                vel = vel - 0.5;   //Without keyStatus trick
             break;
        case 27 :
             exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    if(keyStatus[(int)('d')] == 0 && keyStatus[(int)('a')] == 0)
    curvando = false; 
    if(tecla == 'd')
        tecla = 1;
    if(tecla == 'a')
        tecla = 2;
    glutPostRedisplay();
}

void ResetKeyStatus()
{
    int i;
    //Initialize keyStatus
    for(i = 0; i < 256; i++)
       keyStatus[i] = 0; 
}

void init(void)
{
    ResetKeyStatus();
    // The color the windows will redraw. Its done to erase the previous frame.
    /*
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(-(ViewingWidth/2),     // X coordinate of left edge             
            (ViewingWidth/2),     // X coordinate of right edge            
            -(ViewingHeight/2),     // Y coordinate of bottom edge             
            (ViewingHeight/2),     // Y coordinate of top edge             
            -100,     // Z coordinate of the “near” plane            
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
    */
     //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
  //glLoadIdentity(); // cor de fundo
  //gluOrtho2D(0.0, 2*largura, 2*altura, 0.0);
  //glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);     // modo de projecao ortogonal
    glOrtho(0, 2 * largura, 2 * largura, 0, 1, -2);
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
      
}
float xat, yat, xants, yants, angs;
void moveInimigos() {                  

  for (std::list<Circulo *>::iterator it = inimigos.begin(); it != inimigos.end(); it++)
  {
    (*it)->quadros++;
    (*it)->tiros++;
    //printf("quadros:%d\n", (*it)->quadros);
    if((*it)->quadros >= 60 && !(*it)->rodar) {
        (*it)->rodar = true;
        (*it)->tempo = rand() % 40 + 10; 
        (*it)->direcao = rand() % 2;
        (*it)->quadros=0;
    }
    if((*it)->quadros > (*it)->tempo && (*it)->rodar) {
        (*it)->rodar = false;
        (*it)->quadros=0;
    }
    if((*it)->tiros >= (1/0.2)*60) {
      // printf("ATIRAR!\n");
      (*it)->tiros=0;
      if((*it)->getTipo() == 2) {
      bomba = new Bomba(2*velInimigo, (*it)->getRaio()/10, (*it)->getx(), (*it)->gety(), 1,0,0, (*it)->deltax, (*it)->deltay, (*it)->getxAnt(), (*it)->getx(), (*it)->getyAnt(), (*it)->gety(), 0, 1);
      bombas.push_front(bomba);
      }
    }

    if ((*it)->getTipo() == 2)
    {
        if((*it)->deltax > 0 && (*it)->deltay == 0) { // Pista reta horizontalmente

            xants = (*it)->getxAnt();
            yants = (*it)->getyAnt();
            xat = (*it)->getx();
            yat = (*it)->gety();

            alberto = sqrt(pow(Arena->getx() - (*it)->getx(), 2) + pow(Arena->gety() - (*it)->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if((*it)->getx() - (*it)->getxAnt() > 0)
                x = (*it)->getx() - jadir;
            if((*it)->getx() - (*it)->getxAnt() < 0)
                x = (*it)->getx() + jadir;

            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - (*it)->gety(), 2)) > Arena->getRaio()) {

               if((*it)->getx() - (*it)->getxAnt() > 0)
                x = x - 0.01;
              if((*it)->getx() - (*it)->getxAnt() < 0)
                x = x + 0.01;

            }
 
              
              while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - (*it)->gety(), 2)) <= Arena->getRaio()) {

              if((*it)->getx() - (*it)->getxAnt() > 0)
                x = x - 0.1;
              if((*it)->getx() - (*it)->getxAnt() < 0)
                x = x + 0.1;
              }

              (*it)->setx(x);
              //(*it)->sety(y);

            }
            if(!(*it)->rodar) {

              if(xat - xants > 0)
                (*it)->setx((*it)->getx() + velInimigo);
              if(xat - xants < 0)
                (*it)->setx((*it)->getx() - velInimigo);

           } else {

                angs = (*it)->z * 2 * M_PI / 1000;
                (*it)->setx((*it)->getx() + (cos(angs) * 1.3*velInimigo));
                (*it)->sety((*it)->gety() + (sin(angs) * 1.3*velInimigo));

                 if((*it)->direcao == 0)
                  (*it)->z=(*it)->z+2+velInimigo;
                else
                  (*it)->z=(*it)->z-2-velInimigo;
           }

  }
  if((*it)->deltay > 0 && (*it)->deltax == 0) { // Pista reta verticalmente
          //(*it)->setx((*it)->getx() + velInimigo);
          //(*it)->sety((*it)->gety() - velInimigo);

            xants = (*it)->getxAnt();
            yants = (*it)->getyAnt();
            xat = (*it)->getx();
            yat = (*it)->gety();

            alberto = sqrt(pow(Arena->getx() - (*it)->getx(), 2) + pow(Arena->gety() - (*it)->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if((*it)->gety() - (*it)->getyAnt() > 0)
              y = (*it)->gety() - jadir;
            if((*it)->gety() - (*it)->getyAnt() < 0)
              y = (*it)->gety() + jadir;

            while(sqrt(pow(Arena->getx() - (*it)->getx(), 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

              if((*it)->gety() - (*it)->getyAnt() > 0)
                y = y - 0.01;
              if((*it)->gety() - (*it)->getyAnt() < 0)
                y = y + 0.01;

            }

              
              while(sqrt(pow(Arena->getx() - (*it)->getx(), 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if((*it)->gety() - (*it)->getyAnt() > 0)
                y = y - 0.1;
              if((*it)->gety() - (*it)->getyAnt() < 0)
                y = y + 0.1;
                
              }

              //(*it)->setx(x);
              (*it)->sety(y);

            }
            if(!(*it)->rodar) {
              if(yat - yants > 0)
                (*it)->sety((*it)->gety() + velInimigo);
              if(yat - yants < 0)
                (*it)->sety((*it)->gety() - velInimigo);
            } else {

                angs = (*it)->z * 2 * M_PI / 1000;
                (*it)->setx((*it)->getx() + (cos(angs) * 1.3*velInimigo));
                (*it)->sety((*it)->gety() + (sin(angs) * 1.3*velInimigo));

                if((*it)->direcao == 0)
                  (*it)->z=(*it)->z+2+velInimigo;
                else
                  (*it)->z=(*it)->z-2-velInimigo;

            }         
    }
    if((*it)->deltax > 0 && (*it)->deltay > 0) { // Pista inclinada

         
          if((*it)->deltax > (*it)->deltay) {
            
              xants = (*it)->getxAnt();
              yants = (*it)->getyAnt();
              xat = (*it)->getx();
              yat = (*it)->gety();

            alberto = sqrt(pow(Arena->getx() - (*it)->getx(), 2) + pow(Arena->gety() - (*it)->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";
              //                  printf("jadir: %f alberto: %f\n", jadir, alberto);            

            if((*it)->getx() - (*it)->getxAnt() > 0)
                x = (*it)->getx() - jadir;
            if((*it)->getx() - (*it)->getxAnt() < 0)
                x = (*it)->getx() + jadir;
            if((*it)->gety() - (*it)->getyAnt() > 0)
              y = (*it)->gety() - jadir/((*it)->deltax/(*it)->deltay);
            if((*it)->gety() - (*it)->getyAnt() < 0)
              y = (*it)->gety() + jadir/((*it)->deltax/(*it)->deltay);

            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

              if((*it)->getx() - (*it)->getxAnt() > 0)
                x = x - 0.01;
              if((*it)->getx() - (*it)->getxAnt() < 0)
                x = x + 0.01;
              if((*it)->gety() - (*it)->getyAnt() > 0)
                y = y - 0.01/((*it)->deltax/(*it)->deltay);
              if((*it)->gety() - (*it)->getyAnt() < 0)
                y = y + 0.01/((*it)->deltax/(*it)->deltay);
            }
              
            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if((*it)->getx() - (*it)->getxAnt() > 0)
                x = x - 0.1;
              if((*it)->getx() - (*it)->getxAnt() < 0)
                x = x + 0.1;
              if((*it)->gety() - (*it)->getyAnt() > 0)
                y = y - 0.1/((*it)->deltax/(*it)->deltay);
              if((*it)->gety() - (*it)->getyAnt() < 0)
                y = y + 0.1/((*it)->deltax/(*it)->deltay);
            }
              // TELEPORTE                  
              (*it)->setx(x);
              (*it)->sety(y);

            } 
            if(!(*it)->rodar) {
              if(xat - xants > 0)
                (*it)->setx((*it)->getx() + velInimigo);
              if(xat - xants < 0)
                (*it)->setx((*it)->getx() - velInimigo);
              if(yat - yants > 0) 
                (*it)->sety((*it)->gety() + velInimigo/((*it)->deltax/(*it)->deltay));
              if(yat - yants < 0) 
                (*it)->sety((*it)->gety() - velInimigo/((*it)->deltax/(*it)->deltay));
            } else {

              

                angs = (*it)->z * 2 * M_PI / 1000;
                (*it)->setx((*it)->getx() + (cos(angs) * 1.3*velInimigo));
                (*it)->sety((*it)->gety() + (sin(angs) * 1.3*velInimigo));

                if((*it)->direcao == 0)
                  (*it)->z=(*it)->z+2+velInimigo;
                else
                  (*it)->z=(*it)->z-2-velInimigo;

            }
           
          }
          if((*it)->deltay > (*it)->deltax) {

            xants = (*it)->getxAnt();
            yants = (*it)->getyAnt();
            xat = (*it)->getx();
            yat = (*it)->gety();
            
            alberto = sqrt(pow(Arena->getx() - (*it)->getx(), 2) + pow(Arena->gety() - (*it)->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if((*it)->getx() - (*it)->getxAnt() > 0)
                x = (*it)->getx() - jadir/((*it)->deltay/(*it)->deltax);
            if((*it)->getx() - (*it)->getxAnt() < 0)
                x = (*it)->getx() + jadir/((*it)->deltay/(*it)->deltax);
            if((*it)->gety() - (*it)->getyAnt() > 0)
              y = (*it)->gety() - jadir;
            if((*it)->gety() - (*it)->getyAnt() < 0)
              y = (*it)->gety() + jadir;


            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

                if((*it)->getx() - (*it)->getxAnt() > 0)
                  x = x - 0.01/((*it)->deltay/(*it)->deltax);
                if((*it)->getx() - (*it)->getxAnt() < 0)
                  x = x + 0.01/((*it)->deltay/(*it)->deltax);
                if((*it)->gety() - (*it)->getyAnt() > 0)
                  y = y - 0.01;
                if((*it)->gety() - (*it)->getyAnt() < 0)
                  y = y + 0.01;
            }

              while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if((*it)->getx() - (*it)->getxAnt() > 0)
                x = x - 0.1/((*it)->deltay/(*it)->deltax);
              if((*it)->getx() - (*it)->getxAnt() < 0)
                x = x + 0.1/((*it)->deltay/(*it)->deltax);
              if((*it)->gety() - (*it)->getyAnt() > 0)
                y = y - 0.1;
              if((*it)->gety() - (*it)->getyAnt() < 0)
                y = y + 0.1;
                
              }

              (*it)->setx(x);
              (*it)->sety(y);

            }

            if(!(*it)->rodar) {
              if(yat - yants > 0)
                (*it)->sety((*it)->gety() + velInimigo);
              if(yat - yants < 0)
                (*it)->sety((*it)->gety() - velInimigo);
              if(xat - xants > 0) 
                (*it)->setx((*it)->getx() + velInimigo/((*it)->deltay/(*it)->deltax));
              if(xat - xants < 0) 
                (*it)->setx((*it)->getx() - velInimigo/((*it)->deltay/(*it)->deltax));
            } else {

                

                angs = (*it)->z * 2 * M_PI / 1000;
                (*it)->setx((*it)->getx() + (cos(angs) * 1.3*velInimigo));
                (*it)->sety((*it)->gety() + (sin(angs) * 1.3*velInimigo));

                if((*it)->direcao == 0)
                  (*it)->z=(*it)->z+2+velInimigo;
                else
                  (*it)->z=(*it)->z-2-velInimigo;
            }

            //cout << "esta aqui\n"
          }
          if((*it)->deltay == (*it)->deltax) {

            xants = (*it)->getxAnt();
            yants = (*it)->getyAnt();
            xat = (*it)->getx();
            yat = (*it)->gety();

            alberto = sqrt(pow(Arena->getx() - (*it)->getx(), 2) + pow(Arena->gety() - (*it)->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if((*it)->getx() - (*it)->getxAnt() > 0)
                x = (*it)->getx() - jadir;
            if((*it)->getx() - (*it)->getxAnt() < 0)
                x = (*it)->getx() + jadir;
            if((*it)->gety() - (*it)->getyAnt() > 0)
              y = (*it)->gety() - jadir;
            if((*it)->gety() - (*it)->getyAnt() < 0)
              y = (*it)->gety() + jadir;

             while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

                if((*it)->getx() - (*it)->getxAnt() > 0)
                   x = x - 0.01;
                if((*it)->getx() - (*it)->getxAnt() < 0)
                   x = x + 0.01;
                if((*it)->gety() - (*it)->getyAnt() > 0)
                  y = y - 0.01;
                if((*it)->gety() - (*it)->getyAnt() < 0)
                  y = y + 0.01;
            }

              while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if((*it)->getx() - (*it)->getxAnt() > 0)
                x = x - 0.1;
              if((*it)->getx() - (*it)->getxAnt() < 0)
                x = x + 0.1;
              if((*it)->gety() - (*it)->getyAnt() > 0)
                y = y - 0.1;
              if((*it)->gety() - (*it)->getyAnt() < 0)
                y = y + 0.1;
                
              }

              (*it)->setx(x);
              (*it)->sety(y);

            }

            if(!(*it)->rodar) {
              if(xat - xants > 0)
               (*it)->setx((*it)->getx() + velInimigo);
              if(xat - xants < 0)
               (*it)->setx((*it)->getx() - velInimigo);
              if(yat - yants > 0)
               (*it)->sety((*it)->gety() + velInimigo);
              if(yat - yants < 0)
               (*it)->sety((*it)->gety() - velInimigo);
            } else {

                angs = (*it)->z * 2 * M_PI / 1000;
                (*it)->setx((*it)->getx() + (cos(angs) * 1.3*velInimigo));
                (*it)->sety((*it)->gety() + (sin(angs) * 1.3*velInimigo));
                if((*it)->direcao == 0)
                  (*it)->z=(*it)->z+2+velInimigo;
                else
                  (*it)->z=(*it)->z-2-velInimigo;
            }

          }
          
    }   
    }
    (*it)->update();
  }

}

bool colisaoInimigos()
{

  colisao = false;
  float distancia;
  for (std::list<Circulo *>::iterator it = inimigos.begin(); it != inimigos.end(); it++)
  {
    distancia = sqrt(pow((*it)->getx() - Aviao->getx(), 2) + pow((*it)->gety() - Aviao->gety(), 2));
    if (distancia < ((*it)->getRaio() + Aviao->getRaio()) && (*it)->getTipo() == 2)
    {
      colisao = true;
      break;
    }
  }
  return colisao;
}

int quadros2=0;
void idle(int x)
{

    for (std::list<Bomba *>::iterator it = bombas.begin(); it != bombas.end(); it++) {

      if((*it)->enemy) {
           float distancia;
           distancia = sqrt(pow(Arena->getx() - (*it)->getx(), 2) + pow(Arena->gety() - (*it)->gety(), 2));
           if(distancia > Arena->getRaio() + (*it)->getRaio()) 
            bombas.erase(it++);


      }
    }

    if(!gameover) {
    thetaHeliceInimigo += 2*velInimigo/6;
    moveInimigos();
    }

    if(colisaoInimigos() && fimDecolagem) {
             startGame = false;  //Without keyStatus trick
             fimDecolagem = false;
             jaPassou = false;
             gameover = true;
    }

     if(sqrt(pow(Aviao->getx() - Pista->getx2(), 2) + pow(Aviao->gety() - Pista->gety2(), 2)) < 2*raioOriginal)
    jaPassou = true;
    
  float dist;
  //printf("curvando display: %d\n", curvando);
  if(curvando) {
     //2.098584
      float angulo;
          if(keyStatus[(int)('d')] ) {
                  //Aviao->sety(Aviao->gety() + curva);

         

            if(startGame && fimDecolagem) { 

                thetaCanhao += 2*vel/6;
                angulo = z * 2 * M_PI / 1000;
                //printf("ang:%f\n", angulo);
                //theta = atan2(deltay2, deltax2)*180/M_PI;
                //printf("%.3f\n", theta);
                Aviao->setx(Aviao->getx() + (cos(angulo) * 1.3*vel));
                Aviao->sety(Aviao->gety() + (sin(angulo) * 1.3*vel));
                z=z+2+vel;
                if(z == 1000)
                z=0;
                //theta= 0;
            }
          }
          else if(keyStatus[(int)('a')] ) {
                  //Aviao->sety(Aviao->gety() + curva);
         
              if(startGame && fimDecolagem) { 

               //float angulo;
                thetaCanhao += 2*vel/6;
                angulo = z * 2 * M_PI / 1000;
                //theta = atan2(deltay2, deltax2)*180/M_PI;
                //printf("%.3f\n", theta);
                Aviao->setx(Aviao->getx() + (cos(angulo) * 1.3*vel));
                Aviao->sety(Aviao->gety() + (sin(angulo) * 1.3*vel));
                z=z-2-vel;
                if(z == -1000)
                z=0;
              //printf("angulo:%d\n", z);
                //theta= 0;
              //printf("angulo:%f\n", angulo);
            }
          }
          if(fimDecolagem && vel!= 0) {
      if(deltax == 0) {
      Pista->setx1(Pista->getx2());
      Pista->sety1(Aviao->getyAnt());
      Pista->setx2(Aviao->getx());
      Pista->sety2(Aviao->gety());
      deltax = abs(Pista->getx2() - Pista->getx1());
      deltay = abs(Pista->gety2() - Pista->gety1());
      deltax2 = (Pista->getx2() - Pista->getx1());
      deltay2 = (Pista->gety2() - Pista->gety1());
      theta = atan2(deltay2, deltax2)*180/M_PI;
      } else if(deltay == 0) {
      Pista->setx1(Aviao->getxAnt());
      Pista->sety1(Pista->gety2());
      Pista->setx2(Aviao->getx());
      Pista->sety2(Aviao->gety());
      deltax = abs(Pista->getx2() - Pista->getx1());
      deltay = abs(Pista->gety2() - Pista->gety1());
    deltax2 = (Pista->getx2() - Pista->getx1());
      deltay2 = (Pista->gety2() - Pista->gety1());
      theta = atan2(deltay2, deltax2)*180/M_PI;
      } else {
      Pista->setx1(Aviao->getxAnt());
      Pista->sety1(Aviao->getyAnt());
      Pista->setx2(Aviao->getx());
      Pista->sety2(Aviao->gety());
      deltax = abs(Pista->getx2() - Pista->getx1());
      deltay = abs(Pista->gety2() - Pista->gety1());
      deltax2 = (Pista->getx2() - Pista->getx1());
      deltay2 = (Pista->gety2() - Pista->gety1());
      theta = atan2(deltay2, deltax2)*180/M_PI;
      //printf("theta: %f\n", theta);
    }
  }

  if(deltax > 0 && deltay == 0) { // Pista reta horizontalmente

            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if(Pista->getx2() - Pista->getx1() > 0)
                x = Aviao->getx() - jadir;
            if(Pista->getx2() - Pista->getx1() < 0)
                x = Aviao->getx() + jadir;

            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - Aviao->gety(), 2)) > Arena->getRaio()) {

               if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.01;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.01;

            }
 
              
              while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - Aviao->gety(), 2)) <= Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.1;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.1;
              }

              Aviao->setx(x);
              //Aviao->sety(y);

      }
  }
  if(deltay > 0 && deltax == 0) { // Pista reta verticalmente
          //Aviao->setx(Aviao->getx() + vel);
          //Aviao->sety(Aviao->gety() - vel);

            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if(Pista->gety2() - Pista->gety1() > 0)
              y = Aviao->gety() - jadir;
            if(Pista->gety2() - Pista->gety1() < 0)
              y = Aviao->gety() + jadir;

            while(sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.01;
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.01;

            }

              
              while(sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.1;
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.1;
                
              }

              //Aviao->setx(x);
              Aviao->sety(y);

            }
    }
    if(deltax > 0 && deltay > 0) { // Pista inclinada

          if(deltax > deltay) {
            
            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";
              //                  printf("jadir: %f alberto: %f\n", jadir, alberto);            

            if(Pista->getx2() - Pista->getx1() > 0)
                x = Aviao->getx() - jadir;
            if(Pista->getx2() - Pista->getx1() < 0)
                x = Aviao->getx() + jadir;
            if(Pista->gety2() - Pista->gety1() > 0)
              y = Aviao->gety() - jadir/(deltax/deltay);
            if(Pista->gety2() - Pista->gety1() < 0)
              y = Aviao->gety() + jadir/(deltax/deltay);

            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.01;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.01;
              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.01/(deltax/deltay);
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.01/(deltax/deltay);

                

            }
              
            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.1;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.1;
              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.1/(deltax/deltay);
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.1/(deltax/deltay);

               //printf("2\n");
                
                //printf("PASSOU AQUI\n");
            }

              Aviao->setx(x);
              Aviao->sety(y);

            }


          }
          if(deltay > deltax) {
            
            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if(Pista->getx2() - Pista->getx1() > 0)
                x = Aviao->getx() - jadir/(deltay/deltax);
            if(Pista->getx2() - Pista->getx1() < 0)
                x = Aviao->getx() + jadir/(deltay/deltax);
            if(Pista->gety2() - Pista->gety1() > 0)
              y = Aviao->gety() - jadir;
            if(Pista->gety2() - Pista->gety1() < 0)
              y = Aviao->gety() + jadir;


            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

                if(Pista->getx2() - Pista->getx1() > 0)
                  x = x - 0.01/(deltay/deltax);
                if(Pista->getx2() - Pista->getx1() < 0)
                  x = x + 0.01/(deltay/deltax);
                if(Pista->gety2() - Pista->gety1() > 0)
                  y = y - 0.01;
                if(Pista->gety2() - Pista->gety1() < 0)
                  y = y + 0.01;
            }

              while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.1/(deltay/deltax);
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.1/(deltay/deltax);
              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.1;
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.1;
                
              }

              Aviao->setx(x);
              Aviao->sety(y);

            }

            //cout << "esta aqui\n"
          }
          if(deltay == deltax) {

            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if(Pista->getx2() - Pista->getx1() > 0)
                x = Aviao->getx() - jadir;
            if(Pista->getx2() - Pista->getx1() < 0)
                x = Aviao->getx() + jadir;
            if(Pista->gety2() - Pista->gety1() > 0)
              y = Aviao->gety() - jadir;
            if(Pista->gety2() - Pista->gety1() < 0)
              y = Aviao->gety() + jadir;

             while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

                if(Pista->getx2() - Pista->getx1() > 0)
                   x = x - 0.01;
                if(Pista->getx2() - Pista->getx1() < 0)
                   x = x + 0.01;
                if(Pista->gety2() - Pista->gety1() > 0)
                  y = y - 0.01;
                if(Pista->gety2() - Pista->gety1() < 0)
                  y = y + 0.01;
            }

              while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.1;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.1;
              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.1;
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.1;
                
              }

              Aviao->setx(x);
              Aviao->sety(y);

            }

          }
          
    }

      
  }  else {
  if (startGame)
  {
    if(dist = sqrt(pow(Aviao->getx() - Pista->getx2(), 2) + pow(Aviao->gety() - Pista->gety2(), 2)) <= tamPista/2 + raioOriginal) {

      if(Aviao->getRaio() < 2*raioOriginal) {

        if(tamPista > 200) {   
          Aviao->setRaio(Aviao->getRaio() + 0.15 * (raioOriginal/10)); 
          scale = Aviao->getRaio()/LAMBDA2;
        }
        if(tamPista <= 200 && tamPista > 100) {
          Aviao->setRaio(Aviao->getRaio() + 0.13* (raioOriginal/10) );
          scale = Aviao->getRaio()/LAMBDA2;
        }
       if(tamPista <= 100 && tamPista > 50) {
          Aviao->setRaio(Aviao->getRaio() + 0.1 * (raioOriginal/10) );
          scale = Aviao->getRaio()/LAMBDA2;
        }
        if(tamPista <= 50) {
          Aviao->setRaio(Aviao->getRaio() + 0.072 * (raioOriginal/10));
          scale = Aviao->getRaio()/LAMBDA2;
        }
      }
    }

    if(deltax > 0 && deltay == 0) { // Pista reta horizontalmente

            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if(Pista->getx2() - Pista->getx1() > 0)
                x = Aviao->getx() - jadir;
            if(Pista->getx2() - Pista->getx1() < 0)
                x = Aviao->getx() + jadir;

            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - Aviao->gety(), 2)) > Arena->getRaio()) {

               if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.01;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.01;

            }
 
              
              while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - Aviao->gety(), 2)) <= Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.1;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.1;
              }

              Aviao->setx(x);
              //Aviao->sety(y);

            }

          if(Pista->getx2() - Pista->getx1() > 0)
            Aviao->setx(Aviao->getx() + vel);
          if(Pista->getx2() - Pista->getx1() < 0)
            Aviao->setx(Aviao->getx() - vel);
          //Aviao->sety(Aviao->gety() - vel/2);
    }

    if(deltay > 0 && deltax == 0) { // Pista reta verticalmente
          //Aviao->setx(Aviao->getx() + vel);
          //Aviao->sety(Aviao->gety() - vel);

            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if(Pista->gety2() - Pista->gety1() > 0)
              y = Aviao->gety() - jadir;
            if(Pista->gety2() - Pista->gety1() < 0)
              y = Aviao->gety() + jadir;

            while(sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.01;
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.01;

            }

              
              while(sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.1;
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.1;
                
              }

              //Aviao->setx(x);
              Aviao->sety(y);

            }

          if(Pista->gety2() - Pista->gety1() > 0)
            Aviao->sety(Aviao->gety() + vel);
          if(Pista->gety2() - Pista->gety1() < 0)
            Aviao->sety(Aviao->gety() - vel);                 
    }

    if(deltax > 0 && deltay > 0) { // Pista inclinada

          if(deltax > deltay) {
            
            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";
              //                  printf("jadir: %f alberto: %f\n", jadir, alberto);            

            if(Pista->getx2() - Pista->getx1() > 0)
                x = Aviao->getx() - jadir;
            if(Pista->getx2() - Pista->getx1() < 0)
                x = Aviao->getx() + jadir;
            if(Pista->gety2() - Pista->gety1() > 0)
              y = Aviao->gety() - jadir/(deltax/deltay);
            if(Pista->gety2() - Pista->gety1() < 0)
              y = Aviao->gety() + jadir/(deltax/deltay);

            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.01;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.01;
              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.01/(deltax/deltay);
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.01/(deltax/deltay);

                

            }
              
            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.1;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.1;
              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.1/(deltax/deltay);
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.1/(deltax/deltay);

               //printf("2\n");
                
                //printf("PASSOU AQUI\n");
            }
             //printf("2\n");

              Aviao->setx(x);
              Aviao->sety(y);

            }

            // << "esta aqui\n";

            if(Pista->getx2() - Pista->getx1() > 0)
              Aviao->setx(Aviao->getx() + vel);
            if(Pista->getx2() - Pista->getx1() < 0)
              Aviao->setx(Aviao->getx() - vel);
            if(Pista->gety2() - Pista->gety1() > 0) 
               Aviao->sety(Aviao->gety() + vel/(deltax/deltay));
            if(Pista->gety2() - Pista->gety1() < 0) 
              Aviao->sety(Aviao->gety() - vel/(deltax/deltay));


          }
          if(deltay > deltax) {
            
            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if(Pista->getx2() - Pista->getx1() > 0)
                x = Aviao->getx() - jadir/(deltay/deltax);
            if(Pista->getx2() - Pista->getx1() < 0)
                x = Aviao->getx() + jadir/(deltay/deltax);
            if(Pista->gety2() - Pista->gety1() > 0)
              y = Aviao->gety() - jadir;
            if(Pista->gety2() - Pista->gety1() < 0)
              y = Aviao->gety() + jadir;


            while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

                if(Pista->getx2() - Pista->getx1() > 0)
                  x = x - 0.01/(deltay/deltax);
                if(Pista->getx2() - Pista->getx1() < 0)
                  x = x + 0.01/(deltay/deltax);
                if(Pista->gety2() - Pista->gety1() > 0)
                  y = y - 0.01;
                if(Pista->gety2() - Pista->gety1() < 0)
                  y = y + 0.01;
            }

              while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.1/(deltay/deltax);
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.1/(deltay/deltax);
              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.1;
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.1;
                
              }

              Aviao->setx(x);
              Aviao->sety(y);

            }

            //cout << "esta aqui\n";

            if(Pista->gety2() - Pista->gety1() > 0)
              Aviao->sety(Aviao->gety() + vel);
            if(Pista->gety2() - Pista->gety1() < 0)
              Aviao->sety(Aviao->gety() - vel);
            if(Pista->getx2() - Pista->getx1() > 0) 
               Aviao->setx(Aviao->getx() + vel/(deltay/deltax));
            if(Pista->getx2() - Pista->getx1() < 0) 
              Aviao->setx(Aviao->getx() - vel/(deltay/deltax));
            

          }
          if(deltay == deltax) {

            alberto = sqrt(pow(Arena->getx() - Aviao->getx(), 2) + pow(Arena->gety() - Aviao->gety(), 2));
            if(alberto > Arena->getRaio() ) {
              
              float x, y;
              jadir = alberto - Arena->getRaio();
              //cout << "arena: " << Arena->getRaio() << " ";
              //cout << "alberto" << alberto << " ";
              //cout << "jadir" << jadir << " ";

            if(Pista->getx2() - Pista->getx1() > 0)
                x = Aviao->getx() - jadir;
            if(Pista->getx2() - Pista->getx1() < 0)
                x = Aviao->getx() + jadir;
            if(Pista->gety2() - Pista->gety1() > 0)
              y = Aviao->gety() - jadir;
            if(Pista->gety2() - Pista->gety1() < 0)
              y = Aviao->gety() + jadir;

             while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) > Arena->getRaio()) {

                if(Pista->getx2() - Pista->getx1() > 0)
                   x = x - 0.01;
                if(Pista->getx2() - Pista->getx1() < 0)
                   x = x + 0.01;
                if(Pista->gety2() - Pista->gety1() > 0)
                  y = y - 0.01;
                if(Pista->gety2() - Pista->gety1() < 0)
                  y = y + 0.01;
            }

              while(sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2)) <= Arena->getRaio()) {

              if(Pista->getx2() - Pista->getx1() > 0)
                x = x - 0.1;
              if(Pista->getx2() - Pista->getx1() < 0)
                x = x + 0.1;
              if(Pista->gety2() - Pista->gety1() > 0)
                y = y - 0.1;
              if(Pista->gety2() - Pista->gety1() < 0)
                y = y + 0.1;
                
              }

              Aviao->setx(x);
              Aviao->sety(y);

            }

            if(Pista->getx2() - Pista->getx1() > 0)
              Aviao->setx(Aviao->getx() + vel);
            if(Pista->getx2() - Pista->getx1() < 0)
              Aviao->setx(Aviao->getx() - vel);
            if(Pista->gety2() - Pista->gety1() > 0)
              Aviao->sety(Aviao->gety() + vel);
            if(Pista->gety2() - Pista->gety1() < 0)
              Aviao->sety(Aviao->gety() - vel);

          }
          
    }

    if(!fimDecolagem) {
    vel = vel + aceleracaoIdeal;
    thetaCanhao += 2*vel/6;
    quadros2++;
    } else {
      thetaCanhao += 2*vel/6;
    }

     
     if (jaPassou && sqrt(pow(Pista->getx2() - Aviao->getx(), 2) + pow(Pista->gety2() - Aviao->gety(), 2)) >= 2*raioOriginal) {
      //startGame = false;
      //cout<< Aviao->getRaio();
      Aviao->setRaio(2*raioOriginal);
      scale = Aviao->getRaio()/LAMBDA2;
      vel = vel * velocidade;
      fimDecolagem = true;
      //printf("vel:%f quadros: %d\n", vel, quadros2);
      //cout << tamPista;
    }
    
  }
  
  } // chave do curvando


    if(fimDecolagem && vel != 0) {
      if(deltax == 0) {
      Pista->setx1(Pista->getx2());
      Pista->sety1(Aviao->getyAnt());
      Pista->setx2(Aviao->getx());
      Pista->sety2(Aviao->gety());
      deltax = abs(Pista->getx2() - Pista->getx1());
      deltay = abs(Pista->gety2() - Pista->gety1());
      deltax2 = (Pista->getx2() - Pista->getx1());
      deltay2 = (Pista->gety2() - Pista->gety1());
      theta = atan2(deltay2, deltax2)*180/M_PI;
      } else if(deltay == 0) {
      Pista->setx1(Aviao->getxAnt());
      Pista->sety1(Pista->gety2());
      Pista->setx2(Aviao->getx());
      Pista->sety2(Aviao->gety());
      deltax = abs(Pista->getx2() - Pista->getx1());
      deltay = abs(Pista->gety2() - Pista->gety1());
    deltax2 = (Pista->getx2() - Pista->getx1());
      deltay2 = (Pista->gety2() - Pista->gety1());
      theta = atan2(deltay2, deltax2)*180/M_PI;
      } else {
      Pista->setx1(Aviao->getxAnt());
      Pista->sety1(Aviao->getyAnt());
      Pista->setx2(Aviao->getx());
      Pista->sety2(Aviao->gety());
      deltax = abs(Pista->getx2() - Pista->getx1());
      deltay = abs(Pista->gety2() - Pista->gety1());
      deltax2 = (Pista->getx2() - Pista->getx1());
      deltay2 = (Pista->gety2() - Pista->gety1());
      theta = atan2(deltay2, deltax2)*180/M_PI;
    }
}

    
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, idle, 0);
}
 
int main(int argc, char *argv[])
{

  srand (time(NULL));
    
    if(argc != 2) {
  printf("[USO]: ./trabalhocg <argumento1>\n");
  exit(0);
  }

  // leitura do XML
  //char *dir;
  //dir = get_current_dir_name();
  //char *argumento;
  //strcpy(argumento, dir);
  //std::string filename = argv[1];
  //strcat(dir, argv[1]);
  //strcat(dir, "config.xml");
  //cout << argumento;
  //cout << argv[1];

  char cwd[512];
  strcat(cwd, argv[1]);
  strcat(cwd, "config.xml");
  //cout << cwd;

  TiXmlDocument doc(cwd);

  if(!doc.LoadFile()) {
    cout << "Nao foi possivel localizar o arquivo config.xml\n";
    exit(0);
  }

  TiXmlHandle docHandle(&doc);
  TiXmlElement *leitura = docHandle.FirstChild("aplicacao").FirstChild("arquivoDaArena").FirstChild("nome").ToElement();

  nome = leitura->GetText();

  leitura = docHandle.FirstChild("aplicacao").FirstChild("arquivoDaArena").FirstChild("tipo").ToElement();

  tipo = leitura->GetText();

  leitura = docHandle.FirstChild("aplicacao").FirstChild("arquivoDaArena").FirstChild("caminho").ToElement();

  caminho = leitura->GetText();

  leitura = docHandle.FirstChild("aplicacao").FirstChild("jogador").ToElement();

  velocidade = atof(leitura->Attribute("vel"));
  velTiro = atof(leitura->Attribute("velTiro"));

  // fim da leitura do primeiro XML
  char *nomeSVG = strdup(nome);
  char *tipoSVG = strdup(tipo);
  strcat(nomeSVG, ".");
  strcat(nomeSVG, tipoSVG);
  strcat((char*)caminho, nomeSVG);
  //cout << caminho;
  TiXmlDocument doc2(caminho);
   if(!doc2.LoadFile()) {
    cout << "Nao foi possivel localizar o arquivo arena.svg\n";
    exit(0);
  }
  TiXmlHandle docHandle2(&doc2);

  TiXmlElement *leitura2 = docHandle2.FirstChild("svg").Child("circle", 0).ToElement();

  float wraio, wx, wy, wg, wb, wtipo;
  const char* fill;
  while(leitura2) {

    fill = leitura2->Attribute("fill");

    if (strcmp(fill, "blue") == 0) {
    	largura = atof(leitura2->Attribute("r"));
  		altura = atof(leitura2->Attribute("r"));
  		wx = atof(leitura2->Attribute("cx"));
      wy = atof(leitura2->Attribute("cy"));
      //MUDAR SINAL AQUI!!9
  		deslocamentox = abs(wx - largura);
      deslocamentoy = abs(wy - largura);

  		//printf("%f\n", deslocamento);
		Arena = new Circulo(largura, largura, altura, 0, 0, 254, 0);
    }
    leitura2 = leitura2->NextSiblingElement("circle");
  }

    //cout << deslocamento << "\n";
  // garantir o deslocamento

  leitura2 = docHandle2.FirstChild("svg").Child("circle", 0).ToElement();

  while(leitura2) {

    fill = leitura2->Attribute("fill");

    if (strcmp(fill, "green") == 0) {
    	wraio = atof(leitura2->Attribute("r"));
  		wx = atof(leitura2->Attribute("cx"));
  		wy = atof(leitura2->Attribute("cy"));
      raioOriginal = wraio;
      scale = raioOriginal/LAMBDA2;
  		//deslocamento = wx - largura;
  		//printf("%f\n", deslocamento);
		Aviao = new Circulo(wraio, wx-deslocamentox, wy-deslocamentoy, 0, 0.8, 0, 1);
    }

    if (strcmp(fill, "red") == 0) {
    	wraio = atof(leitura2->Attribute("r"));
  		wx = atof(leitura2->Attribute("cx"));
  		wy = atof(leitura2->Attribute("cy"));
  		//deslocamento = wx - largura;
  		//printf("%f\n", deslocamento);
      raioVoador = wraio;
		circ = new Circulo(wraio, wx-deslocamentox, wy-deslocamentoy, 1, 0, 0, 2);
    circ->setScale(wraio/LAMBDA2);
		inimigos.push_front(circ);
    inimigosOriginal.push_front(circ);
    }

    if (strcmp(fill, "orange") == 0) {
    	wraio = atof(leitura2->Attribute("r"));
  		wx = atof(leitura2->Attribute("cx"));
  		wy = atof(leitura2->Attribute("cy"));
  		//deslocamento = wx - largura;
  		//printf("%f\n", deslocamento);
		circ = new Circulo(wraio, wx-deslocamentox, wy-deslocamentoy, 1, 0.65, 0, 3);
		inimigos.push_front(circ);
    inimigosOriginal.push_front(circ);
    restantes++;
    }

    leitura2 = leitura2->NextSiblingElement("circle");
  }

  // INIMIGOS TEREM IDENTIDADE DE ROBO

  

  // PARA FAZER LEITURA DO RETANGULO

  float wx1, wx2, wy1, wy2;

  leitura2 = docHandle2.FirstChild("svg").Child("line", 0).ToElement();

   wx1 = atof(leitura2->Attribute("x1"));
   wy1 = atof(leitura2->Attribute("y1"));
   wx2 = atof(leitura2->Attribute("x2"));
   wy2 = atof(leitura2->Attribute("y2"));


   // para tratar o angulo
   deltax2 = (wx2 - wx1);
   deltay2 = (wy2 - wy1);

   deltaxOriginal = deltax2;
   deltayOriginal = deltay2;

   deltax = abs(wx2 - wx1);
   deltay = abs(wy2 - wy1);

   tangente = atan2(deltay2, deltax2);
   thetaOriginal = tangente*180/M_PI;
   theta = thetaOriginal;
   z=-100;
   //z = (thetaOriginal*1000);
   printf("%f\n", theta);

   Pista = new Retangulo(wx1-deslocamentox,wx2-deslocamentox,wy1-deslocamentoy, wy2-deslocamentoy);

   Pista2 = new Retangulo(wx1-deslocamentox,wx2-deslocamentox,wy1-deslocamentoy, wy2-deslocamentoy);

  //cout << Pista->getx2();

   tamPista = sqrt(pow(wx1 - wx2, 2) + pow(wy1 - wy2, 2));
   distLimite = ( Arena->getRaio() - Aviao->getRaio() ) ;

   velocidadeIdeal = (tamPista+raioOriginal)/LAMBDA;
   aceleracaoIdeal = ( pow(velocidadeIdeal, 2) / (2*(tamPista+raioOriginal)) );

   vel = aceleracaoIdeal;

   printf("velideal:%f  aceleracaoIdeal:%f\n", velocidadeIdeal, aceleracaoIdeal);

   velInimigo = velocidadeIdeal;

   //scaleInimigo = 20/LAMBDA2;

   //printf("velideal: %f aceleracaoIdeal:%f\n", velocidadeIdeal, aceleracaoIdeal);
   
   robo = new Robo(Aviao->getRaio(), Aviao->getx(), Aviao->gety(), Aviao->getR(), Aviao->getG(), Aviao->getB());

   xOriginal = Aviao->getx();
   yOriginal = Aviao->gety();
   pistax1Original = Pista->getx1();
   pistax2Original = Pista->getx2();
   pistay1Original= Pista->gety1();
   pistay2Original = Pista->gety2();

   restanteOriginal = restantes;
   
   glutInit(&argc, argv);                       // inicializa o glut
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // especifica o uso de cores e buffers
   glutInitWindowSize(2 * largura, 2 * altura); // especifica as dimensoes da janela
   glutInitWindowPosition(100, 100);            // especifica aonde a janela aparece na tela
   glutCreateWindow("Trabalho 4 - CG");                    // cria a janela
   init();
  
   glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

   glutDisplayFunc(display);

   glutMouseFunc(ClicarMouse); 
   glutPassiveMotionFunc(MouseAndandoNaoPressionado);

   glutKeyboardFunc(keyPress);
   glutKeyboardUpFunc(keyup);

  

   glutTimerFunc(1000 / FPS, idle, 0); // funcao que sera redesenhada pelo GLUT
   glutMainLoop();
  
    //glutDisplayFunc(renderScene);
    //glutKeyboardFunc(keyPress);
    //glutIdleFunc(idle);
    //glutKeyboardUpFunc(keyup);
 
 
    return 0;
}

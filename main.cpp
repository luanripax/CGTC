#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <ctime>
#include <list>
#include "tinyxml.h"
#include "circ.h"
#define PI 3.14159265359
#define FPS 60
using namespace std;

int estado;
int botao;
// prototipos das funcoes
float delta;
float delta2;

//config do circulo desenhado
float raio;
float corR;
float corG;
float corB;

//config do circulo modelo
float corModelR;
float corModelG;
float corModelB;
float corSobreR;
float corSobreG;
float corSobreB;

//config do fundo
float largura;
float altura;

float corFundoR;
float corFundoG;
float corFundoB;

float Mousex;
float Mousey;

int ax, ay;

bool w = false;
bool a = false;
bool s = false;
bool d = false;

bool desenhar = false;
bool click = false;
bool colisao = false;
bool arrastando = false;

float distanciaArrasto;

long int inicial = time(NULL);
long int final, quadros = 0;

// titulo
//std::string titulo;
const char *titulo;

Circulo *circ;
Circulo *circMouse;
Circulo *arrastado;

Circulo *Arena;
Circulo *Aviao;

// 0 - Arena 1 - Aviao 2 - Inimigo Aereo 3 - Inimigo terrestre

//lista de circulos
std::list<Circulo *> circulos;

float raioAviao = 10;
float deslocx = 0;
bool startGame = false;
bool primeiroDesenho = false;
float first = 0;
float distanciaDecolar = 200;

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);

bool detectaColisao(float x, float y)
{

  colisao = false;
  float distancia;
  for (std::list<Circulo *>::iterator it = circulos.begin(); it != circulos.end(); it++)
  {
    distancia += sqrt(pow((*it)->getx() - x, 2) + pow((*it)->gety() - y, 2));
    if (distancia < 2 * raio)
    {
      circMouse->setR(corSobreR);
      circMouse->setG(corSobreG);
      circMouse->setB(corSobreB);
      colisao = true;
    }
    distancia = 0;
  }
  if (colisao == false)
  {
    circMouse->setR(corModelR);
    circMouse->setG(corModelG);
    circMouse->setB(corModelB);
  }
  if (colisao)
    return true;
  else
    return false;
}

bool teste;
void ClicarMouse(int button, int state, int x, int y)
{
  Mousex = x;
  Mousey = (altura - y);

  teste = detectaColisao(Mousex, Mousey);
  estado = state;
  botao = button;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    teste = detectaColisao(Mousex, Mousey);
    if (!teste)
    {
      //circ = new Circulo(x, Mousey, corR, corG, corB);
      circulos.push_front(circ);
      click = true;
    }
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
  {
    //momento que se solta
    arrastando = false;
    glutPostRedisplay();
  }
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    float distancia;
    for (std::list<Circulo *>::iterator it = circulos.begin(); it != circulos.end(); it++)
    {
      distancia += sqrt(pow((*it)->getx() - x, 2) + pow((*it)->gety() - Mousey, 2));
      if (distancia <= raio)
      {
        //cout << "ta em um circulo\n";
        arrastando = true;
        arrastado = *it;
        //distanciaArrasto = distancia;
        //ax = Mousex;
        //ay = Mousey;
      }
      distancia = 0;
    }
  }
}

void desenhaCirculoModelo(GLint x, GLint y, GLint raio, int num_linhas)
{

  float angulo;
  //int num_linhas;
  glColor3f(circMouse->getR(), circMouse->getG(), circMouse->getB());
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < num_linhas; i++)
  {
    angulo = i * 2 * M_PI / num_linhas;
    if (desenhar)
      glVertex2f(x + (cos(angulo) * raio), y + (sin(angulo) * raio));
  }

  glEnd();
  glutPostRedisplay();
}

void desenhaCirculosTela()
{

  for (std::list<Circulo *>::iterator it = circulos.begin(); it != circulos.end(); it++)
  {

    float angulo;
    //int num_linhas;
    glColor3f((*it)->getR(), (*it)->getG(), (*it)->getB());
    glBegin(GL_POLYGON);
    for (int i = 0; i < 1000; i++)
    {
      angulo = i * 2 * M_PI / 1000;
      glVertex2f((*it)->getx() + (cos(angulo) * raio), (*it)->gety() + (sin(angulo) * raio));
    }

    glEnd();
  }
  //glutPostRedisplay();
}

void MouseAndandoSolto(int x, int y)
{

  //drawHollowCircle(x,y,raio);
  //Mousex = x;
  // Mousey = (altura - y);
  //detectaColisao(x, Mousey);
  //desenhar = true;
  //printf("Mouse ANDANDO solto na janela. Posição: (%d, %d)\n", x,y);
}

void MouseAndandoClicado(int x, int y)
{
  Mousex = x;
  Mousey = (altura - y);
  // SEMPRE ESTA EM GLUT DOWN ENQUANTO SE MOVE
  if (arrastando)
  {
    //printf("Mouse DIREITO ANDANDO pressionado na janela. ESTADO: %d Posição: (%d, %d)\n",estado, x,y);
    arrastado->setx(x);
    arrastado->sety(Mousey);
  }
  //if(botao == GLUT_LEFT_BUTTON)
  //printf("Mouse  ESQUERDO ANDANDO Pressionadoado na janela. Posição: (%d, %d)\n", x,y);
}

float dx, dy;
void GerenciaTeclado(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'w':
    //dy = dy + 3.0;
    w = true;
    break;
  case 'a':
    //dx = dx - 3.0;
    a = true;
    break;
  case 's':
    //dy = dy - 3.0;
    s = true;
    break;
  case 'd':
    //dx = dx + 3.0;
    d = true;
    break;
  }
  //glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'w':
    //dy = dy + 3.0;
    w = false;
    break;
  case 'u':
    //dy = dy + 3.0;
    startGame = true;
    break;
  case 'a':
    //dx = dx - 3.0;
    a = false;
    break;
  case 's':
    //dy = dy - 3.0;
    s = false;
    break;
  case 'd':
    //dx = dx + 3.0;
    d = false;
    break;
  }
  //glutPostRedisplay();
}

void idle(int x)
{
  if (!startGame)
  {
    if (w == true)
      dy = dy + 0.1;
    if (a == true)
      dx = dx - 0.1;
    if (s == true)
      dy = dy - 0.1;
    if (d == true)
      dx = dx + 0.1;
  }
  glutPostRedisplay();
  primeiroDesenho = true;
  glutTimerFunc(1000 / FPS, idle, 0);
  //usleep(1000);
}

const char *nome;
const char *tipo;
const char *caminho;
float velocidade;

float cx, cy;

// funcao principal
int main(int argc, char **argv)
{

  //if(argc != 2) {
  //printf("[USO]: ./trabalhocg <argumento1>\n");
  //exit(0);
  //}

  // leitura do XML
  TiXmlDocument doc(argv[1]);

  doc.LoadFile();
  TiXmlHandle docHandle(&doc);
  TiXmlElement *leitura = docHandle.FirstChild("aplicacao").FirstChild("arquivoDaArena").FirstChild("nome").ToElement();

  nome = leitura->GetText();

  leitura = docHandle.FirstChild("aplicacao").FirstChild("arquivoDaArena").FirstChild("tipo").ToElement();

  tipo = leitura->GetText();

  leitura = docHandle.FirstChild("aplicacao").FirstChild("arquivoDaArena").FirstChild("caminho").ToElement();

  caminho = leitura->GetText();

  leitura = docHandle.FirstChild("aplicacao").FirstChild("jogador").ToElement();

  velocidade = atof(leitura->Attribute("vel"));
  // fim da leitura do primeiro XML
  char *nomeSVG = strdup(nome);
  char *tipoSVG = strdup(tipo);
  strcat(nomeSVG, ".");
  strcat(nomeSVG, tipoSVG);
  TiXmlDocument doc2(nomeSVG);
  //cout << nomeSVG;
  doc2.LoadFile();
  TiXmlHandle docHandle2(&doc2);

  TiXmlElement *leitura2 = docHandle2.FirstChild("svg").Child("circle", 0).ToElement();

  float wraio, wx, wy, wr, wg, wb, wtipo;
  while(leitura2) {

    wx = atof(leitura2->Attribute("cx"));
    wy = atof(leitura2->Attribute("cy"));
    wraio = atof(leitura2->Attribute("r"));

    cout << wx <<" "<<  wy << " "<< wraio << endl;
    
    leitura2 = leitura2->NextSiblingElement("circle");
  }

  //caminho = leitura2->Attribute("fill");

  //largura = atof(leitura2->Attribute("r"));
  //altura = atof(leitura2->Attribute("r"));

  //leitura2 = docHandle2.FirstChild("svg").Child("circle", 1).ToElement();

  //cx = atof(leitura2->Attribute("cx"));
  //cy = atof(leitura2->Attribute("cy"));

  Arena = new Circulo(10, 20, Mousey, corR, corG, corB, 0);

  Aviao = new Circulo(10, 20, Mousey, corR, corG, corB, 0);

  //cout << cx;

  //inicialização do programa
  //circMouse = new Circulo(0,0, corModelR, corModelG, corModelB); // instancia circulo do mouse

  //glutInit(&argc, argv);                       // inicializa o glut
  //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // especifica o uso de cores e buffers
  //glutInitWindowSize(2 * largura, 2 * altura); // especifica as dimensoes da janela
  //glutInitWindowPosition(100, 100);            // especifica aonde a janela aparece na tela
  //glutCreateWindow(titulo);                    // cria a janela
  //init();

  //glutPassiveMotionFunc(MouseAndandoSolto);
  //glutMotionFunc(MouseAndandoClicado);
  //glutMouseFunc(ClicarMouse);

  //glutDisplayFunc(display);
  //glutKeyboardFunc(GerenciaTeclado);
  //glutKeyboardUpFunc(keyup);
  //glutTimerFunc(1000 / FPS, idle, 0); // funcao que sera redesenhada pelo GLUT
  //glutMainLoop();
  //} else {
  // cout << "[ERRO]: Não foi encontrado o arquivo config.xml\n";
  // exit(0);
  // }

  return 0;
}

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); // cor de fundo
  //glMatrixMode(GL_PROJECTION);
  //gluOrtho2D(0.0, largura, altura, 0.0);
  //glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);     // modo de projecao ortogonal
  glOrtho(0.0, 2 * largura, 0.0, 2 * altura, -2.0, 1.0);
}

void display(void)
{
  if (startGame)
  {
    raioAviao += 0.05;
    deslocx += 0.8;
    if (deslocx >= 150)
      startGame = false;
  }
  glClear(GL_COLOR_BUFFER_BIT);

  float angulo;
  //int num_linhas;
  glColor3f(0, 0, 254);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 1000; i++)
  {
    angulo = i * 2 * M_PI / 1000;
    glVertex2f(largura + (cos(angulo) * largura), largura + (sin(angulo) * largura));
  }
  glEnd();

  glColor3f(11.0, 130.0, 30.0);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 1000; i++)
  {
    angulo = i * 2 * M_PI / 1000;
    glVertex2f((largura + deslocx) + (cos(angulo) * raioAviao), largura + (sin(angulo) * raioAviao));
  }
  glEnd();

  glColor3f(0, 15, 0);
  glBegin(GL_POLYGON);
  for (int i = 0; i < 1000; i++)
  {
    angulo = i * 2 * M_PI / 1000;
    glVertex2f(largura + (cos(angulo) * 20), largura + (sin(angulo) * 20));
  }
  glEnd();

  quadros++;
  final = time(NULL);
  if (final - inicial > 0)
  {
    cout << "Fps: " << quadros / (final - inicial) << endl;
    quadros = 0;
    inicial = final;
  }

  //while(!startGame);

  //glutPostRedisplay();
  //if(click == true)
  //desenhaCirculosTela();

  //desenhaCirculoModelo(Mousex, Mousey, raio, 4000);
  glFlush();
}
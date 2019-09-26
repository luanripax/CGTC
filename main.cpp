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
#include "rec.h"
#define PI 3.14159265359
#define FPS 60
#define LAMBDA 111.11
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
float vel;
bool fimDecolagem = false;

// titulo
//std::string titulo;
const char *titulo;

Circulo *circ;
Circulo *circMouse;
Circulo *arrastado;

Circulo *Arena;
Circulo *Aviao;
Retangulo *Pista;

float deslocamento = 0;

// 0 - Arena 1 - Aviao 2 - Inimigo Aereo 3 - Inimigo terrestre

//lista de circulos
std::list<Circulo *> circulos;
std::list<Circulo *> inimigos;

float raioAviao = 10;
float deslocx = 0;
bool startGame = false;
bool primeiroDesenho = false;
float first = 0;
float distanciaDecolar = 200;
float tamPista;
float distLimite;

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);

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
    if(!fimDecolagem)
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

float distAux;

bool colisaoInimigos(float xFuturo, float yFuturo, float xAtual, float yAtual)
{

  colisao = false;
  float distancia;
  for (std::list<Circulo *>::iterator it = inimigos.begin(); it != inimigos.end(); it++)
  {
    distancia += sqrt(pow((*it)->getx() - xFuturo, 2) + pow((*it)->gety() - yFuturo, 2));
    if (distancia < (2 * (*it)->getRaio()) && (*it)->getTipo() == 2)
    {
      distAux = sqrt(pow((*it)->getx() - xAtual, 2) + pow((*it)->gety() - yAtual, 2));
      colisao = true;
    }
    distancia = 0;
  }
  if (colisao)
    return true;
  else
    return false;
}


float distanciaArena(float x, float y)
{
    float distancia;
    distancia = sqrt(pow(Arena->getx() - x, 2) + pow(Arena->gety() - y, 2));
    return distancia;
}


void idle(int x)
{
  distLimite = ( Arena->getRaio() - Aviao->getRaio() ) ;
  if (!startGame)
  {
  	float distAtual;
    distAtual = distanciaArena(Aviao->getx(), Aviao->gety());

    if (w == true) {
      float distFutura;
      distFutura = distanciaArena(Aviao->getx(), Aviao->gety() - vel);
      if(distFutura <= distLimite) {
      	// se nao estiver em colisao
      	if(!colisaoInimigos(Aviao->getx(), Aviao->gety() - vel, Aviao->getx(), Aviao->gety()))
      		Aviao->sety(Aviao->gety() - vel);
      	else {
      		//cout << distAux;
      		// pegar distancia do inimigo
      		// distlimite  = 2 * raio do inimigo
      		Aviao->sety(Aviao->gety() - (distAux - 40));	
      	}
      } else {
      	Aviao->sety(Aviao->gety() - (distLimite - distAtual));	
      }
      //Aviao->sety(Aviao->gety() - vel);
    }

    if (a == true) {
      float distFutura;
      distFutura = distanciaArena(Aviao->getx() - vel, Aviao->gety());
      if(distFutura <= distLimite) {
      	// se nao estiver em colisao
      	if(!colisaoInimigos(Aviao->getx() - vel, Aviao->gety(), Aviao->getx(), Aviao->gety()))
      		Aviao->setx(Aviao->getx() - vel);
      	else {
      		//cout << distAux;
      		// pegar distancia do inimigo
      		// distlimite  = 2 * raio do inimigo
      		Aviao->setx(Aviao->getx() - (distAux - 40));	
      	}
      } else {
      	Aviao->setx(Aviao->getx() - (distLimite - distAtual));	
      }
    }

    if (s == true) {
      float distFutura;
      distFutura = distanciaArena(Aviao->getx(), Aviao->gety() + vel);
      if(distFutura <= distLimite) {
      	// se nao estiver em colisao
      	if(!colisaoInimigos(Aviao->getx(), Aviao->gety() + vel, Aviao->getx(), Aviao->gety()))
      		Aviao->sety(Aviao->gety() + vel);
      	else {
      		//cout << distAux;
      		// pegar distancia do inimigo
      		// distlimite  = 2 * raio do inimigo
      		Aviao->sety(Aviao->gety() + (distAux - 40));	
      	}
      } else {
      	Aviao->sety(Aviao->gety() + (distLimite - distAtual));	
      }
    }

    if (d == true) {
      float distFutura;
      distFutura = distanciaArena(Aviao->getx() + vel, Aviao->gety());
      if(distFutura <= distLimite) {
      	// se nao estiver em colisao
      	if(!colisaoInimigos(Aviao->getx() + vel, Aviao->gety(), Aviao->getx(), Aviao->gety()))
      		Aviao->setx(Aviao->getx() + vel);
      	else {
      		//cout << distAux;
      		// pegar distancia do inimigo
      		// distlimite  = 2 * raio do inimigo
      		Aviao->setx(Aviao->getx() + (distAux - 40));	
      	}
      } else {
      	Aviao->setx(Aviao->getx() + (distLimite - distAtual));	
      }
    }
  }
  glutPostRedisplay();
  primeiroDesenho = true;
  glutTimerFunc(1000 / FPS, idle, 0);
}

const char *nome;
const char *tipo;
const char *caminho;
float velocidade;

float cx, cy;

void desenhaArena() {

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

void desenhaPista() {

  glColor3f(0, 0, 0);
  glBegin(GL_LINES);
    	glVertex2f(Pista->getx1(), Pista->gety1());
   		glVertex2f(Pista->getx2(), Pista->gety2());
  glEnd();
}

void desenhaInimigos()
{

  for (std::list<Circulo *>::iterator it = inimigos.begin(); it != inimigos.end(); it++)
  {

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
  //glutPostRedisplay();
}

float velocidadeIdeal;
float aceleracaoIdeal;
float deltax, deltay;
float raioOriginal;
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

  //vel = (velocidade/LAMBDA2);
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

  float wraio, wx, wy, wg, wb, wtipo;
  const char* fill;
  while(leitura2) {

    fill = leitura2->Attribute("fill");

    if (strcmp(fill, "blue") == 0) {
    	largura = atof(leitura2->Attribute("r"));
  		altura = atof(leitura2->Attribute("r"));
  		wx = atof(leitura2->Attribute("cx"));
  		deslocamento = abs(wx - largura);
  		//printf("%f\n", deslocamento);
		Arena = new Circulo(largura, largura, altura, 0, 0, 254, 0);
    }
    leitura2 = leitura2->NextSiblingElement("circle");
  }

  // garantir o deslocamento

  leitura2 = docHandle2.FirstChild("svg").Child("circle", 0).ToElement();

  while(leitura2) {

    fill = leitura2->Attribute("fill");

    if (strcmp(fill, "green") == 0) {
    	wraio = atof(leitura2->Attribute("r"));
  		wx = atof(leitura2->Attribute("cx"));
  		wy = atof(leitura2->Attribute("cy"));
      raioOriginal = wraio;
  		//deslocamento = wx - largura;
  		//printf("%f\n", deslocamento);
		Aviao = new Circulo(wraio, wx-deslocamento, wy-deslocamento, 0, 0.8, 0, 1);
    }

    if (strcmp(fill, "red") == 0) {
    	wraio = atof(leitura2->Attribute("r"));
  		wx = atof(leitura2->Attribute("cx"));
  		wy = atof(leitura2->Attribute("cy"));
  		//deslocamento = wx - largura;
  		//printf("%f\n", deslocamento);
		circ = new Circulo(wraio, wx-deslocamento, wy-deslocamento, 1, 0, 0, 2);
		inimigos.push_front(circ);
    }

    if (strcmp(fill, "orange") == 0) {
    	wraio = atof(leitura2->Attribute("r"));
  		wx = atof(leitura2->Attribute("cx"));
  		wy = atof(leitura2->Attribute("cy"));
  		//deslocamento = wx - largura;
  		//printf("%f\n", deslocamento);
		circ = new Circulo(wraio, wx-deslocamento, wy-deslocamento, 1, 0.65, 0, 3);
		inimigos.push_front(circ);
    }

    leitura2 = leitura2->NextSiblingElement("circle");
  }

  //cout << inimigos.size();

  // PARA FAZER LEITURA DO RETANGULO

  float wx1, wx2, wy1, wy2;

  leitura2 = docHandle2.FirstChild("svg").Child("line", 0).ToElement();

   wx1 = atof(leitura2->Attribute("x1"));
   wy1 = atof(leitura2->Attribute("y1"));
   wx2 = atof(leitura2->Attribute("x2"));
   wy2 = atof(leitura2->Attribute("y2"));

   //cout << wx1 << " " << wy1 << " " << wx2  << " " << wy2 << endl;
   //cout << deslocamento;

   deltax = abs(wx2 - wx1);
   deltay = abs(wy2 - wy1);

   cout << deltay;
   cout << deltax;

   Pista = new Retangulo(wx1-deslocamento,wx2-deslocamento,wy1-deslocamento, wy2-deslocamento);

  //cout << Pista->getx2();

   tamPista = sqrt(pow(wx1 - wx2, 2) + pow(wy1 - wy2, 2));
   distLimite = ( Arena->getRaio() - Aviao->getRaio() ) ;

   velocidadeIdeal = tamPista/LAMBDA;
   aceleracaoIdeal = ( pow(velocidadeIdeal, 2) / (2*tamPista) );

  vel = aceleracaoIdeal;
  //cout << aceleracaoIdeal;



  glutInit(&argc, argv);                       // inicializa o glut
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // especifica o uso de cores e buffers
  glutInitWindowSize(2 * largura, 2 * altura); // especifica as dimensoes da janela
  glutInitWindowPosition(100, 100);            // especifica aonde a janela aparece na tela
  glutCreateWindow(titulo);                    // cria a janela
  init();

  //glutPassiveMotionFunc(MouseAndandoSolto);
  //glutMotionFunc(MouseAndandoClicado);
  //glutMouseFunc(ClicarMouse);

  glutDisplayFunc(display);
  glutKeyboardFunc(GerenciaTeclado);
  glutKeyboardUpFunc(keyup);
  glutTimerFunc(1000 / FPS, idle, 0); // funcao que sera redesenhada pelo GLUT
  glutMainLoop();
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
  //gluOrtho2D(0.0, 2*largura, 2*altura, 0.0);
  //glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);     // modo de projecao ortogonal
  glOrtho(0, 2 * largura, 2 * largura, 0, 1, -2);
}

// crescer so apartir da metade da pista
// ajustar as questoes da aceleração
// ajustar a passagem do caminho relativo

void display(void)
{
  if (startGame)
  {
    if(Aviao->getx() >= 503 - deslocamento)
  	  Aviao->setRaio(Aviao->getRaio() + 0.15);
    
    //cout << Aviao->getRaio();

    if(deltax > 0 && deltay == 0) {
        	Aviao->setx(Aviao->getx() + vel);
          //Aviao->sety(Aviao->gety() - vel/2);
    }

    if(deltay > 0 && deltax == 0) {
        	//Aviao->setx(Aviao->getx() + vel);
          Aviao->sety(Aviao->gety() - vel);
    }

    if(deltax > 0 && deltay > 0) {
          if(deltax > deltay) {
        	Aviao->setx(Aviao->getx() + vel);
          Aviao->sety(Aviao->gety() - vel/(deltax/deltay));
          }
          if(deltay > deltax) {
        	Aviao->setx(Aviao->getx() + vel/(deltay/deltax));
          Aviao->sety(Aviao->gety() - vel);
          }
          if(deltay == deltax) {
        	Aviao->setx(Aviao->getx() + vel);
          Aviao->sety(Aviao->gety() - vel);
          }
    }

  	vel = vel + aceleracaoIdeal;

    //printf("%.2f", Pista->getx2());
    if (Aviao->getx() >= Pista->getx2()  && Aviao->gety() <= Pista->gety2() && sqrt(pow(Pista->getx2() - Aviao->getx(), 2) + pow(Pista->gety2() - Aviao->gety(), 2)) >= 2*raioOriginal) {
      startGame = false;
      Aviao->setRaio(20);
      vel = vel * velocidade;
      fimDecolagem = true;
    }
  }
  glClear(GL_COLOR_BUFFER_BIT);

  desenhaArena();

  desenhaPista();

  desenhaInimigos();

  desenhaAviao();

	  quadros++;
  final = time(NULL);
  if (final - inicial > 0)
  {
    cout << "Fps: " << quadros / (final - inicial) << endl;
    quadros = 0;
    inicial = final;
    cout << vel;
  }

  //while(!startGame);

  //glutPostRedisplay();
  //if(click == true)
  //desenhaCirculosTela();

  //desenhaCirculoModelo(Mousex, Mousey, raio, 4000);
  glFlush();
}
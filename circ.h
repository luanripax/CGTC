class Circulo
{
  private:
  float raio, corR, corG, corB, x, y;
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
    int getTipo();
    void setTipo(int r);
    void draw(Circulo *circ);
    Circulo* drag(Circulo *sqr, float x, float y);
};
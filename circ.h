class Circulo
{
  private:
  float raio, corR, corG, corB, x, y;
  public:
    Circulo(float x, float y, float R, float G, float B);
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
    void draw(Circulo *circ);
    Circulo* drag(Circulo *sqr, float x, float y);
};


class Bomba
{
  private:
  float raio, corR, corG, corB, x, y, px1, px2, py1, py2, xInicial, yInicial, ajuste;
  public:
    float deltax, deltay, vel, raioOriginal;
    int tipo;
    Bomba(float vel,float raio, float x, float y, float R, float G, float B, float deltax, float deltay, float px1, float px2, float py1, float py2, int tipo);
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
    float getdeltax();
    void setdeltax(float b);
    float getdeltay();
    void setdeltay(float b);
    float getpx1();
    void setpx1(float b);
    float getpx2();
    void setpx2(float b);
    float getpy1();
    void setpy1(float b);
    float getpy2();
    void setpy2(float b);
    float getxInicial();
    float getyInicial();
    float getVel();
    bool getajuste();
    void setajuste();
};
#ifndef PONTO_H
#define PONTO_H

class Ponto
{
    private:
        double x;
        double y;
    
    public:
        Ponto(double x, double y);
        Ponto();
        double getX();
        double getY();
};

#endif
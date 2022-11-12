#ifndef PONTO_H
#define PONTO_H

#include "../registro-base/registro-base.h"

class Ponto : public RegistroBase
{
    private:
        double x;
        double y;
    
    public:
        Ponto(int id, double x, double y);
        Ponto(int id);
        double getX();
        double getY();
};

#endif
#ifndef PONTO_H
#define PONTO_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

#include "../registro-base/registro-base.h"

using namespace std;

class Ponto : public RegistroBase
{
    private:
        double x;
        double y;
        int numero;
    
    public:
        Ponto(int id, int numero, double x, double y);
        Ponto(int id, int numero = 0);
        double getX();
        double getY();
        string toString();
};

#endif
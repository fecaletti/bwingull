#ifndef PONTO_H
#define PONTO_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

#include "../registro-base/registro-base.h"
#include "../stringavel/stringavel.h"
#include "../../../packages/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class Ponto : public RegistroBase, public IStringavel
{
    private:
        double x;
        double y;
        int numero;
    
    public:
        Ponto(int id, int numero, double x, double y);
        Ponto(int id, int numero = 0);
        double GetX();
        double GetY();
        int GetNumero();
        string ToString();
        json ToJson();
        static Ponto* FromJson(json entrada);
};

#endif
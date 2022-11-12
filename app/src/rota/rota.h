#ifndef ROTA_H
#define ROTA_H

#include "../ponto/ponto.h"
#include "../registro-base/registro-base.h"
#include <iostream>
#include <sstream>
#include <ostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class Rota: public RegistroBase
{
    private:
        vector<Ponto>* Pontos;
        string Descricao;

    public:
        Rota(int id);
        string toString();
};

#endif
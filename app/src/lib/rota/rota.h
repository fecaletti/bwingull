#ifndef ROTA_H
#define ROTA_H

#include "../ponto/ponto.h"
#include "../registro-base/registro-base.h"
#include "../stringavel/stringavel.h"
#include "../../../packages/nlohmann/json.hpp"
#include <iostream>
#include <sstream>
#include <ostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;
using json = nlohmann::json;

class Rota: public RegistroBase, public IStringavel
{
    private:
        string Descricao;

    public:
        Rota(int id);
        string ToString();
        vector<Ponto*>* Pontos;
        bool operator!= (Rota& outraRota);
        bool operator== (Rota& outraRota);
        bool RemovePonto(int index);
        void SetaDescricao(string descricao);
        string GetDescricao();
        json ToJson();
        static Rota* FromJson(json entrada);
};

#endif
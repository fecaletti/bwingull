#include "rota.h"

Rota :: Rota(int id) : RegistroBase(id)
{
    this->Pontos = new vector<Ponto*>();
}

string Rota :: toString()
{
    ostringstream strBuff;
    strBuff << "Rota " << this->id << ": " << this->Descricao << " - Pontos (QTD.): " << this->Pontos->size();
    return strBuff.str();
}
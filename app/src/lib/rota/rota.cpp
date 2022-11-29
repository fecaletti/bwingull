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

bool Rota :: operator!= (Rota& outraRota)
{
    return (this->id != outraRota.id) || (this->Descricao != outraRota.Descricao);
}

bool Rota :: operator== (Rota& outraRota)
{
    return this->id == outraRota.id;
}

bool Rota :: RemovePonto(int index)
{
    if((this->Pontos->size() - 1) < index)
        return false;
    
    this->Pontos->erase(this->Pontos->begin() + index);
    return true;
}

void Rota :: SetaDescricao(string descricao)
{
    this->Descricao = descricao;
}

string Rota :: GetDescricao()
{
    return this->Descricao;
}
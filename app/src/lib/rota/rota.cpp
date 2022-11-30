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

json Rota :: ToJson()
{
    vector<json>* jPontos = new vector<json>();
    for(int i  = 0; i < this->Pontos->size(); i++)
    {
        jPontos->push_back(this->Pontos->at(i)->ToJson());
    }

    json jBuff = {
        { "Id", this->id },
        { "Descricao", this->Descricao },
        { "Pontos", *jPontos }
    };

    return jBuff;
}

Rota* Rota :: FromJson(json input)
{
    Rota* novaRota = new Rota(input["Id"]);
    novaRota->SetaDescricao(input["Descricao"]);

    vector<json> jPontos = input["Pontos"];
    for(int i = 0; i < jPontos.size(); i++)
    {
        novaRota->Pontos->push_back(Ponto::FromJson(jPontos.at(i)));
    }

    return novaRota;
}
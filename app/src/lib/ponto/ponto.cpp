#include "ponto.h"

Ponto :: Ponto(int id, int numero, double x, double y) : RegistroBase(id)
{
    this->x = x;
    this->y = y;
    this->numero = numero;
}

Ponto :: Ponto(int id, int numero) : RegistroBase(id)
{
    this->x = 0;
    this->y = 0;
    this->numero = numero;
}

double Ponto :: GetX()
{
    return this->x;
}

double Ponto :: GetY()
{
    return this->y;
}

string Ponto :: ToString()
{
    ostringstream strBuf;
    strBuf << "Ponto " << this->numero << " - X: " << this->GetX() << " - Y: " << this->GetY();
    return strBuf.str();
}

int Ponto :: GetNumero()
{
    return this->numero;
}

json Ponto :: ToJson()
{
    json jBuff = {
        { "Id", this->id },
        { "Numero", this->numero },
        { "X", this->x },
        { "Y", this->y }
    };

    return jBuff;
}

Ponto* Ponto :: FromJson(json input)
{
    Ponto* novoPonto = new Ponto(input["Id"], input["Numero"], input["X"], input["Y"]);
    return novoPonto;
}
#include "ponto.h"

Ponto::Ponto(int id, int numero, double x, double y) : RegistroBase(id)
{
    this->x = x;
    this->y = y;
    this->numero = numero;
}

Ponto::Ponto(int id, int numero) : RegistroBase(id)
{
    this->x = 0;
    this->y = 0;
    this->numero = numero;
}

double Ponto::getX()
{
    return this->x;
}

double Ponto::getY()
{
    return this->y;
}
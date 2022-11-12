#include "ponto.h"

Ponto::Ponto(int id, double x, double y) : RegistroBase(id)
{
    this->x = x;
    this->y = y;
}

Ponto::Ponto(int id) : RegistroBase(id)
{
    this->x = 0;
    this->y = 0;
}

double Ponto::getX()
{
    return this->x;
}

double Ponto::getY()
{
    return this->y;
}
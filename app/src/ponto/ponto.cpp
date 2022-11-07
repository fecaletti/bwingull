#include "ponto.h"

Ponto::Ponto(double x, double y)
{
    this->x = x;
    this->y = y;
}

Ponto::Ponto()
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
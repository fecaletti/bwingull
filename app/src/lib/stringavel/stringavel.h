#ifndef STRINGAVEL_H
#define STRINGAVEL_H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

class IStringavel
{
    public:
        virtual string ToString() = 0;
};

#endif
#ifndef REGISTRO_BASE_H
#define REGISTRO_BASE_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "../../../packages/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

class RegistroBase 
{
    protected:
        int id;

    public:
        RegistroBase(int id)
        {
            this->id = id;
        };

        int GetId()
        {
            return this->id;
        }

        virtual json ToJson() = 0;
};

#endif
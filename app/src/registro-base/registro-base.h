#ifndef REGISTRO_BASE_H
#define REGISTRO_BASE_H

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
};

#endif
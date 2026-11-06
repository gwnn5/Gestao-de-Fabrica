#ifndef FABRICA_H
#define FABRICA_H
#include "uteis.h"

class Fabrica
{
    public:
        Fabrica();
        virtual ~Fabrica();

    protected:

    private:
        string nome;
        Hora Hora_abertura;
        Hora Hora_encerramento;

};

#endif // FABRICA_H

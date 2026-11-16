#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include "uteis.h"
class Fabrica;

class Dispositivo
{
    public:
        Dispositivo();
        virtual ~Dispositivo();
        int GetId() const { return Id; }
        string GetMarca() const { return Marca; }
        Posicao GetPosicao() const { return pos; }

    protected:
        int Id;
        string Marca;
        int Prob_avaria;
        Fabrica *Fab;
        Posicao pos;

    private:
};

#endif // DISPOSITIVO_H


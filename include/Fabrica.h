#ifndef FABRICA_H
#define FABRICA_H
#include "uteis.h"
#include "Motor.h"
#include "Sensor.h"

class Fabrica
{
    public:
        Fabrica();
        virtual ~Fabrica();
        void Avisar_gestor(int _id);

    protected:

    private:
        string Nome;
        Hora Hora_abertura;
        Hora Hora_encerramento;

};

#endif // FABRICA_H

#ifndef SENSOR_H
#define SENSOR_H
#include "uteis.h"
#include "Dispositivo.h"

class Fabrica;

class Sensor : public Dispositivo
{
    public:
        Sensor();
        virtual ~Sensor();
        //metodos
        virtual void Run();

    protected:

    private:
        float Valor;



};

#endif // SENSOR_H

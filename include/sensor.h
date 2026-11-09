#ifndef SENSOR_H
#define SENSOR_H
#include "uteis.h"
#include "Dispositivo.h"

class Fabrica;

class Sensor : public Dispositivo
{
    public:
        Sensor(int _id, string _marca, Posicao _pos, int _prob_avaria, float _valor);
        virtual ~Sensor();
        //metodos
        virtual void Run();

    protected:

    private:
        float Valor;



};

#endif // SENSOR_H

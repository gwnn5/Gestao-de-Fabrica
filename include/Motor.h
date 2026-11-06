#ifndef MOTOR_H
#define MOTOR_H
#include "uteis.h"
#include "Dispositivo.h"

class Fabrica;

class Motor : public Dispositivo
{
    public:
        Motor();
        virtual ~Motor();
        //metodos
        virtual void Run();

    protected:

    private:
        float Consumo_Hora;
        int Temp_Aviso;
        int Temp_Paragem;
        ESTADO_MOTOR Estado;
        CLASSE_TEMP Class_temp;


};

#endif // MOTOR_H

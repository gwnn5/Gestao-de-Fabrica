#ifndef MOTOR_H
#define MOTOR_H
#include "uteis.h"

class Motor
{
    public:
        Motor();
        virtual ~Motor();

    protected:

    private:
        int Id;
        string Marca;
        float Consumo_Hora;
        int Temp_Aviso;
        int Temp_Paragem;
        int Prob_Avaria;
        string Estado;
        int Class_temp; //1 para verde,2 para amarelho e 3 para vermelho? (?)

};

#endif // MOTOR_H

#include "Sensor.h"

Sensor::Sensor(int _id, string _marca, Posicao _pos, int _prob_avaria, float _valor)
{
    Id = _id;
    Marca = _marca;
    pos = _pos;
    Prob_avaria = _prob_avaria;
    Valor = _valor;
    //ctor
}

Sensor::~Sensor()
{
    //dtor
}

void Sensor::Run(){

}

void Sensor::Mostrar(ostream &f) const
{
    Dispositivo::Mostrar(f);
    f << " | Valor: " << Valor << endl;
}

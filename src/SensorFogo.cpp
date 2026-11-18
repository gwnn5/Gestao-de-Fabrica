#include "SensorFogo.h"
#include <iostream>

using namespace std;

SensorFogo::SensorFogo(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual)
    : Sensor(id, marca, pos, prob, valor_aviso, valor_atual) {}

string SensorFogo::Get_Tipo() const {
    return "SFOGO";
}

void SensorFogo::Mostrar(ostream &f) const {
    f << "[Fogo] ";
    Sensor::Mostrar(f); 
}
#include "SensorTemperatura.h"
#include <iostream>

using namespace std;

SensorTemperatura::SensorTemperatura(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual)
    : Sensor(id, marca, pos, prob, valor_aviso, valor_atual) {}

string SensorTemperatura::Get_Tipo() const {
    return "STEMPERATURA"; 
}

void SensorTemperatura::Mostrar(ostream &f) const {
    f << "[Temperatura] ";
    Sensor::Mostrar(f); 
}
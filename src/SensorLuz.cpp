#include "SensorLuz.h"
#include <iostream>

using namespace std;

SensorLuz::SensorLuz(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual)
    : Sensor(id, marca, pos, prob, valor_aviso, valor_atual) {}

string SensorLuz::Get_Tipo() const { 
    return "SLUZ"; }

void SensorLuz::Mostrar(ostream &f) const {
    f << "[Luz] ";
    Sensor::Mostrar(f); 
}
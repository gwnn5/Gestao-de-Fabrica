#include "SensorMissil.h"
#include <iostream>
#include <cstdlib>

using namespace std;

SensorMissil::SensorMissil(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual)
    : Sensor(id, marca, pos, prob, valor_aviso, valor_atual) {}

string SensorMissil::Get_Tipo() const {
    return "SMISSIL"; 
}

void SensorMissil::Mostrar(ostream &f) const {
     f << "[Missil] ";
    Sensor::Mostrar(f); 
}

void SensorMissil::Run() {
    int chance_avaria = rand() % 100;
    if (chance_avaria < Get_Prob()) { 
        this->valor_atual = -1; // Avariado
        return;
    }
    
    int chance_missel = rand() % 1000;
    if (chance_missel == 0) {
        this->valor_atual = 1; // Míssil detetado!
    } else {
        this->valor_atual = 0; // Zona segura
    }
}
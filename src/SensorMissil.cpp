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

// Em vez de variar o valor, o sensor de mísseis só deteta ou não deteta
void SensorMissil::Run() {
    int chance_avaria = rand() % 100;
    if (chance_avaria < Get_Prob()) {   // Avaria com probabilidade Prob_avaria %
        this->valor_atual = -1;
        return;
    }
    
    int chance_missel = rand() % 1000;  // Em média, míssil 1 vez em 1000 leituras
    if (chance_missel == 0) {
        this->valor_atual = 1;
    } else {
        this->valor_atual = 0;
    }
}
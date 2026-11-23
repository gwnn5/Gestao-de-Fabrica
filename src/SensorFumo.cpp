#include "SensorFumo.h"
#include <iostream>
#include <cstdlib>

using namespace std;

SensorFumo::SensorFumo(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual)
    : Sensor(id, marca, pos, prob, valor_aviso, valor_atual) {}

string SensorFumo::Get_Tipo() const {
    return "SFUMO"; 
}

void SensorFumo::Mostrar(ostream &f) const {
    f << "[Fumo] ";
    Sensor::Mostrar(f); 
}

// Em vez de variar o valor, o sensor de fumo só deteta ou não deteta
void SensorFumo::Run() {
    int chance_avaria = rand() % 100;
    if (chance_avaria < Get_Prob()) {   // Avaria com probabilidade Prob_avaria %
        this->valor_atual = -1;
        return;
    }
    
    int chance_fumo = rand() % 500;     // Em média, fumo 1 vez em 500 leituras
    if (chance_fumo == 0) {
        this->valor_atual = 1;
    } else {
        this->valor_atual = 0;
    }
}
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

void SensorFumo::Run() {
    int chance_avaria = rand() % 100;
    if (chance_avaria < Get_Prob()) { // Usa Get_Prob() se for privado
        this->valor_atual = -1; // Avariado
        return;
    }
    
    int chance_fumo = rand() % 500;
    if (chance_fumo == 0) {
        this->valor_atual = 1; // Fumo detetado!
    } else {
        this->valor_atual = 0; // Zona segura
    }
}
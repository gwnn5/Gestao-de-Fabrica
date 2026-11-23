#include "SensorHumidade.h"
#include <iostream>

using namespace std;

SensorHumidade::SensorHumidade(int id, string marca, Posicao p, float prob, float valor_aviso, float valor_atual) 
    : Sensor(id, marca, p, prob, valor_aviso, valor_atual) {}

string SensorHumidade::Get_Tipo() const { 
    return "SHUMIDADE"; 
}

string SensorHumidade::GetValorAtualString() const {
    // -1 é o código de avaria
    if (this->valor_atual == -1) {
        return "AVARIA";
    }

    // O simulador espera a humidade em percentagem, ex.: "85%"
    return to_string(static_cast<int>(this->valor_atual)) + "%"; 
}

void SensorHumidade::Mostrar(ostream &f) const {
    f << "[Humidade] ";
    Sensor::Mostrar(f); 
}
#include "Sensor.h"
#include <cstdlib>  // Necessário para usar a função rand()
#include <string>
#include <iostream>

Sensor::Sensor(int _id, string _marca, Posicao _pos, int _prob_avaria, float _valor)
{
    Id = _id;
    Marca = _marca;
    pos = _pos;
    Prob_avaria = _prob_avaria;
    Valor = _valor;
    //ctor
}


Sensor::~Sensor() {}


// ==========================================
// COMPORTAMENTO PADRÃO (SENSORES COMUNS)
// ==========================================

void Sensor::Run() {
    // 1. Verifica se ocorre uma avaria neste ciclo de execução
    // A função rand() % 100 gera um número entre 0 e 99.
    // Se for menor que Prob_avaria, o sensor avaria.
    int chance_avaria = rand() % 100;
    if (chance_avaria < this->Prob_avaria) {
        this->Valor = -1; // -1 serve como um código de erro/falha para o sensor
        return; // Interrompe a execução, pois o sensor está avariado
    }

    // 2. Simula o funcionamento normal: pequena flutuação aleatória no valor lido
    // Gera uma variação entre -5 e +5
    float variacao = (rand() % 11) - 5;
    this->Valor += variacao;

    // Garante que o valor lido não seja negativo (exceto o código de falha -1)
    if (this->Valor < 0 && this->Valor != -1) {
        this->Valor = 0;
    }
}

void Sensor::Mostrar(ostream &f) const
{
    Dispositivo::Mostrar(f);
    f << " | Valor: " << Valor << endl;
}

string Sensor::GetValorAtualString() const
{
    if (Valor == -1) return "AVARIA";
    return to_string((int)Valor);
}

// ==========================================
// COMPORTAMENTOS ESPECÍFICOS (CLASSES DERIVADAS)
// ==========================================

// O simulador exige que a humidade tenha o símbolo '%'
string SensorHumidade::GetValorAtualString() const {
    if (this->Valor == -1) return "AVARIA";
    return to_string((int)this->Valor) + "%";
}


// Sensor de Mísseis: Deteta se um míssil vem na direção da fábricaS
// O valor lido deve ser apenas 0 (seguro) ou 1 (alerta)
void SensorMissel::Run() {
    // Verifica avaria
    int chance_avaria = rand() % 100;
    if (chance_avaria < this->Prob_avaria) {
        this->Valor = -1; // Avariado
        return;
    }

    // Probabilidade muito baixa de detetar um míssil real (ex: 1 em 1000 ciclos)
    int chance_missel = rand() % 1000;
    if (chance_missel == 0) {
        this->Valor = 1; // Míssil detetado! (Dispara o evento na fábrica)
    } else {
        this->Valor = 0; // Zona segura
    }
}


// Sensor de Fumo: Deteta incêndios e zonas de fumo[cite: 8]
// Tal como o míssil, o valor é essencialmente binário (0 ou 1)
void SensorFumo::Run() {
    // Verifica avaria
    int chance_avaria = rand() % 100;
    if (chance_avaria < this->Prob_avaria) {
        this->Valor = -1; // Avariado
        return;
    }

    // Probabilidade baixa de detetar fumo (ex: 1 em 500 ciclos)
    int chance_fumo = rand() % 500;
    if (chance_fumo == 0) {
        this->Valor = 1; // Fumo detetado!
    } else {
        this->Valor = 0; // Zona segura
    }
}

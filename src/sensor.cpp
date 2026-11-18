#include "Sensor.h"
#include "SensorHumidade.h" 
#include "SensorMissil.h" 
#include "SensorFumo.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

// ==========================================
// CONSTRUTOR E DESTRUTOR
// ==========================================

Sensor::Sensor(int _id, string _marca, Posicao _pos, float _prob_avaria, float _valor_aviso, float _valor_atual)
    : Dispositivo(_id, _marca, _pos, _prob_avaria) // Chama o construtor da classe base
{
    this->valor_aviso = _valor_aviso;
    this->valor_atual = _valor_atual;
}

Sensor::~Sensor() {}


// ==========================================
// MÉTODOS DE CONTRATO (Para o Load XML e Avisos)
// ==========================================

float Sensor::Get_Valor() const {
    return this->valor_atual;
}

bool Sensor::Em_Alerta() const {
    // Retorna true se o valor atual ultrapassar ou igualar o valor de aviso
    return this->valor_atual >= this->valor_aviso;
}


// ==========================================
// COMPORTAMENTO PADRÃO (SENSORES COMUNS)
// ==========================================

void Sensor::Run() {
    // 1. Verifica se ocorre uma avaria neste ciclo de execução
    // A função rand() % 100 gera um número entre 0 e 99.
    // Nota: Se der erro no 'Prob_avaria', é porque está privado no Dispositivo. 
    // Nesse caso, muda 'this->Prob_avaria' para 'this->Get_Prob()'.
    int chance_avaria = rand() % 100;
    if (chance_avaria < this->Prob_avaria) {
        this->valor_atual = -1; // -1 serve como um código de erro/falha para o sensor
        return; // Interrompe a execução, pois o sensor está avariado
    }

    // 2. Simula o funcionamento normal: pequena flutuação aleatória no valor lido
    // Gera uma variação entre -5 e +5
    float variacao = (rand() % 11) - 5; 
    this->valor_atual += variacao;

    // Garante que o valor lido não seja negativo (exceto o código de falha -1)
    if (this->valor_atual < 0 && this->valor_atual != -1) {
        this->valor_atual = 0; 
    }
}

void Sensor::Mostrar(ostream &f) const
{
    Dispositivo::Mostrar(f);
    f << " | Tipo: " << Get_Tipo() 
      << " | Valor Atual: " << valor_atual 
      << " | Aviso: " << valor_aviso << endl;
}
// ==========================================
// FORMATAÇÃO DO VALOR ATUAL (XML)
// ==========================================

// 1. Implementação Padrão da Classe Base (O teu código)
string Sensor::GetValorAtualString() const {
    // Se o sensor estiver avariado
    if (this->valor_atual == -1) {
        return "AVARIA";
    }
    // Para a maioria dos sensores (Fogo, Luz, etc.), retorna apenas o número.
    return to_string((int)this->valor_atual);
}

// 2. Implementação Específica da Humidade (O código do teu colega, corrigido)
// O simulador exige que a humidade tenha o símbolo '%'
string SensorHumidade::GetValorAtualString() const {
    if (this->valor_atual == -1) return "AVARIA";
    return to_string((int)this->valor_atual) + "%";
}


// Sensor de Mísseis: Deteta se um míssil vem na direção da fábrica[cite: 10]
// O valor lido deve ser apenas 0 (seguro) ou 1 (alerta)
void SensorMissel::Run() {
    // Verifica avaria
    int chance_avaria = rand() % 100;
    if (chance_avaria < this->Prob_avaria) {
        this->valor_atual = -1; // Avariado
        return;
    }

    // Probabilidade muito baixa de detetar um míssil real (ex: 1 em 1000 ciclos)
    int chance_missel = rand() % 1000;
    if (chance_missel == 0) {
        this->valor_atual = 1; // Míssil detetado! (Dispara o evento na fábrica)
    } else {
        this->valor_atual = 0; // Zona segura
    }
}


// Sensor de Fumo: Deteta incêndios e zonas de fumo
// Tal como o míssil, o valor é essencialmente binário (0 ou 1)
void SensorFumo::Run() {
    // Verifica avaria
    int chance_avaria = rand() % 100;
    if (chance_avaria < this->Prob_avaria) {
        this->valor_atual = -1; // Avariado
        return;
    }

    // Probabilidade baixa de detetar fumo (ex: 1 em 500 ciclos)
    int chance_fumo = rand() % 500;
    if (chance_fumo == 0) {
        this->valor_atual = 1; // Fumo detetado!
    } else {
        this->valor_atual = 0; // Zona segura
    }
}
#include "Sensor.h"
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

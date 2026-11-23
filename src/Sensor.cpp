#include "Sensor.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

Sensor::Sensor(int _id, string _marca, Posicao _pos, float _prob_avaria, float _valor_aviso, float _valor_atual)
    : Dispositivo(_id, _marca, _pos, _prob_avaria)
{
    this->valor_aviso = _valor_aviso;
    this->valor_atual = _valor_atual;
}

Sensor::~Sensor() {}


float Sensor::Get_Valor() const {
    return this->valor_atual;
}

bool Sensor::Em_Alerta() const {
    return this->valor_atual >= this->valor_aviso;
}


// Comportamento comum (Luz, Temperatura, Fogo, Humidade).
// Fumo e Míssil têm o seu próprio Run.
void Sensor::Run() {
    // 1. Avaria com probabilidade Prob_avaria %: rand() % 100 dá um número de 0 a 99
    int chance_avaria = rand() % 100;
    if (chance_avaria < this->Prob_avaria) {
        this->valor_atual = -1;   // -1 é o código de avaria
        return;
    }

    // 2. Funcionamento normal: o valor varia entre -5 e +5
    float variacao = (rand() % 11) - 5;
    this->valor_atual += variacao;

    // Uma leitura não pode ser negativa (o -1 está reservado para avaria)
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

// Por omissão mostra só o número; a humidade redefine para acrescentar '%'
string Sensor::GetValorAtualString() const {
    if (this->valor_atual == -1) {
        return "AVARIA";
    }
    return to_string((int)this->valor_atual);
}

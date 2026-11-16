#include "Motor.h"
#include <iostream>
#include <cstdlib>

// ==========================================
// IMPLEMENTAÇÃO DA CLASSE BASE: Motor
// ==========================================

Motor::Motor(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, int prob) {
    this->Id = id;
    this->Marca = marca;
    this->pos = p;
    this->Consumo_Hora = consumo;
    this->Temp_Aviso = t_aviso;
    this->Temp_Paragem = t_paragem;
    this->Prob_avaria = prob;
    
    this->Estado = STOP; // Estado inicial por defeito[cite: 8]
    this->Valor_Temp_Atual = 20.0f; // Temperatura ambiente inicial (simulação)
}

Motor::~Motor() {}

// Retorna o estado atual do motor em formato de string (texto)
// Necessário para a tag <ESTADO_ATUAL> do simulador[cite: 11]
string Motor::GetEstadoString() const {
    switch(this->Estado) {
        case STOP:     return "STOP";
        case START:    return "START";
        case RUN:      return "RUN";
        case AVARIADO: return "AVARIADO";
        default:       return "DESCONHECIDO";
    }
}

// Retorna a cor da temperatura atual em formato de string (texto)
// Necessário para a tag <ESTADO_COR> do simulador[cite: 11]
string Motor::GetCorString() const {
    CLASSE_TEMP cor = Limites.Classificar(this->Valor_Temp_Atual);
    switch(cor) {
        case VERDE:    return "VERDE";
        case AMARELO:  return "AMARELO";
        case VERMELHO: return "VERMELHO";
        default:       return "DESCONHECIDO";
    }
}


// ==========================================
// IMPLEMENTAÇÃO: MotorCombustao
// ==========================================

MotorCombustao::MotorCombustao(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, int prob)
    : Motor(id, marca, p, consumo, t_aviso, t_paragem, prob) {}

void MotorCombustao::Start() {
    if (Estado == STOP) Estado = START;
}

void MotorCombustao::Run() {
    // Verifica avaria
    if (rand() % 100 < Prob_avaria) {
        Estado = AVARIADO;
        return;
    }
    
    if (Estado == START || Estado == RUN) {
        Estado = RUN;
        Valor_Temp_Atual += 5.0f; // Aquece mais rápido
    }
}

void MotorCombustao::Stop() { Estado = STOP; }
void MotorCombustao::Restart() { Stop(); Start(); Run(); }

bool MotorCombustao::Estou_Quente() {
    // Retorna true se já ultrapassou a zona verde[cite: 8]
    return Limites.Classificar(Valor_Temp_Atual) != VERDE; 
}


// ==========================================
// IMPLEMENTAÇÃO: MotorEletrico
// ==========================================

MotorEletrico::MotorEletrico(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, int prob)
    : Motor(id, marca, p, consumo, t_aviso, t_paragem, prob) {}

void MotorEletrico::Start() { if (Estado == STOP) Estado = START; }

void MotorEletrico::Run() {
    // Verifica avaria
    if (rand() % 100 < Prob_avaria) {
        Estado = AVARIADO;
        return;
    }
    
    if (Estado == START || Estado == RUN) {
        Estado = RUN;
        Valor_Temp_Atual += 2.0f; // Aquece de forma mais lenta
    }
}

void MotorEletrico::Stop() { Estado = STOP; }
void MotorEletrico::Restart() { Stop(); Start(); Run(); }

bool MotorEletrico::Estou_Quente() {
    return Limites.Classificar(Valor_Temp_Atual) != VERDE;
}


// ==========================================
// IMPLEMENTAÇÃO: MotorInducao
// ==========================================

MotorInducao::MotorInducao(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, int prob)
    : Motor(id, marca, p, consumo, t_aviso, t_paragem, prob) {}

void MotorInducao::Start() { if (Estado == STOP) Estado = START; }

void MotorInducao::Run() {
    // Verifica avaria
    if (rand() % 100 < Prob_avaria) {
        Estado = AVARIADO;
        return;
    }
    
    if (Estado == START || Estado == RUN) {
        Estado = RUN;
        Valor_Temp_Atual += 3.5f; // Aquecimento moderado
    }
}

void MotorInducao::Stop() { Estado = STOP; }
void MotorInducao::Restart() { Stop(); Start(); Run(); }

bool MotorInducao::Estou_Quente() {
    return Limites.Classificar(Valor_Temp_Atual) != VERDE;
}
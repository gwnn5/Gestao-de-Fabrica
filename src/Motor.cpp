#include "../include/Motor.h"

// Implementação do construtor da classe base abstrata Motor
Motor::Motor(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, int prob) {
    this->Id = id;
    this->Marca = marca;
    this->pos = p;
    this->Consumo_Hora = consumo;
    this->Temp_Aviso = t_aviso;
    this->Temp_Paragem = t_paragem;
    this->Prob_avaria = prob;

    this->Estado = STOP;           // Estado inicial predefinido como STOP
//  this->Class_temp = VERDE;      // Classe de temperatura inicial predefinida como VERDE
    this->Valor_Temp_Atual = 20.0; // Temperatura inicial simulada
}

Motor::~Motor() {}

// Implementação do construtor e métodos da classe derivada MotorCombustao
MotorCombustao::MotorCombustao(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, int prob)
    : Motor(id, marca, p, consumo, t_aviso, t_paragem, prob) {}

void MotorCombustao::Start() {
    Estado = START;
}

void MotorCombustao::Run() {
    Estado = RUN;
}

void MotorCombustao::Stop() {
    Estado = STOP;
}

void MotorCombustao::Restart() {
    Estado = START;
}

bool MotorCombustao::Estou_Quente() {
    // Retorna true se a temperatura atual atingir ou ultrapassar o limite de aviso (AMARELO)
    return Valor_Temp_Atual >= Temp_Aviso;
}

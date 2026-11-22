#include "MotorCombustao.h"

// Implementação do construtor e métodos da classe derivada MotorCombustao
MotorCombustao::MotorCombustao(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, float prob)
    : Motor(id, marca, p, consumo, t_aviso, t_paragem, prob) {}

MotorCombustao::~MotorCombustao()
{
    //dtor
}

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
string MotorCombustao::Get_Tipo() const { return "MCOMBUSTAO"; }

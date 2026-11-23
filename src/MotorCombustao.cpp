#include "MotorCombustao.h"

MotorCombustao::MotorCombustao(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, float prob)
    : Motor(id, marca, p, consumo, t_aviso, t_paragem, prob) {}

MotorCombustao::~MotorCombustao()
{
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

// O motor de combustão volta logo a arrancar, sem passar por STOP
void MotorCombustao::Restart() {
    Estado = START;
}

bool MotorCombustao::Estou_Quente() {
    return Valor_Temp_Atual >= Temp_Aviso;
}
string MotorCombustao::Get_Tipo() const { return "MCOMBUSTAO"; }

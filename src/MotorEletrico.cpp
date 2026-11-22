#include "MotorEletrico.h"

MotorEletrico::MotorEletrico(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, float prob)
    : Motor(id, marca, p, consumo, t_aviso, t_paragem, prob)
{
}

MotorEletrico::~MotorEletrico()
{
}

void MotorEletrico::Start() { Estado = START; }
void MotorEletrico::Run()   { Estado = RUN; }
void MotorEletrico::Stop()  { Estado = STOP; }
void MotorEletrico::Restart()
{
    Stop();
    Start();
}

bool MotorEletrico::Estou_Quente()
{
    return Valor_Temp_Atual >= Temp_Aviso;
}
string MotorEletrico::Get_Tipo() const { return "MELETRICO"; }

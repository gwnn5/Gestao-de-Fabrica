#include "MotorInducao.h"

MotorInducao::MotorInducao(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, float prob)
    : Motor(id, marca, p, consumo, t_aviso, t_paragem, prob)
{
}

MotorInducao::~MotorInducao()
{
}

void MotorInducao::Start() { Estado = START; }
void MotorInducao::Run()   { Estado = RUN; }
void MotorInducao::Stop()  { Estado = STOP; }
void MotorInducao::Restart()
{
    Stop();
    Start();
}

bool MotorInducao::Estou_Quente()
{
    return Valor_Temp_Atual >= Temp_Aviso;
}
string MotorInducao::Get_Tipo() const { return "MINDUCAO"; }

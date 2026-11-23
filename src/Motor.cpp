#include "Motor.h"
#include <iostream>
#include <cstdlib>

// O motor começa parado e a 20°. As faixas ficam a zero até ao
// Set_Limites, que o Load chama com as faixas do tipo do motor.
Motor::Motor(int id, string marca, Posicao p,
             float consumo, int t_aviso,
             int t_paragem, float prob)
    : Dispositivo(id, marca, p, prob),
      Consumo_Hora(consumo),
      Temp_Aviso(t_aviso),
      Temp_Paragem(t_paragem),
      Estado(STOP),
      Limites{},
      Valor_Temp_Atual(20.0f)
{
}


Motor::~Motor() {}

string Motor::Estado_Para_Texto() const
{
    switch (Estado)
    {
        case STOP:     return "STOP";
        case START:    return "START";
        case RUN:      return "RUN";
        case AVARIADO: return "AVARIADO";
    }
    return "?";
}

string Motor::Classe_Para_Texto() const
{
    switch (Limites.Classificar(Valor_Temp_Atual))
    {
        case VERDE:    return "VERDE";
        case AMARELO:  return "AMARELO";
        case VERMELHO: return "VERMELHO";
    }
    return "?";
}

void Motor::Mostrar(ostream &f) const
{
    Dispositivo::Mostrar(f);   // Primeiro os dados comuns: ID, marca e posição
    f << " | Estado: " << Estado_Para_Texto()
      << " | Temp: " << Valor_Temp_Atual << " (" << Classe_Para_Texto() << ")"
      << " | Consumo/h: " << Consumo_Hora << endl;
}

void Motor::Set_Temperatura(float temp) {
    this->Valor_Temp_Atual = temp;
}

void Motor::Set_Estado(ESTADO_MOTOR novo_estado) {
    this->Estado = novo_estado;
}

void Motor::Set_Limites(LimitesTemp novos_limites) {
    this->Limites = novos_limites;
}

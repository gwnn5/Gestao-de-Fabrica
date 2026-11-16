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
    Dispositivo::Mostrar(f);   // imprime ID, marca e posicao
    f << " | Estado: " << Estado_Para_Texto()
      << " | Temp: " << Valor_Temp_Atual << " (" << Classe_Para_Texto() << ")"
      << " | Consumo/h: " << Consumo_Hora << endl;
}


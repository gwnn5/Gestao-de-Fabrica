#include "Dispositivo.h"

Dispositivo::Dispositivo() {
    Id = 0;
    Marca = "";
    Prob_avaria = 0.0f;
    Fab = nullptr; // Inicializar ponteiro a nulo (Tarefa A7)
    pos.x = 0;
    pos.y = 0;
    Avarias = 0;
    Horas_Trabalhadas = 0;
}

// Construtor parametrizado chamado por Sensor e Motor
Dispositivo::Dispositivo(int id, string marca, Posicao p, float prob) {
    Id = id;
    Marca = marca;
    pos = p;
    Prob_avaria = prob;
    Fab = nullptr; // Inicializar ponteiro a nulo (Tarefa A7)
    Avarias = 0;
    Horas_Trabalhadas = 0;
}

Dispositivo::~Dispositivo()
{
    //dtor
}

void Dispositivo::Mostrar(ostream &f) const
{
    f << "ID: " << Id << " | Marca: " << Marca
      << " | Pos: (" << pos.x << "," << pos.y << ")";
}
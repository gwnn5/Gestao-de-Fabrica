#include "Dispositivo.h"

Dispositivo::Dispositivo() {
    Id = 0;
    Marca = "";
    Prob_avaria = 0.0f;
    Fab = nullptr;
    pos.x = 0;
    pos.y = 0;
    Avarias = 0;
    Horas_Trabalhadas = 0;
}

Dispositivo::Dispositivo(int id, string marca, Posicao p, float prob) {
    Id = id;
    Marca = marca;
    pos = p;
    Prob_avaria = prob;
    Fab = nullptr;           // Só fica definido quando a fábrica faz Add
    Avarias = 0;
    Horas_Trabalhadas = 0;
}

Dispositivo::~Dispositivo()
{
}

void Dispositivo::Mostrar(ostream &f) const
{
    f << "ID: " << Id << " | Marca: " << Marca
      << " | Pos: (" << pos.x << "," << pos.y << ")";
}
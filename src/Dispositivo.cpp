#include "Dispositivo.h"

Dispositivo::Dispositivo()
{
    //ctor
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

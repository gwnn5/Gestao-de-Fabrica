#include "Dispositivo.h"

Dispositivo::Dispositivo() {
    Id = 0;
    Marca = "";
    Prob_avaria = 0;
    Fab = nullptr;
    pos.x = 0;
    pos.y = 0;
}

Dispositivo::~Dispositivo()
{
    //dtor
}




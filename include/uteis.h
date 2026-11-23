#ifndef UTEIS_H_INCLUDED
#define UTEIS_H_INCLUDED

// Includes e tipos simples partilhados por todo o projeto.

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>
using namespace std;

// Hora do dia (horário de abertura e de fecho da fábrica).
struct Hora {
    int horas;
    int minutos;
};

// Coordenadas (x, y): posição de um dispositivo ou dimensão da fábrica.
struct Posicao {
    int x;
    int y;
};

#endif // UTEIS_H_INCLUDED

#ifndef UTEIS_H_INCLUDED
#define UTEIS_H_INCLUDED

#include <iostream>
#include <fstream>
using namespace std;

enum ESTADO_MOTOR { STOP, START, RUN, AVARIADO };
enum CLASSE_TEMP  { VERDE, AMARELO, VERMELHO };

struct Hora {
    int horas;
    int minutos;
};

struct Posicao {
    int x;
    int y;
};

#endif // UTEIS_H_INCLUDED

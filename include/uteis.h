#ifndef UTEIS_H_INCLUDED
#define UTEIS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cstdlib>
using namespace std;

struct Hora {
    int horas;
    int minutos;
};

struct Posicao {
    int x;
    int y;
};

// ==========================================
// FUNÇÕES AUXILIARES PARA LER O XML
// ==========================================

/**
 * @brief Separa um texto do tipo "A,B" em dois inteiros (ex.: "100,120" ou "0,80").
 * @param texto Texto a separar.
 * @param a Recebe o valor antes da vírgula.
 * @param b Recebe o valor depois da vírgula.
 * @return true se encontrou a vírgula, false caso contrário.
 */
inline bool Separar_Par(const string &texto, int &a, int &b)
{
    size_t pos = texto.find(',');
    if (pos == string::npos)
        return false;
    a = atoi(texto.substr(0, pos).c_str());
    b = atoi(texto.substr(pos + 1).c_str());
    return true;
}

/**
 * @brief Converte texto em número, ignorando um '%' no fim (ex.: "85%" -> 85).
 * @param texto Texto a converter.
 * @return O valor numérico.
 */
inline float Texto_Para_Numero(string texto)
{
    size_t pos = texto.find('%');
    if (pos != string::npos)
        texto = texto.substr(0, pos);
    return (float)atof(texto.c_str());
}

#endif // UTEIS_H_INCLUDED

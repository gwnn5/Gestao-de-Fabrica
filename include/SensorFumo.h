#ifndef SENSORFUMO_H
#define SENSORFUMO_H
#include "Sensor.h"

/** @brief Sensor de fumo. O valor é 1 (fumo detetado) ou 0 (sem fumo). */
class SensorFumo : public Sensor {
public:
    SensorFumo(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual);
    string Get_Tipo() const override;
    void Mostrar(ostream &f) const override;
    void Run() override; 
};

#endif
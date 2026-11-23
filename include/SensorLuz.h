#ifndef SENSORLUZ_H
#define SENSORLUZ_H
#include "Sensor.h"

// Sensor de luz.
class SensorLuz : public Sensor {
public:
    SensorLuz(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual);
    string Get_Tipo() const override;
    void Mostrar(ostream &f) const override;
};

#endif
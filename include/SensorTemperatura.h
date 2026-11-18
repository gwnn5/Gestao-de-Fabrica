#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H
#include "Sensor.h"

class SensorTemperatura : public Sensor {
public:
    SensorTemperatura(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual);
    string Get_Tipo() const override;
    void Mostrar(ostream &f) const override;
};

#endif
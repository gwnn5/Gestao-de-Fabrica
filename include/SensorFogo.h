#ifndef SENSORFOGO_H
#define SENSORFOGO_H
#include "Sensor.h"

// Sensor de fogo.
class SensorFogo : public Sensor {
public:
    SensorFogo(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual);
    string Get_Tipo() const override;
    void Mostrar(ostream &f) const override;
};

#endif




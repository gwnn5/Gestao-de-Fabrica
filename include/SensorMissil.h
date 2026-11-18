#ifndef SENSORMISSIL_H
#define SENSORMISSIL_H
#include "Sensor.h"

class SensorMissil : public Sensor {
public:
    SensorMissil(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual);
    string Get_Tipo() const override;
    void Mostrar(ostream &f) const override;
    void Run() override; 
};

#endif
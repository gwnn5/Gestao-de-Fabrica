#ifndef SENSORFUMO_H
#define SENSORFUMO_H
#include "Sensor.h"

class SensorFumo : public Sensor {
public:
    SensorFumo(int id, string marca, Posicao pos, float prob, float valor_aviso, float valor_atual);
    string Get_Tipo() const override;
    void Mostrar(ostream &f) const override;
    void Run() override; 
};

#endif
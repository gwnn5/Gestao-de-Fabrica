#ifndef SENSORHUMIDADE_H
#define SENSORHUMIDADE_H

#include "Sensor.h"

// Sensor de humidade. No XML o valor aparece em percentagem (ex.: "85%").
class SensorHumidade : public Sensor {
public:
    SensorHumidade(int id, string marca, Posicao p, float prob, float valor_aviso, float valor_atual);
    string Get_Tipo() const override;
    string GetValorAtualString() const override;
    void Mostrar(ostream &f) const override;
};

#endif
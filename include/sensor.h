#ifndef SENSOR_H
#define SENSOR_H

#include "uteis.h"
#include "Dispositivo.h"
#include <string>

class Fabrica;

class Sensor : public Dispositivo {
    protected:
        float valor_aviso;
        float valor_atual;

    public:
        float Get_Aviso() const { return valor_aviso; }
        // Construtor atualizado com valor_aviso e valor_atual
        Sensor(int _id, string _marca, Posicao _pos, float _prob_avaria, float _valor_aviso, float _valor_atual);
        virtual ~Sensor();
        
        // Métodos de contrato exigidos pelo Elemento C
        float Get_Valor() const;
        virtual bool Em_Alerta() const;
        virtual string Get_Tipo() const = 0; // Método virtual puro para as etiquetas do XML

        // Adicionado para suportar formatações específicas, como o '%' no SensorHumidade
        virtual string GetValorAtualString() const; 

        // Métodos de simulação
        virtual void Run();
        
        // Verifica se a tua classe Dispositivo requer ostream&
        void Mostrar(ostream &f) const override;
};

#endif // SENSOR_H
#ifndef SENSOR_H
#define SENSOR_H

#include "uteis.h"
#include "Dispositivo.h"
#include <string>

using namespace std;

class Fabrica;

class Sensor : public Dispositivo {
    protected:
        float valor_aviso;
        float valor_atual;

    public:
        // Getter para o aviso
        float Get_Aviso() const { return valor_aviso; }
        
        // Construtor base atualizado
        Sensor(int _id, string _marca, Posicao _pos, float _prob_avaria, float _valor_aviso, float _valor_atual);
        virtual ~Sensor();
        
        // Métodos de contrato exigidos pelo Elemento C
        float Get_Valor() const;
        virtual bool Em_Alerta() const;
        
        // Método virtual puro - OBRIGA os filhos a terem a sua própria etiqueta XML
        virtual string Get_Tipo() const = 0; 

        // Suporta formatações específicas (como o '%' no SensorHumidade)
        virtual string GetValorAtualString() const; 

        // Métodos de simulação
        virtual void Run();
        
        // Mostra a informação no ecrã
        void Mostrar(ostream &f) const override;
};

#endif // SENSOR_H
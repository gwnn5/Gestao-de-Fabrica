#ifndef SENSOR_H
#define SENSOR_H

#include "uteis.h"
#include "Dispositivo.h"
#include <string>

class Fabrica;

class Sensor : public Dispositivo {
    public:
        Sensor(int id, string marca, Posicao p, int prob, float valor_aviso);
        virtual ~Sensor();
        
        // Métodos de simulação
        virtual void Run();
        
        // Método virtual para formatação do valor para exportação XML
        virtual string GetValorAtualString() const;

    protected:
        float Valor;
        float Valor_Aviso;
};

// ==========================================
// CLASSES DERIVADAS (Tipos de Sensores)
// ==========================================

class SensorLuz : public Sensor {
    public: 
        SensorLuz(int id, string marca, Posicao p, int prob, float valor_aviso) 
            : Sensor(id, marca, p, prob, valor_aviso) {}
};

class SensorHumidade : public Sensor {
    public: 
        SensorHumidade(int id, string marca, Posicao p, int prob, float valor_aviso) 
            : Sensor(id, marca, p, prob, valor_aviso) {}
        
        // Sobrescrito para adicionar o símbolo '%' exigido pelo simulador na tag <VALOR_ATUAL>
        string GetValorAtualString() const override;
};

class SensorFumo : public Sensor {
    public: 
        SensorFumo(int id, string marca, Posicao p, int prob, float valor_aviso) 
            : Sensor(id, marca, p, prob, valor_aviso) {}
        
        // Sobrescrito pois tem comportamento de deteção específico (binário: 0 ou 1)
        void Run() override;
};

class SensorMissel : public Sensor {
    public: 
        SensorMissel(int id, string marca, Posicao p, int prob, float valor_aviso) 
            : Sensor(id, marca, p, prob, valor_aviso) {}
        
        // Sobrescrito pois tem comportamento de deteção específico (binário: 0 ou 1)
        void Run() override;
};

class SensorTemperatura : public Sensor {
    public: 
        SensorTemperatura(int id, string marca, Posicao p, int prob, float valor_aviso) 
            : Sensor(id, marca, p, prob, valor_aviso) {}
};

#endif // SENSOR_H
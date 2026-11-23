#ifndef SENSOR_H
#define SENSOR_H

#include "uteis.h"
#include "Dispositivo.h"
#include <string>

using namespace std;

class Fabrica;

// Classe abstrata de todos os sensores.
// Um sensor guarda a última leitura e o valor a partir do qual dispara
// um aviso. Uma leitura de -1 significa que o sensor está avariado.
class Sensor : public Dispositivo {
    protected:
        float valor_aviso;   // A partir deste valor o sensor está em alerta
        float valor_atual;   // Última leitura (-1 = avariado)

    public:
        float Get_Aviso() const { return valor_aviso; }
        
        Sensor(int _id, string _marca, Posicao _pos, float _prob_avaria, float _valor_aviso, float _valor_atual);
        virtual ~Sensor();
        
        float Get_Valor() const;
        // true se a leitura atual atingiu o valor de aviso.
        virtual bool Em_Alerta() const;
        
        // Etiqueta XML do tipo (SHUMIDADE, SLUZ, ...). Virtual pura: cada sensor define a sua.
        virtual string Get_Tipo() const = 0; 

        // Leitura em texto para o XML e o HTML ("AVARIA" se avariado).
        virtual string GetValorAtualString() const; 

        // Simula uma leitura: o sensor pode avariar ou o valor varia um pouco.
        virtual void Run();
        
        void Mostrar(ostream &f) const override;
};

#endif // SENSOR_H

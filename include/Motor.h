#ifndef MOTOR_H
#define MOTOR_H
#include "uteis.h"
#include "Dispositivo.h"

class Fabrica;

// Classe abstrata Motor que herda de Dispositivo
class Motor : public Dispositivo
{
    public:
        Motor(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, int prob);
        virtual ~Motor();
        
       // Métodos virtuais puros a implementar pelas classes derivadas
        virtual void Run() = 0;
        virtual void Start() = 0;
        virtual void Restart() = 0;
        virtual void Stop() = 0;
        virtual bool Estou_Quente() = 0;

    protected:
        float Consumo_Hora;       
        int Temp_Aviso;           // Temperatura limite para aviso (passa a AMARELO)
        int Temp_Paragem;         // Temperatura limite para paragem (passa a VERMELHO)
        ESTADO_MOTOR Estado;      // Estado atual do motor (STOP, START, RUN, AVARIADO)
        CLASSE_TEMP Class_temp;   // Classe de temperatura atual (VERDE, AMARELO, VERMELHO)
        float Valor_Temp_Atual;   // Registo da temperatura atual exata do motor
};

// Classes derivadas para tipos específicos de motores de acordo com o ficheiro XML
class MotorCombustao : public Motor {
    public:
        MotorCombustao(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, int prob);
        void Run() override;
        void Start() override;
        void Restart() override;
        void Stop() override;
        bool Estou_Quente() override;
};

class MotorEletrico : public Motor { /* A implementar de forma semelhante */ };
class MotorInducao : public Motor { /* A implementar de forma semelhante */ };

#endif // MOTOR_H
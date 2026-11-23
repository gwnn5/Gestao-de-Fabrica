#ifndef MOTORELETRICO_H
#define MOTORELETRICO_H

#include "Motor.h"

// Motor de elétrico.
// Implementa as mudanças de estado e identifica-se no XML como MELETRICO.
class MotorEletrico : public Motor
{
      public:
        MotorEletrico(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, float prob);
        virtual ~MotorEletrico();

        void Run() override;
        void Start() override;
        void Restart() override;
        void Stop() override;
        bool Estou_Quente() override;
        string Get_Tipo() const override;
};

#endif // MOTORELETRICO_H

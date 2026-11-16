#ifndef MOTORINDUCAO_H
#define MOTORINDUCAO_H

#include "Motor.h"


class MotorInducao : public Motor
{
      public:
        MotorInducao(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, int prob);
        virtual ~MotorInducao();

        void Run() override;
        void Start() override;
        void Restart() override;
        void Stop() override;
        bool Estou_Quente() override;
        string Get_Tipo() const override;
};

#endif // MOTORINDUCAO_H

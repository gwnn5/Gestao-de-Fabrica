#ifndef MOTORCOMBUSTAO_H
#define MOTORCOMBUSTAO_H

#include "Motor.h"

// Motor de combustão.
// Implementa as mudanças de estado e identifica-se no XML como MCOMBUSTAO.
class MotorCombustao : public Motor {
    public:
        MotorCombustao(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, float prob);
        virtual ~MotorCombustao();
        void Run() override;
        void Start() override;
        void Restart() override;
        void Stop() override;
        bool Estou_Quente() override;
        string Get_Tipo() const override;
};



#endif // MOTORCOMBUSTAO_H

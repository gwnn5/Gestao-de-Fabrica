#ifndef MOTOR_H
#define MOTOR_H
#include "uteis.h"
#include "Dispositivo.h"

// Estados possíveis de um motor.
enum ESTADO_MOTOR { STOP, START, RUN, AVARIADO };
// Classe (cor) de temperatura de um motor.
enum CLASSE_TEMP  { VERDE, AMARELO, VERMELHO };

class Fabrica;

// Intervalo de temperaturas [minimo, maximo], lido do XML como "0, 80".
struct Faixa {
    int minimo;
    int maximo;
};

// As três faixas de temperatura de um tipo de motor.
struct LimitesTemp {
    Faixa verde, amarelo, vermelho;

    // Devolve a cor correspondente a uma temperatura.
    // Compara do mais quente para o mais frio: basta passar o início
    // de uma faixa para pertencer a ela.
    CLASSE_TEMP Classificar(float temp) const
    {
        if (temp >= vermelho.minimo) return VERMELHO;
        if (temp >= amarelo.minimo)  return AMARELO;
        return VERDE;
    }
};

// Classe abstrata de todos os motores.
// Não se cria um Motor genérico: só MotorCombustao, MotorEletrico e
// MotorInducao, que implementam os métodos virtuais puros.
class Motor : public Dispositivo
{
    public:
        Motor(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, float prob);
        virtual ~Motor();
        void Mostrar(ostream &f) const override;

        // Etiqueta XML do tipo: "MCOMBUSTAO", "MELETRICO" ou "MINDUCAO".
        virtual string Get_Tipo() const = 0;
        ESTADO_MOTOR Get_Estado() const { return Estado; }

        // Mudanças de estado: cada tipo de motor implementa as suas
        virtual void Run() = 0;
        virtual void Start() = 0;
        virtual void Restart() = 0;
        virtual void Stop() = 0;
        // true se a temperatura atual já atingiu a temperatura de aviso.
        virtual bool Estou_Quente() = 0;

        float Get_Temperatura() const { return Valor_Temp_Atual; }
        float Get_Consumo() const { return Consumo_Hora; }
        // Cor atual, calculada a partir da temperatura e das faixas do tipo.
        CLASSE_TEMP Get_Classe_Temp() const { return Limites.Classificar(Valor_Temp_Atual); }

        // Usado na manutenção para repor uma temperatura normal.
        Faixa Get_Faixa_Verde() const { return Limites.verde; }

        // Ainda sem implementação: o Relatorio usa EstadoParaString e
        // CorParaString, definidas na Fabrica.cpp
        string GetEstadoString() const;
        string GetCorString() const;

        // Setters usados pelo Load e pela Manutenção
        void Set_Temperatura(float temp);
        void Set_Estado(ESTADO_MOTOR novo_estado);
        void Set_Limites(LimitesTemp novos_limites);

    protected:
        float Consumo_Hora;
        int Temp_Aviso;           // A partir daqui o motor está quente (início do AMARELO)
        int Temp_Paragem;         // A partir daqui o motor deve parar (início do VERMELHO)
        ESTADO_MOTOR Estado;
        LimitesTemp Limites;      // Faixas de temperatura do tipo deste motor
        float Valor_Temp_Atual;
        // Textos usados pelo Mostrar.
        string Estado_Para_Texto() const;
        string Classe_Para_Texto() const;
};

#endif // MOTOR_H

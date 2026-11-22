#ifndef MOTOR_H
#define MOTOR_H
#include "uteis.h"
#include "Dispositivo.h"

// Estados possíveis de um motor
enum ESTADO_MOTOR { STOP, START, RUN, AVARIADO };
// Classes de temperatura do motor
enum CLASSE_TEMP  { VERDE, AMARELO, VERMELHO };

class Fabrica;

struct Faixa {
    int minimo;
    int maximo;
};

struct LimitesTemp {
    Faixa verde, amarelo, vermelho;

    CLASSE_TEMP Classificar(float temp) const
    {
        if (temp >= vermelho.minimo) return VERMELHO;
        if (temp >= amarelo.minimo)  return AMARELO;
        return VERDE;
    }
};

// Classe abstrata Motor que herda de Dispositivo
class Motor : public Dispositivo
{
    public:
        Motor(int id, string marca, Posicao p, float consumo, int t_aviso, int t_paragem, float prob);
        virtual ~Motor();
        void Mostrar(ostream &f) const override;

       // Métodos virtuais puros a implementar pelas classes derivadas
        virtual string Get_Tipo() const = 0;
        ESTADO_MOTOR Get_Estado() const { return Estado; }
        virtual void Run() = 0;
        virtual void Start() = 0;
        virtual void Restart() = 0;
        virtual void Stop() = 0;
        virtual bool Estou_Quente() = 0;

        // ==========================================
        // NOVOS GETTERS ADICIONADOS AQUI
        // ==========================================
        float Get_Temperatura() const { return Valor_Temp_Atual; }
        float Get_Consumo() const { return Consumo_Hora; }
        CLASSE_TEMP Get_Classe_Temp() const { return Limites.Classificar(Valor_Temp_Atual); }
        // ==========================================

        Faixa Get_Faixa_Verde() const { return Limites.verde; }

        // Métodos auxiliares para exportação XML
        string GetEstadoString() const;
        string GetCorString() const;

        // ==========================================
        // SETTERS (Para o Load do XML e Manutenção)
        // ==========================================
        void Set_Temperatura(float temp);
        void Set_Estado(ESTADO_MOTOR novo_estado);
        void Set_Limites(LimitesTemp novos_limites);

    protected:
        float Consumo_Hora;
        int Temp_Aviso;           // Temperatura limite para aviso (passa a AMARELO)
        int Temp_Paragem;         // Temperatura limite para paragem (passa a VERMELHO)
        ESTADO_MOTOR Estado;      // Estado atual do motor (STOP, START, RUN, AVARIADO)
        LimitesTemp Limites;      // Classe de temperatura atual (VERDE, AMARELO, VERMELHO)
        float Valor_Temp_Atual;   // Registo da temperatura atual exata do motor
        string Estado_Para_Texto() const;
        string Classe_Para_Texto() const;
};

#endif // MOTOR_H
#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include "uteis.h"
class Fabrica;

class Dispositivo
{
    public:
        Dispositivo();
        // Construtor com parâmetros para ser chamado pelas subclasses
        Dispositivo(int id, string marca, Posicao p, float prob);
        virtual ~Dispositivo();
        
        void Atribuir_Fabrica(Fabrica *_F) { Fab = _F; }
        virtual void Mostrar(ostream &f) const;

        // Getters do Contrato (Tarefa A3)
        int Get_Id() const { return Id; }
        string Get_Marca() const { return Marca; }
        Posicao Get_Pos() const { return pos; }
        float Get_Prob() const { return Prob_avaria; }
        int Get_Avarias() const { return Avarias; }
        int Get_Horas_Trabalhadas() const { return Horas_Trabalhadas; }

    protected:
        int Id;
        string Marca;
        float Prob_avaria; // Alterado para float para não perder precisão
        Fabrica *Fab;
        Posicao pos;
        
        // Atributos adicionados para as estatísticas (Rankings e Relatórios)
        int Avarias;
        int Horas_Trabalhadas;

    private:
};

#endif // DISPOSITIVO_H
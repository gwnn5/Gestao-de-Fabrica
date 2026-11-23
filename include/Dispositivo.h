#ifndef DISPOSITIVO_H
#define DISPOSITIVO_H

#include "uteis.h"
class Fabrica;

// Classe base de tudo o que está instalado na fábrica (motores e sensores).
// Guarda os dados comuns a todos os dispositivos, para não os repetir
// em Motor e em Sensor.
class Dispositivo
{
    public:
        Dispositivo();
        // Construtor chamado pelas subclasses na lista de inicialização.
        Dispositivo(int id, string marca, Posicao p, float prob);
        // Virtual para que delete através de um ponteiro da base chame o destrutor certo.
        virtual ~Dispositivo();
        
        // Liga o dispositivo à fábrica que o gere (chamado por Fabrica::Add).
        void Atribuir_Fabrica(Fabrica *_F) { Fab = _F; }
        // Escreve ID, marca e posição; as subclasses acrescentam os seus dados.
        virtual void Mostrar(ostream &f) const;

        int Get_Id() const { return Id; }
        string Get_Marca() const { return Marca; }
        Posicao Get_Pos() const { return pos; }
        float Get_Prob() const { return Prob_avaria; }
        int Get_Avarias() const { return Avarias; }
        int Get_Horas_Trabalhadas() const { return Horas_Trabalhadas; }

    protected:
        int Id;
        string Marca;
        float Prob_avaria;       // Probabilidade de avaria em cada ciclo, em %
        Fabrica *Fab;            // Fábrica a que pertence (nullptr até ao Add)
        Posicao pos;
        
        int Avarias;             // Número de avarias, usado nos rankings
        int Horas_Trabalhadas;   // Horas em funcionamento, usado nos rankings

    private:
};

#endif // DISPOSITIVO_H

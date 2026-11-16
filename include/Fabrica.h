#ifndef FABRICA_H
#define FABRICA_H
#include "uteis.h"
#include "Motor.h"
#include "Sensor.h"
#include "User.h" // Inclui as definições dos utilizadores
#include <list>
#include <string>

class Fabrica
{
    public:
        Fabrica(User *ut);
        virtual ~Fabrica();
        void Avisar_gestor(int _id);
        // Métodos principais de gestão
        Motor *Procurar_Motor(int id);
        bool Load(const string &ficheiro); // Carrega a configuração inicial via XML
        bool Add(User *ut);
        bool Add(Motor *m);
        bool Add(Sensor *s);
        void Listar(ostream &f = std::cout); // Lista o estado atual da fábrica
        void Desligar(int id_motor);         // Desliga um motor específico dado o seu ID
        ESTADO_MOTOR Get_Estado(int id_motor); // Obtém o estado de um motor específico
        list<Motor *> *Listar_Tipo(string Tipo, ostream &f = std::cout);
        bool Manutencao();                 // Efetua a manutenção aos dispositivos

        // --- MÉTODOS EM FALTA ADICIONADOS AQUI ---
        list<string> *Ranking_Dos_Fracos(); // Devolve lista de marcas que mais avariam[cite: 9]
        list<Motor *> *Ranking_Dos_Mais_Trabalhadores(); // Devolve lista de motores que mais trabalharam[cite: 9]
        void Relatorio(string fich_xml); // Envia relatório XML do estado da fábrica e consumo[cite: 9]
        void Listagem_HTML(string fich_html); // Grava ficheiro HTML com o estado atual[cite: 9]
        // -----------------------------------------

        // Métodos de alerta gerados pelos sensores e respetivas reações
        int Aviso_Humidade(list<Motor *> &lm);
        int Aviso_Fumo(list<Motor *> &lm, string fich_video);
        int Aviso_Luz(string fich_video);
        void Aviso_Missel(string fvideo, string festado = "Estado.txt");

    private:
        string Nome;
        Hora Hora_abertura;
        Hora Hora_encerramento;

        User* utilizadorAtual;       // Apontador para o utilizador a operar o sistema no momento
        list<Motor*> listaMotores;
        list<Sensor*> listaSensores;
};
#endif // FABRICA_H
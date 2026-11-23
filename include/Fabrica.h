#ifndef FABRICA_H
#define FABRICA_H
#include "uteis.h"
#include "Motor.h"
#include "Sensor.h"
#include "User.h"
#include <list>
#include <string>

// Gere a fábrica e todos os seus dispositivos.
// É dona dos motores e dos sensores: recebe-os com Add e apaga-os no
// destrutor. Antes de alterar a fábrica verifica as permissões do
// utilizador atual. Os utilizadores só são guardados, não apagados.
class Fabrica
{
    public:
        Fabrica(User *ut);
        virtual ~Fabrica();
        // Avisa o gestor sobre um problema no dispositivo com este ID.
        void Avisar_gestor(int _id);

        // Motor com este ID, ou NULL se não existir.
        Motor *Procurar_Motor(int id);
        // Carrega a configuração, os motores e os sensores de um ficheiro XML.
        bool Load(const string &ficheiro);
        // Os Add só aceitam se o utilizador atual tiver permissão para adicionar
        bool Add(User *ut);
        bool Add(Motor *m);
        bool Add(Sensor *s);
        // Escreve o nome, o horário e todos os motores e sensores.
        void Listar(ostream &f = std::cout);
        // Põe em STOP o motor com este ID (não faz nada se não existir).
        void Desligar(int id_motor);
        // Estado do motor com este ID (STOP se não existir).
        ESTADO_MOTOR Get_Estado(int id_motor);
        // Lista nova com os motores do tipo pedido; quem chama apaga a lista, não os motores.
        list<Motor *> *Listar_Tipo(string Tipo, ostream &f = std::cout);
        // Repõe os motores numa temperatura normal. Devolve true se interveio em algum dispositivo.
        bool Manutencao();

        // Setters e getters usados pelo Load
        void Set_Nome(string n);
        void Set_Horas(Hora abertura, Hora encerramento);
        void Set_Vizinhanca(int v);
        void Set_Dimensao(Posicao d);
        string Get_Nome() const;

        // Marcas que mais avariam.
        list<string> *Ranking_Dos_Fracos();
        // Motores que mais horas trabalharam.
        list<Motor *> *Ranking_Dos_Mais_Trabalhadores();
        // Grava em XML o estado de todos os dispositivos e o consumo do dia.
        void Relatorio(string fich_xml);
        // Grava uma página HTML com o estado atual da fábrica.
        void Listagem_HTML(string fich_html);

        // Reações aos avisos dos sensores
        int Aviso_Humidade(list<Motor *> &lm);
        int Aviso_Fumo(list<Motor *> &lm, string fich_video);
        int Aviso_Luz(string fich_video);
        void Aviso_Missel(string fvideo, string festado = "Estado.txt");

    private:
        string Nome;
        Hora Hora_abertura;
        Hora Hora_encerramento;

        int Vizinhanca;              // Raio usado no aviso de humidade
        Posicao Dimensao;            // Dimensão da fábrica (x, y)

        User* utilizadorAtual;       // Quem está a operar o sistema
        list<User*> listaUsers;      // Utilizadores registados (não são apagados pela fábrica)
        list<Motor*> listaMotores;   // Apagados no destrutor
        list<Sensor*> listaSensores; // Apagados no destrutor
};
#endif // FABRICA_H

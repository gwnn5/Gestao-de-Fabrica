#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User {
    protected:
        int Id;
        string Nome;
    public:
        User(int id, string nome) : Id(id), Nome(nome) {}
        virtual ~User() {}
        
        // Interfaces virtuais para verificar as permissões do utilizador
        virtual bool PodeAdicionar() const = 0;
        virtual bool PodeRemover() const = 0;
        virtual bool PodeListar() const = 0;
        virtual bool PodeRun() const = 0;
        virtual bool PodeManutencao() const = 0;
};

// Utilizador com privilégios máximos (Pode fazer tudo)
class Admin : public User {
    public:
        Admin(int id, string nome) : User(id, nome) {}
        bool PodeAdicionar() const override { return true; }
        bool PodeRemover() const override { return true; }
        bool PodeListar() const override { return true; }
        bool PodeRun() const override { return true; }
        bool PodeManutencao() const override { return true; }
};

// Utilizador com privilégios normais
class Normal : public User {
    public:
        Normal(int id, string nome) : User(id, nome) {}
        bool PodeAdicionar() const override { return true; }
        bool PodeRemover() const override { return false; } // Não pode remover
        bool PodeListar() const override { return true; }
        bool PodeRun() const override { return true; }
        bool PodeManutencao() const override { return true; }
};

// Utilizador visitante (Permissões restritas, geralmente apenas visualização)
class Visitante : public User {
    public:
        Visitante(int id, string nome) : User(id, nome) {}
        bool PodeAdicionar() const override { return false; }
        bool PodeRemover() const override { return false; }
        bool PodeListar() const override { return true; } // Apenas listar
        bool PodeRun() const override { return false; }
        bool PodeManutencao() const override { return false; }
};
#endif // USER_H
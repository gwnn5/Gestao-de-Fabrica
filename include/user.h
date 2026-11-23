#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

/**
 * @brief Classe abstrata de utilizador.
 *
 * Cada tipo de utilizador responde de forma diferente às perguntas de
 * permissão. A fábrica consulta-as antes de cada operação (ex.: Add).
 */
class User {
    protected:
        int Id;
        string Nome;
    public:
        User(int id, string nome) : Id(id), Nome(nome) {}
        virtual ~User() {}
        
        // Permissões: virtuais puras, cada tipo de utilizador define as suas
        virtual bool PodeAdicionar() const = 0;
        virtual bool PodeRemover() const = 0;
        virtual bool PodeListar() const = 0;
        virtual bool PodeRun() const = 0;
        virtual bool PodeManutencao() const = 0;
};

/** @brief Pode fazer tudo. */
class Admin : public User {
    public:
        Admin(int id, string nome) : User(id, nome) {}
        bool PodeAdicionar() const override { return true; }
        bool PodeRemover() const override { return true; }
        bool PodeListar() const override { return true; }
        bool PodeRun() const override { return true; }
        bool PodeManutencao() const override { return true; }
};

/** @brief Pode fazer tudo exceto remover. */
class Normal : public User {
    public:
        Normal(int id, string nome) : User(id, nome) {}
        bool PodeAdicionar() const override { return true; }
        bool PodeRemover() const override { return false; }
        bool PodeListar() const override { return true; }
        bool PodeRun() const override { return true; }
        bool PodeManutencao() const override { return true; }
};

/** @brief Só pode listar. */
class Visitante : public User {
    public:
        Visitante(int id, string nome) : User(id, nome) {}
        bool PodeAdicionar() const override { return false; }
        bool PodeRemover() const override { return false; }
        bool PodeListar() const override { return true; }
        bool PodeRun() const override { return false; }
        bool PodeManutencao() const override { return false; }
};
#endif // USER_H
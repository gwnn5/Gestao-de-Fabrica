#include "Fabrica.h"

Fabrica::Fabrica(User *ut)
{
    //ctor
    utilizadorAtual = ut;
}

Fabrica::~Fabrica()
{
    //dtor
}

Motor *Fabrica::Procurar_Motor(int id)
{
    list<Motor *>::iterator it;
    for (it = listaMotores.begin(); it != listaMotores.end(); it++)
    {
        if ((*it)->Get_Id() == id)
            return *it;
    }
    return NULL;   // não encontrou
}

void Fabrica::Avisar_gestor(int _id)
{

}

bool Fabrica::Add(Motor *m)
{
    if (utilizadorAtual->PodeAdicionar()){
        listaMotores.push_back(m);
        m->Atribuir_Fabrica(this);
        return true;
    }
    return false;
}

void Fabrica::Desligar(int id_motor)
{
    Procurar_Motor(id_motor)->Stop();
}


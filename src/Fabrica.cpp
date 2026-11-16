#include "Fabrica.h"

Fabrica::Fabrica(User *ut)
{
    //ctor
    utilizadorAtual = ut;
}

Fabrica::~Fabrica()
{

    list<Motor *>::iterator itM;
    for (itM = listaMotores.begin(); itM != listaMotores.end(); itM++)
        delete *itM;
    listaMotores.clear();

    list<Sensor *>::iterator itS;
    for (itS = listaSensores.begin(); itS != listaSensores.end(); itS++)
        delete *itS;
    listaSensores.clear();
}

Motor *Fabrica::Procurar_Motor(int id)
{
    list<Motor *>::iterator it;
    for (it = listaMotores.begin(); it != listaMotores.end(); it++)
    {
        if ((*it)->Get_Id() == id)
            return *it;
    }
    return NULL;   // n�o encontrou
}

// ==========================================
// Métodos de Gestão (Adicionar)
// ==========================================
bool Fabrica::Add(User *ut) {
    if (utilizadorAtual && utilizadorAtual->PodeAdicionar()) {
        // Lógica futura para gerir lista de utilizadores, se necessário
        return true;
    }
    return false;
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

bool Fabrica::Add(Sensor *s)
{
    if (utilizadorAtual != NULL && utilizadorAtual->PodeAdicionar()){
        listaSensores.push_back(s);
        s->Atribuir_Fabrica(this);
        return true;
    }
    return false;
}

void Fabrica::Desligar(int id_motor)
{
    Motor *m = Procurar_Motor(id_motor);
    if (m != NULL)
        m->Stop();
}

ESTADO_MOTOR Fabrica::Get_Estado(int id_motor)
{
    Motor *m = Procurar_Motor(id_motor);
    if (m != NULL)
        return m->Get_Estado();
    return STOP;   // motor nao existe
}

void Fabrica::Listar(ostream &f)
{
    f << "=== Fabrica: " << Nome << " ===" << endl;
    f << "Horario: " << Hora_abertura.horas << "h - "
      << Hora_encerramento.horas << "h" << endl;

    f << "--- Motores (" << listaMotores.size() << ") ---" << endl;
    list<Motor *>::iterator itM;
    for (itM = listaMotores.begin(); itM != listaMotores.end(); itM++)
        (*itM)->Mostrar(f);

    f << "--- Sensores (" << listaSensores.size() << ") ---" << endl;
    list<Sensor *>::iterator itS;
    for (itS = listaSensores.begin(); itS != listaSensores.end(); itS++)
        (*itS)->Mostrar(f);
}

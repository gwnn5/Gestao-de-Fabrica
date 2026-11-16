#include "Fabrica.h"

// ==========================================
// Construtor e Destrutor
// ==========================================
Fabrica::Fabrica(User *ut) {
    this->utilizadorAtual = ut;
    this->Nome = "";
    this->Hora_abertura.horas = 0;
    this->Hora_encerramento.horas = 0;
}

Fabrica::~Fabrica() {
    // Libertar a memória alocada para os motores
    for (Motor* m : listaMotores) {
        delete m;
    }
    listaMotores.clear();

    // Libertar a memória alocada para os sensores
    for (Sensor* s : listaSensores) {
        delete s;
    }
    listaSensores.clear();
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

bool Fabrica::Add(Motor *m) {
    if (utilizadorAtual && utilizadorAtual->PodeAdicionar()) {
        listaMotores.push_back(m);
        return true;
    }
    return false;
}
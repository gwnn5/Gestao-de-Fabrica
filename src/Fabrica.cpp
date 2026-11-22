#include "Fabrica.h"
#include "uteis.h"
#include "Motor.h"
#include "Sensor.h"
#include <fstream>
#include <iostream>
#include <cstdlib> // Necessário para usar rand() na Manutenção

using namespace std;

// ==============================================================================
// FUNÇÕES AUXILIARES
// ==============================================================================

/**
 * @brief Converte o enumerador ESTADO_MOTOR para uma string reconhecida pelo simulador XML.
 *
 * @param e O estado atual do motor (STOP, START, RUN, AVARIADO).
 * @return string com o texto exato exigido pelas tags do simulador gráfico.
 */
string EstadoParaString(ESTADO_MOTOR e) {
    switch(e) {
        case STOP: return "STOP";
        case START: return "START";
        case RUN: return "RUN";
        case AVARIADO: return "AVARIADO";
        default: return "STOP";
    }
}

/**
 * @brief Converte o enumerador CLASSE_TEMP para uma string de cor reconhecida pelo simulador XML.
 *
 * @param c A classe de temperatura atual do motor (VERDE, AMARELO, VERMELHO).
 * @return string com a cor correspondente para visualização no simulador.
 */
string CorParaString(CLASSE_TEMP c) {
    switch(c) {
        case VERDE: return "VERDE";
        case AMARELO: return "AMARELO";
        case VERMELHO: return "VERMELHO";
        default: return "VERDE";
    }
}

// ==============================================================================
// MÉTODOS DO ELEMENTO B (Gestão da fábrica)
// ==============================================================================

/**
 * @brief Cria a fábrica com valores por omissão (o Load substitui-os pelos do XML).
 * @param ut Utilizador que está a operar o sistema.
 */
Fabrica::Fabrica(User *ut)
{
    utilizadorAtual = ut;
    Nome = "Sem nome";
    Hora_abertura.horas = 8;
    Hora_abertura.minutos = 0;
    Hora_encerramento.horas = 18;
    Hora_encerramento.minutos = 0;
    Vizinhanca = 0;
    Dimensao.x = 0;
    Dimensao.y = 0;
}

/**
 * @brief Liberta a memória de todos os motores e sensores da fábrica.
 */
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

// ---------- Setters (usados pelo Load) ----------
void Fabrica::Set_Nome(string n) { Nome = n; }

void Fabrica::Set_Horas(Hora abertura, Hora encerramento)
{
    Hora_abertura = abertura;
    Hora_encerramento = encerramento;
}

void Fabrica::Set_Vizinhanca(int v) { Vizinhanca = v; }
void Fabrica::Set_Dimensao(Posicao d) { Dimensao = d; }
string Fabrica::Get_Nome() const { return Nome; }

/**
 * @brief Procura um motor pelo ID.
 * @return Apontador para o motor, ou NULL se não existir.
 */
Motor *Fabrica::Procurar_Motor(int id)
{
    list<Motor *>::iterator it;
    for (it = listaMotores.begin(); it != listaMotores.end(); it++)
    {
        if ((*it)->Get_Id() == id)
            return *it;
    }
    return NULL;
}

/**
 * @brief Adiciona um utilizador, se o utilizador atual tiver permissão.
 */
bool Fabrica::Add(User *ut)
{
    if (ut == NULL || utilizadorAtual == NULL || !utilizadorAtual->PodeAdicionar())
        return false;
    listaUsers.push_back(ut);
    return true;
}

/**
 * @brief Adiciona um motor, se o utilizador atual tiver permissão.
 */
bool Fabrica::Add(Motor *m)
{
    if (m == NULL || utilizadorAtual == NULL || !utilizadorAtual->PodeAdicionar())
        return false;
    listaMotores.push_back(m);
    m->Atribuir_Fabrica(this);
    return true;
}

/**
 * @brief Adiciona um sensor, se o utilizador atual tiver permissão.
 */
bool Fabrica::Add(Sensor *s)
{
    if (s == NULL || utilizadorAtual == NULL || !utilizadorAtual->PodeAdicionar())
        return false;
    listaSensores.push_back(s);
    s->Atribuir_Fabrica(this);
    return true;
}

/**
 * @brief Desliga (STOP) o motor com o ID indicado, se existir.
 */
void Fabrica::Desligar(int id_motor)
{
    Motor *m = Procurar_Motor(id_motor);
    if (m != NULL)
        m->Stop();
}

/**
 * @brief Devolve o estado de um motor (STOP se não existir).
 */
ESTADO_MOTOR Fabrica::Get_Estado(int id_motor)
{
    Motor *m = Procurar_Motor(id_motor);
    if (m != NULL)
        return m->Get_Estado();
    return STOP;
}

/**
 * @brief Lista a fábrica: nome, horário, motores e sensores.
 * @param f Stream de saída (por omissão, o ecrã).
 */
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

// ==============================================================================
// MÉTODOS DO ELEMENTO A (Ficheiros de Saída e Manutenção)
// ==============================================================================

/**
 * @brief Gera um relatório em formato XML com o estado atual de todos os dispositivos da fábrica.
 *
 * Este método cria um ficheiro XML compatível com o simulador gráfico fornecido,
 * listando todos os motores e sensores, os seus estados atuais e valores.
 * No final, inclui o consumo total de todos os motores no dia.
 *
 * @param fich_xml O nome ou caminho do ficheiro XML a ser gerado (ex: "Relatorio.xml").
 */
void Fabrica::Relatorio(string fich_xml) {
    ofstream out(fich_xml.c_str());
    if (!out.is_open()) {
        cout << "Erro ao criar o relatorio XML!" << endl;
        return;
    }

    float consumo_total_dia = 0.0f;

    // Início do documento XML com a tag raiz exigida pelo simulador
    out << "<DADOS>\n";

    // 1. Exportação dos dados referentes aos Motores
    out << "\t<MOTORES>\n";
    for (list<Motor *>::iterator itM = listaMotores.begin(); itM != listaMotores.end(); itM++) {
        Motor *m = *itM;
        out << "\t\t<" << m->Get_Tipo() << ">\n";
        out << "\t\t\t<ID>" << m->Get_Id() << "</ID>\n";
        out << "\t\t\t<MARCA>" << m->Get_Marca() << "</MARCA>\n";

        // Tags específicas e obrigatórias para o correto funcionamento do simulador
        out << "\t\t\t<VALOR_TEMP_ATUAL>" << m->Get_Temperatura() << "</VALOR_TEMP_ATUAL>\n";
        out << "\t\t\t<ESTADO_ATUAL>" << EstadoParaString(m->Get_Estado()) << "</ESTADO_ATUAL>\n";
        out << "\t\t\t<ESTADO_COR>" << CorParaString(m->Get_Classe_Temp()) << "</ESTADO_COR>\n";
        out << "\t\t\t<CONSUMO_HORA>" << m->Get_Consumo() << "</CONSUMO_HORA>\n";

        Posicao p = m->Get_Pos();
        out << "\t\t\t<POSICAO>" << p.x << "," << p.y << "</POSICAO>\n";
        out << "\t\t</" << m->Get_Tipo() << ">\n";

        // Acumula o consumo do motor iterado para o cálculo do total diário
        consumo_total_dia += m->Get_Consumo();
    }
    out << "\t</MOTORES>\n";

    // 2. Exportação dos dados referentes aos Sensores
    out << "\t<SENSORES>\n";
    for (list<Sensor *>::iterator itS = listaSensores.begin(); itS != listaSensores.end(); itS++) {
        Sensor *s = *itS;
        string tipo = s->Get_Tipo(); // Devolve a etiqueta XML, ex: "SHUMIDADE"
        out << "\t\t<" << tipo << ">\n";
        out << "\t\t\t<ID>" << s->Get_Id() << "</ID>\n";
        out << "\t\t\t<MARCA>" << s->Get_Marca() << "</MARCA>\n";

        Posicao p = s->Get_Pos();
        out << "\t\t\t<POSICAO>" << p.x << "," << p.y << "</POSICAO>\n";

        // Tag obrigatória de Aviso (adicionado)
        out << "\t\t\t<VALOR_AVISO>" << s->Get_Aviso() << "</VALOR_AVISO>\n";

        // Tag obrigatória para mostrar o valor lido pelo sensor no simulador (usa o método formatado '%')
        out << "\t\t\t<VALOR_ATUAL>" << s->GetValorAtualString() << "</VALOR_ATUAL>\n";
        out << "\t\t</" << tipo << ">\n";
    }
    out << "\t</SENSORES>\n";

    // 3. Resumo do fecho do dia com o consumo total da fábrica
    out << "\t<RESUMO>\n";
    out << "\t\t<CONSUMO_TOTAL_DIA>" << consumo_total_dia << "</CONSUMO_TOTAL_DIA>\n";
    out << "\t</RESUMO>\n";

    out << "</DADOS>\n";

    out.close();
    cout << "Relatorio XML guardado com sucesso: " << fich_xml << endl;
}

/**
 * @brief Gera uma página HTML simples para visualização do estado da fábrica no browser.
 */
void Fabrica::Listagem_HTML(string fich_html) {
    ofstream out(fich_html.c_str());
    if (!out.is_open()) {
        cout << "Erro ao criar o ficheiro HTML!" << endl;
        return;
    }

    out << "<!DOCTYPE html>\n<html>\n<head>\n";
    out << "<title>Estado da Fabrica</title>\n";
    out << "<style>table { border-collapse: collapse; width: 60%; margin-bottom: 20px; } th, td { border: 1px solid black; padding: 8px; text-align: center; } th { background-color: #f2f2f2; }</style>\n";
    out << "</head>\n<body>\n";
    out << "<h1>Relatorio Atual da Fabrica</h1>\n";

    out << "<h2>Motores</h2>\n";
    out << "<table>\n<tr><th>ID</th><th>Marca</th><th>Temperatura</th><th>Estado</th><th>Cor</th></tr>\n";
    for (list<Motor *>::iterator itM = listaMotores.begin(); itM != listaMotores.end(); itM++) {
        Motor *m = *itM;
        out << "<tr>"
            << "<td>" << m->Get_Id() << "</td>"
            << "<td>" << m->Get_Marca() << "</td>"
            << "<td>" << m->Get_Temperatura() << "</td>"
            << "<td>" << EstadoParaString(m->Get_Estado()) << "</td>"
            << "<td>" << CorParaString(m->Get_Classe_Temp()) << "</td>"
            << "</tr>\n";
    }
    out << "</table>\n";

    out << "<h2>Sensores</h2>\n";
    out << "<table>\n<tr><th>ID</th><th>Marca</th><th>Tipo</th><th>Valor Atual</th><th>Em Alerta?</th></tr>\n";
    for (list<Sensor *>::iterator itS = listaSensores.begin(); itS != listaSensores.end(); itS++) {
        Sensor *s = *itS;
        out << "<tr>"
            << "<td>" << s->Get_Id() << "</td>"
            << "<td>" << s->Get_Marca() << "</td>"
            << "<td>" << s->Get_Tipo() << "</td>"
            << "<td>" << s->GetValorAtualString() << "</td>"
            << "<td>" << (s->Em_Alerta() ? "SIM (PERIGO)" : "NAO") << "</td>"
            << "</tr>\n";
    }
    out << "</table>\n";

    out << "</body>\n</html>\n";
    out.close();
    cout << "Listagem HTML gerada com sucesso: " << fich_html << endl;
}

bool Fabrica::Manutencao() {
    bool houve_manutencao = false;

    // 1. Manutenção dos Motores
    for (list<Motor *>::iterator itM = listaMotores.begin(); itM != listaMotores.end(); itM++) {
        Motor *m = *itM;
        // Obter a faixa verde do motor
        Faixa verde = m->Get_Faixa_Verde();

        // Gerar uma temperatura aleatória dentro do intervalo [minimo, maximo] da faixa verde
        float nova_temp = verde.minimo + (rand() % (verde.maximo - verde.minimo + 1));

        // Atualizar a temperatura e estado do motor
        m->Set_Temperatura(nova_temp);
        m->Set_Estado(RUN);
        houve_manutencao = true;
    }

    // 2. Manutenção dos Sensores
    for (list<Sensor *>::iterator itS = listaSensores.begin(); itS != listaSensores.end(); itS++) {
        Sensor *s = *itS;
        // Se o sensor estiver avariado (valor == -1), a manutenção deve repará-lo
        if (s->Get_Valor() == -1) {
            // NOTA: Se quiseres que a reparação funcione a 100%,
            // precisas de garantir que existe um método para repor o valor, ex: s->Set_Valor(0);
            houve_manutencao = true;
        }
    }

    return houve_manutencao;
}

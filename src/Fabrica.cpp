#include "Fabrica.h"
#include "uteis.h"
#include "Motor.h"
#include "Sensor.h"
#include "MotorCombustao.h"
#include "MotorEletrico.h"
#include "MotorInducao.h"
#include "SensorHumidade.h"
#include "SensorLuz.h"
#include "SensorFumo.h"
#include "SensorMissil.h"
#include "SensorTemperatura.h"
#include "SensorFogo.h"
#include "XML.h"
#include <fstream>
#include <iostream>
#include <cstdlib>   // rand(), usado na Manutenção

using namespace std;

// ==============================================================================
// FUNÇÕES AUXILIARES (enums para texto)
// ==============================================================================

// Converte o enumerador ESTADO_MOTOR para uma string reconhecida pelo simulador XML.
// e: O estado atual do motor (STOP, START, RUN, AVARIADO).
// Devolve string com o texto exato exigido pelas tags do simulador gráfico.
string EstadoParaString(ESTADO_MOTOR e) {
    switch(e) {
        case STOP: return "STOP";
        case START: return "START";
        case RUN: return "RUN";
        case AVARIADO: return "AVARIADO";
        default: return "STOP";
    }
}

// Converte o enumerador CLASSE_TEMP para uma string de cor reconhecida pelo simulador XML.
// c: A classe de temperatura atual do motor (VERDE, AMARELO, VERMELHO).
// Devolve string com a cor correspondente para visualização no simulador.
string CorParaString(CLASSE_TEMP c) {
    switch(c) {
        case VERDE: return "VERDE";
        case AMARELO: return "AMARELO";
        case VERMELHO: return "VERMELHO";
        default: return "VERDE";
    }
}

// ==============================================================================
// GESTÃO DA FÁBRICA
// ==============================================================================

// Cria a fábrica com valores por omissão (o Load substitui-os pelos do XML).
// ut: Utilizador que está a operar o sistema.
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

// Liberta a memória de todos os motores e sensores da fábrica.
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

// Procura um motor pelo ID.
// Devolve apontador para o motor, ou NULL se não existir.
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

// Adiciona um utilizador, se o utilizador atual tiver permissão.
bool Fabrica::Add(User *ut)
{
    if (ut == NULL || utilizadorAtual == NULL || !utilizadorAtual->PodeAdicionar())
        return false;
    listaUsers.push_back(ut);
    return true;
}

// Adiciona um motor, se o utilizador atual tiver permissão.
bool Fabrica::Add(Motor *m)
{
    if (m == NULL || utilizadorAtual == NULL || !utilizadorAtual->PodeAdicionar())
        return false;
    listaMotores.push_back(m);
    m->Atribuir_Fabrica(this);
    return true;
}

// Adiciona um sensor, se o utilizador atual tiver permissão.
bool Fabrica::Add(Sensor *s)
{
    if (s == NULL || utilizadorAtual == NULL || !utilizadorAtual->PodeAdicionar())
        return false;
    listaSensores.push_back(s);
    s->Atribuir_Fabrica(this);
    return true;
}

// Desliga (STOP) o motor com o ID indicado, se existir.
void Fabrica::Desligar(int id_motor)
{
    Motor *m = Procurar_Motor(id_motor);
    if (m != NULL)
        m->Stop();
}

// Devolve o estado de um motor (STOP se não existir).
ESTADO_MOTOR Fabrica::Get_Estado(int id_motor)
{
    Motor *m = Procurar_Motor(id_motor);
    if (m != NULL)
        return m->Get_Estado();
    return STOP;
}

// Lista a fábrica: nome, horário, motores e sensores.
// f: Stream de saída (por omissão, o ecrã).
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
// LOAD DO XML
// ==============================================================================

// Lê um par "x,y" de uma tag filha e devolve-o como Posicao.
// no: Nó pai (ex.: um motor).
// tag: Nome da tag (ex.: "POSICAO").
// Devolve a posição lida, ou (0,0) se a tag não existir ou estiver mal escrita.
static Posicao Ler_Posicao(const XMLNode *no, const string &tag)
{
    Posicao p;
    p.x = 0;
    p.y = 0;
    XmlParaPar(no->Texto_De(tag), p.x, p.y);
    return p;
}

// Lê um número inteiro de uma tag filha (aceita "85%").
// Devolve o valor lido, ou 'omissao' se não existir ou for inválido.
static int Ler_Int(const XMLNode *no, const string &tag, int omissao = 0)
{
    int v;
    if (XmlParaInt(no->Texto_De(tag), v))
        return v;
    return omissao;
}

// Lê um número decimal de uma tag filha (aceita "0,5" e "85%").
// Devolve o valor lido, ou 'omissao' se não existir ou for inválido.
static float Ler_Float(const XMLNode *no, const string &tag, float omissao = 0.0f)
{
    float v;
    if (XmlParaFloat(no->Texto_De(tag), v))
        return v;
    return omissao;
}

// Lê as faixas VERDE, AMARELO e VERMELHO de um tipo de motor.
// def: Nó DEFINICOES.
// tipo: Tag do tipo (MCOMBUSTAO, MELETRICO ou MINDUCAO).
// lim: Recebe as três faixas.
// prob: Recebe a probabilidade de avaria desse tipo.
// Devolve false se o tipo não estiver definido no XML.
static bool Ler_Definicao_Motor(const XMLNode *def, const string &tipo, LimitesTemp &lim, float &prob)
{
    const XMLNode *t = def->Procurar(tipo);
    if (t == NULL)
        return false;
    XmlParaPar(t->Texto_De("VERDE"), lim.verde.minimo, lim.verde.maximo);
    XmlParaPar(t->Texto_De("AMARELO"), lim.amarelo.minimo, lim.amarelo.maximo);
    XmlParaPar(t->Texto_De("VERMELHO"), lim.vermelho.minimo, lim.vermelho.maximo);
    prob = Ler_Float(t, "PROB_AVARIA");
    return true;
}

// Converte o texto do XML ("RUN", "START", ...) no enum ESTADO_MOTOR.
static ESTADO_MOTOR Texto_Para_Estado(const string &s)
{
    if (s == "RUN")      return RUN;
    if (s == "START")    return START;
    if (s == "AVARIADO") return AVARIADO;
    return STOP;
}

// Carrega a configuração da fábrica a partir de um ficheiro XML.
// Lê as definições (nome, horário, vizinhança, dimensão e faixas de
// temperatura de cada tipo de motor), cria os motores e os sensores
// e adiciona-os à fábrica com Add().
// ficheiro: Caminho do ficheiro XML.
// Devolve true se o ficheiro foi lido; false se não abriu ou é inválido.
bool Fabrica::Load(const string &ficheiro)
{
    string erro;
    XMLNode *raiz = XMLNode::Carregar(ficheiro, erro);
    if (raiz == NULL)
    {
        cout << "Erro no Load: " << erro << endl;
        return false;
    }

    // ---------- 1. Definições ----------
    LimitesTemp limComb, limElet, limInd;
    float probComb = 0, probElet = 0, probInd = 0;

    const XMLNode *def = raiz->Procurar("DEFINICOES");
    if (def != NULL)
    {
        Set_Nome(def->Texto_De("NOME_EMPRESA"));

        Hora abre, fecha;
        abre.horas = Ler_Int(def, "HORA_INICIO", 8);
        abre.minutos = 0;
        fecha.horas = Ler_Int(def, "HORA_FECHO", 18);
        fecha.minutos = 0;
        Set_Horas(abre, fecha);

        Set_Vizinhanca(Ler_Int(def, "VIZINHANCA_AVISO"));
        Set_Dimensao(Ler_Posicao(def, "DIMENSAO_FABRICA"));

        Ler_Definicao_Motor(def, "MCOMBUSTAO", limComb, probComb);
        Ler_Definicao_Motor(def, "MELETRICO", limElet, probElet);
        Ler_Definicao_Motor(def, "MINDUCAO", limInd, probInd);
    }

    // ---------- 2. Motores ----------
    const XMLNode *mot = raiz->Procurar("MOTORES");
    if (mot != NULL)
    {
        const vector<XMLNode *> &lista = mot->Get_Filhos();
        for (size_t i = 0; i < lista.size(); i++)
        {
            const XMLNode *n = lista[i];
            string tipo = XmlNormaliza(n->Get_Nome());

            int id = Ler_Int(n, "ID");
            string marca = n->Texto_De("MARCA");
            Posicao p = Ler_Posicao(n, "POSICAO");
            float consumo = Ler_Float(n, "CONSUMO_HORA");

            // Temp_Aviso = início da faixa amarela; Temp_Paragem = início da vermelha
            Motor *m = NULL;
            LimitesTemp lim;
            if (tipo == "mcombustao")
            {
                lim = limComb;
                m = new MotorCombustao(id, marca, p, consumo, lim.amarelo.minimo, lim.vermelho.minimo, probComb);
            }
            else if (tipo == "meletrico")
            {
                lim = limElet;
                m = new MotorEletrico(id, marca, p, consumo, lim.amarelo.minimo, lim.vermelho.minimo, probElet);
            }
            else if (tipo == "minducao")
            {
                lim = limInd;
                m = new MotorInducao(id, marca, p, consumo, lim.amarelo.minimo, lim.vermelho.minimo, probInd);
            }
            else
            {
                cout << "Load: tipo de motor desconhecido '" << n->Get_Nome() << "'" << endl;
                continue;
            }

            m->Set_Limites(lim);
            m->Set_Temperatura(Ler_Float(n, "VALOR_TEMP_ATUAL", 20.0f));
            m->Set_Estado(Texto_Para_Estado(n->Texto_De("ESTADO_ATUAL")));

            if (!Add(m))
                delete m;   // sem permissão: não pode ficar perdido em memória
        }
    }

    // ---------- 3. Sensores ----------
    const XMLNode *sen = raiz->Procurar("SENSORES");
    if (sen != NULL)
    {
        const vector<XMLNode *> &lista = sen->Get_Filhos();
        for (size_t i = 0; i < lista.size(); i++)
        {
            const XMLNode *n = lista[i];
            string tipo = XmlNormaliza(n->Get_Nome());

            int id = Ler_Int(n, "ID");
            string marca = n->Texto_De("MARCA");
            Posicao p = Ler_Posicao(n, "POSICAO");
            float prob = Ler_Float(n, "PROB_AVARIA");
            float aviso = Ler_Float(n, "VALOR_AVISO");
            float atual = Ler_Float(n, "VALOR_ATUAL");

            Sensor *s = NULL;
            if (tipo == "shumidade")         s = new SensorHumidade(id, marca, p, prob, aviso, atual);
            else if (tipo == "sluz")         s = new SensorLuz(id, marca, p, prob, aviso, atual);
            else if (tipo == "sfumo")        s = new SensorFumo(id, marca, p, prob, aviso, atual);
            else if (tipo == "smissil")      s = new SensorMissil(id, marca, p, prob, aviso, atual);
            else if (tipo == "stemperatura") s = new SensorTemperatura(id, marca, p, prob, aviso, atual);
            else if (tipo == "sfogo")        s = new SensorFogo(id, marca, p, prob, aviso, atual);
            else
            {
                cout << "Load: tipo de sensor desconhecido '" << n->Get_Nome() << "'" << endl;
                continue;
            }

            if (!Add(s))
                delete s;
        }
    }

    delete raiz;   // apaga a árvore do XML; os motores e sensores ficam na fábrica
    return true;
}


// ==============================================================================
// RELATÓRIOS E MANUTENÇÃO
// ==============================================================================

// Gera um relatório em formato XML com o estado atual de todos os dispositivos da fábrica.
// Este método cria um ficheiro XML compatível com o simulador gráfico fornecido,
// listando todos os motores e sensores, os seus estados atuais e valores.
// No final, inclui o consumo total de todos os motores no dia.
// fich_xml: O nome ou caminho do ficheiro XML a ser gerado (ex: "Relatorio.xml").
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
        string tipo = s->Get_Tipo();   // Etiqueta XML, ex.: "SHUMIDADE"
        out << "\t\t<" << tipo << ">\n";
        out << "\t\t\t<ID>" << s->Get_Id() << "</ID>\n";
        out << "\t\t\t<MARCA>" << s->Get_Marca() << "</MARCA>\n";

        Posicao p = s->Get_Pos();
        out << "\t\t\t<POSICAO>" << p.x << "," << p.y << "</POSICAO>\n";

        // Valor a partir do qual o sensor dispara o aviso
        out << "\t\t\t<VALOR_AVISO>" << s->Get_Aviso() << "</VALOR_AVISO>\n";

        // Valor lido, já formatado (a humidade leva '%', avariado dá "AVARIA")
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

// Gera uma página HTML simples para ver o estado da fábrica no browser.
// Uma tabela para os motores (temperatura, estado e cor) e outra para os
// sensores (valor atual e se estão em alerta).
// fich_html: Nome do ficheiro HTML a gerar.
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

// Manutenção de todos os dispositivos.
// Cada motor volta a uma temperatura aleatória dentro da sua faixa verde
// e fica em RUN.
// Devolve true se interveio em pelo menos um dispositivo.
bool Fabrica::Manutencao() {
    bool houve_manutencao = false;

    // 1. Manutenção dos Motores
    for (list<Motor *>::iterator itM = listaMotores.begin(); itM != listaMotores.end(); itM++) {
        Motor *m = *itM;
        Faixa verde = m->Get_Faixa_Verde();

        // Temperatura aleatória dentro de [minimo, maximo] da faixa verde
        float nova_temp = verde.minimo + (rand() % (verde.maximo - verde.minimo + 1));

        m->Set_Temperatura(nova_temp);
        m->Set_Estado(RUN);
        houve_manutencao = true;
    }

    // 2. Manutenção dos Sensores
    for (list<Sensor *>::iterator itS = listaSensores.begin(); itS != listaSensores.end(); itS++) {
        Sensor *s = *itS;
        // Um sensor avariado (valor -1) deve ser reparado.
        // Ainda não é: falta no Sensor um setter para repor o valor.
        if (s->Get_Valor() == -1) {
            houve_manutencao = true;
        }
    }

    return houve_manutencao;
}

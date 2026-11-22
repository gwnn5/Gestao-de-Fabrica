#include "XML.h"
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <memory>
#include <sstream>

using namespace std;

// Funcoes de texto

string XmlNormaliza(const string& s)
{
    string r;
    for (size_t i = 0; i < s.size(); i++)
    {
        unsigned char c = (unsigned char)s[i];
        if (c != '_' && c != '-' && !isspace(c))
            r += (char)tolower(c);
    }
    return r;
}

static string Trim(const string& s)
{
    size_t ini = s.find_first_not_of(" \t\r\n");
    if (ini == string::npos)
        return "";
    return s.substr(ini, s.find_last_not_of(" \t\r\n") - ini + 1);
}

string XmlTrim(const string& s)
{
    return Trim(s);
}

// "85%" -> "85"
static string SemPercentagem(string s)
{
    s = Trim(s);
    if (!s.empty() && s[s.size() - 1] == '%')
        s.erase(s.size() - 1);
    return s;
}

// aceita % no final
bool XmlParaInt(const string& s, int& valor)
{
    string t = SemPercentagem(s);
    char* fim;
    long v = strtol(t.c_str(), &fim, 10);
    if (fim == t.c_str())
        return false;                       // nao leu nenhum numero
    while (isspace((unsigned char)*fim))
        fim++;
    if (*fim != '\0')
        return false;                       // sobrou lixo ("8x")
    valor = (int)v;
    return true;
}

//aceita virgula
bool XmlParaFloat(const string& s, float& valor)
{
    string t = SemPercentagem(s);
    for (size_t i = 0; i < t.size(); i++)   // converte virgula decimal -> ponto
        if (t[i] == ',')
            t[i] = '.';
    char* fim;
    double v = strtod(t.c_str(), &fim);
    if (fim == t.c_str())
        return false;
    while (isspace((unsigned char)*fim))
        fim++;
    if (*fim != '\0')
        return false;
    valor = (float)v;
    return true;
}

// "0,80" -> a=0, b=80
bool XmlParaPar(const string& s, int& a, int& b)
{
    size_t p = s.find(',');
    int x, y;
    if (p == string::npos || !XmlParaInt(s.substr(0, p), x) || !XmlParaInt(s.substr(p + 1), y))
        return false;
    a = x;
    b = y;
    return true;
}

// XMLNode

XMLNode::XMLNode(const string& n) : nome(n)
{
}

XMLNode::~XMLNode()
{
    for (size_t i = 0; i < filhos.size(); i++)
        delete filhos[i];
}

const XMLNode* XMLNode::Procurar(const string& n) const
{
    string alvo = XmlNormaliza(n);
    for (size_t i = 0; i < filhos.size(); i++)
        if (XmlNormaliza(filhos[i]->nome) == alvo)
            return filhos[i];
    return NULL;
}

vector<const XMLNode*> XMLNode::Procurar_Todos(const string& n) const
{
    vector<const XMLNode*> r;
    string alvo = XmlNormaliza(n);
    for (size_t i = 0; i < filhos.size(); i++)
        if (XmlNormaliza(filhos[i]->nome) == alvo)
            r.push_back(filhos[i]);
    return r;
}

string XMLNode::Texto_De(const string& n) const
{
    const XMLNode* f = Procurar(n);
    if (f == NULL)
        return "";
    return f->texto;
}

// Parser: le <A>texto</A>, filhos aninhados, comentarios, <?xml ... ?> e BOM.
// 't' e o texto todo e 'i' a posicao atual (avanca ao longo da leitura).

// Salta espacos, comentarios <!-- --> e <?xml ... ?>
static void Saltar(const string& t, size_t& i)
{
    for (;;)
    {
        while (i < t.size() && isspace((unsigned char)t[i]))
            i++;
        const char* fim;
        if (t.compare(i, 4, "<!--") == 0)
            fim = "-->";
        else if (t.compare(i, 2, "<?") == 0)
            fim = "?>";
        else
            return;
        size_t p = t.find(fim, i);
        i = (p == string::npos) ? t.size() : p + strlen(fim);
    }
}

static string Ler_Nome(const string& t, size_t& i)
{
    size_t ini = i;
    while (i < t.size() && !isspace((unsigned char)t[i]) && t[i] != '>' && t[i] != '/')
        i++;
    return t.substr(ini, i - ini);
}

// Le um elemento completo (t[i] == '<'). Devolve NULL se estiver mal formado.
static XMLNode* Ler_Elemento(const string& t, size_t& i)
{
    i++;   // '<'
    string nome = Ler_Nome(t, i);
    if (nome.empty())
        return NULL;
    size_t gt = t.find('>', i);           // ignora atributos ate ao '>'
    if (gt == string::npos)
        return NULL;
    bool vazio = (gt > i && t[gt - 1] == '/');   // <TAG/>
    i = gt + 1;
    if (vazio)
        return new XMLNode(nome);

    unique_ptr<XMLNode> no(new XMLNode(nome));
    string texto;
    for (;;)
    {
        size_t p = t.find('<', i);
        if (p == string::npos)
            return NULL;                    // o elemento nunca fechou
        texto += t.substr(i, p - i);
        i = p;

        if (t.compare(i, 2, "</") == 0)     // fecho: tem de ser o mesmo nome
        {
            i += 2;
            string fecho = Ler_Nome(t, i);
            while (i < t.size() && isspace((unsigned char)t[i]))
                i++;                        // aceita "</NOME >"
            if (fecho != nome || i >= t.size() || t[i] != '>')
                return NULL;
            i++;
            no->Set_Texto(Trim(texto));
            return no.release();
        }

        size_t antes = i;
        Saltar(t, i);
        if (i != antes)
            continue;                       // era um comentario

        XMLNode* filho = Ler_Elemento(t, i);
        if (filho == NULL)
            return NULL;
        no->Adicionar(filho);
    }
}

XMLNode* XMLNode::Carregar(const string& ficheiro, string& erro)
{
    ifstream in(ficheiro.c_str(), ios::binary);
    if (!in)
    {
        erro = "nao foi possivel abrir '" + ficheiro + "'";
        return NULL;
    }
    ostringstream os;
    os << in.rdbuf();
    return Interpretar(os.str(), erro);
}

XMLNode* XMLNode::Interpretar(const string& t, string& erro)
{
    size_t i = (t.compare(0, 3, "\xEF\xBB\xBF") == 0) ? 3 : 0;   // BOM UTF-8
    Saltar(t, i);

    XMLNode* raiz = NULL;
    if (i < t.size() && t[i] == '<')
    {
        raiz = Ler_Elemento(t, i);
        if (raiz != NULL)
        {
            Saltar(t, i);
            if (i < t.size())               // sobrou conteudo depois da raiz
            {
                delete raiz;
                raiz = NULL;
            }
        }
    }

    if (raiz == NULL)
    {
        int linha = 1;
        for (size_t k = 0; k < i; k++)
            if (t[k] == '\n')
                linha++;
        erro = "XML invalido (linha " + to_string(linha) + ")";
    }
    return raiz;
}

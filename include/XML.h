#ifndef XML_H
#define XML_H

// Leitor de XML simples: transforma o ficheiro numa arvore de XMLNode
// e converte os textos lidos em numeros.
#include <string>
#include <vector>

class XMLNode;

std::string XmlNormaliza(const std::string& s); // Normaliza um nome para comparar tags: minusculas, sem espacos, "_" nem "-"

std::string XmlTrim(const std::string& s); // Remove espacos, tabs e quebras de linha do inicio e do fim. 

bool XmlParaInt(const std::string& s, int& valor); // Aceita um '%' no fim ("85%" -> 85)
bool XmlParaFloat(const std::string& s, float& valor); // Aceita virgula decimal ("0,5" -> 0.5)
bool XmlParaPar(const std::string& s, int& a, int& b); // Separa na virgula ("0, 80" -> 0 e 80)

/* No de uma arvore XML. Os atributos sao ignorados.
   A procura de filhos usa XmlNormaliza, logo "PROB_AVARIA" == "prob-avaria". */
class XMLNode
{
    public:
        explicit XMLNode(const std::string& nome = "");
        ~XMLNode();   // apaga os filhos

        const std::string& Get_Nome() const { return nome; }
        const std::string& Get_Texto() const { return texto; }
        const std::vector<XMLNode*>& Get_Filhos() const { return filhos; }

        const XMLNode* Procurar(const std::string& nome) const; // Primeiro filho com esse nome (NULL se nao existir). 

        std::vector<const XMLNode*> Procurar_Todos(const std::string& nome) const;  // Todos os filhos com esse nome. 

        std::string Texto_De(const std::string& nome) const; // Texto do primeiro filho com esse nome ("" se nao existir). 

        static XMLNode* Carregar(const std::string& ficheiro, std::string& erro); // Le o ficheiro e devolve a raiz da arvore (a apagar por quem chama), ou NULL com a explicacao em 'erro'
        static XMLNode* Interpretar(const std::string& conteudo, std::string& erro);  // O mesmo, mas a partir de um texto ja em memoria

        void Set_Texto(const std::string& t) { texto = t; } // Usados pelo parser enquanto constroi a arvore
        void Adicionar(XMLNode* filho) { filhos.push_back(filho); }

    private:
        XMLNode(const XMLNode&);              // sem copia (donos dos filhos)
        XMLNode& operator=(const XMLNode&);

        std::string nome;
        std::string texto;
        std::vector<XMLNode*> filhos;
};

#endif // XML_H

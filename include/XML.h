#ifndef XML_H
#define XML_H
#include <string>
#include <vector>

class XMLNode;

std::string XmlNormaliza(const std::string& s); // Normaliza um nome 

std::string XmlTrim(const std::string& s); // Remove espacos, tabs e quebras de linha do inicio e do fim. 

bool XmlParaInt(const std::string& s, int& valor); //aceitam um '%' no fim
bool XmlParaFloat(const std::string& s, float& valor); //aceita virgula decimal
bool XmlParaPar(const std::string& s, int& a, int& b); //separa na virgula

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

        static XMLNode* Carregar(const std::string& ficheiro, std::string& erro); // Le e interpreta um ficheiro / um texto. 
        static XMLNode* Interpretar(const std::string& conteudo, std::string& erro);  //Devolve o na raiz (a apagar por quem o chama) ou NULL, no caso de 'erro' diz o que correu mal. 

        void Set_Texto(const std::string& t) { texto = t; } // usados pelo parser ( classe Interprete)
        void Adicionar(XMLNode* filho) { filhos.push_back(filho); }

    private:
        XMLNode(const XMLNode&);              // sem copia (donos dos filhos)
        XMLNode& operator=(const XMLNode&);

        std::string nome;
        std::string texto;
        std::vector<XMLNode*> filhos;
};

#endif // XML_H

#include <iostream>
#include "Fabrica.h"
#include "User.h"

using namespace std;

int main()
{
    // O Load usa Add, por isso o utilizador tem de ter permissão para adicionar
    Admin *admin = new Admin(1, "admin");
    Fabrica *fab = new Fabrica(admin);

    if (fab->Load("ExemploParaSimuladorXML.xml"))
        fab->Listar();
    else
        cout << "Nao foi possivel carregar a fabrica." << endl;

    delete fab;     // Apaga também os motores e os sensores
    delete admin;   // A fábrica não apaga os utilizadores
    return 0;
}

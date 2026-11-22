#include <iostream>
#include "Fabrica.h"
#include "User.h"

using namespace std;

int main()
{
    Admin *admin = new Admin(1, "admin");
    Fabrica *fab = new Fabrica(admin);

    if (fab->Load("ExemploParaSimuladorXML.xml"))
        fab->Listar();
    else
        cout << "Nao foi possivel carregar a fabrica." << endl;

    delete fab;     // apaga motores e sensores
    delete admin;
    return 0;
}

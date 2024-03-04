#include <iostream>
#include <GuilleElArquitecto.h>
#include <ErrorInformant.h>
int main()
{
    //Primer argumento, el nombre del aviso.
    //Segundo argumento la descripcion
    //Tercer argumento el tipo de aviso
    //Ultimo argumento las opciones
    //Devuelve un entero que determina que opcion ha seleccionado el usuario
    cout << ErrorInf().showErrorMessageBox("test", "do", EI_WARNING, EI_W_RETRY) << endl;
    std::cout << "Hello World!\n";
}


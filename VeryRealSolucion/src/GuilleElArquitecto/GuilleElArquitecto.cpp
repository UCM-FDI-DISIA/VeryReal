// GuilleElArquitecto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Entity.h"
#include "Component.h"
int main()
{
    std::cout << "Hello World!\n";
    Entity* ent = new Entity();
    Component* c=ent->AddComponent<Component>(PACEVON);
    Component* c1 = ent->AddComponent<Component>(SHEILON);
    Component* c2 = ent->AddComponent<Component>(CISCON);
    Component* c3 = ent->AddComponent<Component>(CRISTININI);
    while (true) {
        ent->Update();
        ent->GetComponent<Component>(PACEVON)->SetActive(false);
        ent->GetComponent<Component>(SHEILON)->SetActive(false);
        ent->GetComponent<Component>(CISCON)->SetActive(false);
    }
    std::cout << "Hello World!\n";
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln

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

//SCENE MANAGER
//Update() {
//	//pdriamos tener 2 escenas activas
//	for (autol: lista) {
//		if(l->si estas activa->update)
//	}
//}
//
//update() {
//	//no podriamos tener 2 a la vez
//	update->pila.top();
//
//	insertar por alante pausa, insertar el juego
//}
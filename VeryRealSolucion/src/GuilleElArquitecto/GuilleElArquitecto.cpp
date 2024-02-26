// GuilleElArquitecto.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "Entity.h"
#include "Component.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
using namespace std;
int main()
{
    std::cout << "Hello World!\n";
   /* Entity* ent = new Entity();
    Component* c=ent->AddComponent<Component>(PACEVON);
    Component* c1 = ent->AddComponent<Component>(SHEILON);
    Component* c2 = ent->AddComponent<Component>(CISCON);
    Component* c3 = ent->AddComponent<Component>(CRISTININI);
    while (true) {
        ent->Update();
        ent->GetComponent<Component>(PACEVON)->SetActive(false);
        ent->GetComponent<Component>(SHEILON)->SetActive(false);
        ent->GetComponent<Component>(CISCON)->SetActive(false);
    }*/

    Vector2 Vec2a = Vector2();
    Vector2 Vec2b = Vector2(5, 5);
    Vector2 Vec2c = Vector2(Vec2b);
    Vector2 Vec2d = Vector2(Vector2(10,10));

    cout << Vec2a << " " << Vec2b << " " << Vec2c << " " << Vec2d << " " << '\n';

    Vector3 Vec3a = Vector3();
    Vector3 Vec3b = Vector3(5, 5,5);
    Vector3 Vec3d = Vector3(Vector3(-10, -10,-10));

    cout << Vec3a << " " << Vec3b << " " <<" " << Vec3d << " " << '\n';

    Vec3a =Vec3b+Vec3d;
 
    Vec3b = Vec3b / 2;

    cout << (Vec3b == Vec3d) << endl;
    
    cout << Vec3d.Magnitude() << endl;
    cout << Vec3d.Normalize() << endl;

   cout << Vec3a << " " << Vec3b << " " << " " << Vec3d << " " << '\n';
    

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
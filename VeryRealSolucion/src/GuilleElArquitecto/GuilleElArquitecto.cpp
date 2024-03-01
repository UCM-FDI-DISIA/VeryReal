//HECHO POR: SHEILA JULVEZ Y PABLO CERRADA
#include "SceneManager.h"
#include <iostream>
using namespace std;
int main()
{
	//SceneManager* a = static_cast<SceneManager*>(SceneManager::Instance());
	SceneManager::Instance()->AddScene("hOLA");
	SceneManager::Instance()->AddScene("Adios");
	cout << "Hello world!";
}
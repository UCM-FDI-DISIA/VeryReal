// LuaLuengo_test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <Scene.h>
#include <SceneManager.h>
#include <Entity.h>
#include <Creator.h>
#include <TransformComponent.h>
#include <ScriptManager.h>
#include "CreatorTransformComponent.h"



int main()
{
    VeryReal::Creator::Instance()->AddCreator("Transform", new VeryReal::CreatorTransformComponent());
    VeryReal::ScriptManager::Instance()->Init("Prefabs");
    VeryReal::ScriptManager::Instance()->ReadPrefabs();
}

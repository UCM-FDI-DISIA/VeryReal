// LuaLuengo_test.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
//#include "ScriptManager.h"
//#include <Map.h>
#include <Scene.h>
#include <SceneManager.h>
#include <Entity.h>
#include <Creator.h>
#include <TransformComponent.h>
#include <ScriptManager.h>
#include "Creator.h"



int main()
{
    VeryReal::Creator::Instance()->AddCreator("Transform", new VeryReal::CreatorTransformComponent());
    ScriptManager::Instance()->Init("PlayScene");
    SM().Test("PlayScene");
}

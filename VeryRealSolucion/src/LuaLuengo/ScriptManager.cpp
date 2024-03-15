extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "ScriptManager.h"
#include <lua.hpp>
#include <LuaBridge.h>
#include <Map.h>
#include <Scene.h>
#include <SceneManager.h>
#include <Entity.h>
#include <Creator.h>
#include <TransformComponent.h>
#include <iostream>
//#include <sol>

using namespace VeryReal;
ScriptManager::ScriptManager()
{
	lua_state = luaL_newstate();

	luaL_openlibs(lua_state);
}

ScriptManager::~ScriptManager()
{
	lua_close(lua_state);
}
	

void ScriptManager::Error(int status)
{
	if (status == 0) {
		return;
	}

	std::cerr << "[LUA ERROR] " << lua_tostring(lua_state, -1) << std::endl;

	lua_pop(lua_state, 1);
}


void ScriptManager::Init(std::string p)
{
	std::string a = "../../bin/LuaFiles/" + p + ".lua";
	int script_status = luaL_dofile(lua_state, a.c_str());		//TEMPORAL!
	Error(script_status);


}

void ScriptManager::TestScene() {
	Scene* scn = SceneManager::Instance()->AddScene("luaTest"); // Creación de la escena(lleva el nombre del archivo .lua)
	std::cout << "TestScene" << "\n";
}

void ScriptManager::Test(std::string namescene)
{
	VeryReal::Scene* scene = VeryReal::SceneManager::Instance()->AddScene(namescene); // Creación de la escena(lleva el nombre del archivo .lua)
	std::cout << "Nombre de la escena: " << namescene << std::endl;

	std::string ent = "Entities";
	luabridge::LuaRef entities = luabridge::getGlobal(lua_state, ent.c_str()); // Referencia a la primera tabla

	if (entities.isTable()) {
		for (int i = 1; i <= entities.length(); ++i) { // Recorremos la tabla de entidades
			luabridge::LuaRef entity = entities[i];

			if (entity.isTable()) {
				std::string nameentity = entity["name"].tostring(); // DUDA: unsafe_cast
				std::cout << "Nombre de la entidad: " << nameentity << std::endl;
				VeryReal::Entity* e = scene->AddEntity(nameentity); // Añadiendo entidades
				luabridge::LuaRef components = entity["components"];

				if (components.isTable()) {
					for (int j = 1; j <= components.length(); ++j) { // Recorremos la tabla interior(componentes)
						luabridge::LuaRef component = components[j];
						
						if (component.isTable()) {
							std::string namecomponent = component["name"].tostring();
							std::cout << "Nombre del componente: " << namecomponent << std::endl;
						
							if (VeryReal::Creator::Instance()->GetCreator(namecomponent) != nullptr) {
								luabridge::LuaRef parameters = component["parameters"];
								if (parameters.isTable()) {
									while (lua_next(parameters, 0) != 0) {
										std::string key = lua_tostring(parameters, -2);
										std::string val = lua_tostring(parameters, -1);
										std::cout << "Clave: " << key << ", Valor: " << val << std::endl;
										//VeryReal::Creator::Instance()->GetCreator(namecomponent)->AddParameter(key, val);
										lua_pop(component, 1);
									}
								}
								else {} //Error
								
								VeryReal::Component* c = e->AddComponent(namecomponent);
								
								std::cout << VeryReal::SceneManager::Instance()->GetScene("PlayScene")->GetEntity(nameentity)->HasComponent(namecomponent) << "\n";

								
							}
							else {//ERROR
							}
							
						}
						
						
					}
					std::cout << std::endl;
				}
			}
		}
	}
	std::cout << "Test" << "\n";
}


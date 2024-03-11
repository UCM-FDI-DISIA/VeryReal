#include "ScriptManager.h"
#include <lua.hpp>
#include <LuaBridge.h>
#include <Map.h>
#include <Scene.h>
#include <SceneManager.h>
#include <Entity.h>
#include <Creator.h>
#include <CreatorTransformComponent.h>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

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

	cerr << "[LUA ERROR] " << lua_tostring(lua_state, -1) << endl;

	lua_pop(lua_state, 1);
}


void ScriptManager::Init()
{
	int script_status = luaL_dofile(lua_state, "luaTest.lua");

	Error(script_status);
}

void ScriptManager::Test()
{
	VeryReal::Scene* scn = VeryReal::SceneManager::Instance()->AddScene("luaTest"); // Creación de la escena(lleva el nombre del archivo .lua)

	string ent = "Entities";
	luabridge::LuaRef entities = luabridge::getGlobal(lua_state, ent.c_str()); // Referencia a la primera tabla

	if (entities.isTable()) {
		for (int i = 1; i <= entities.length(); ++i) { // Recorremos la tabla de entidades
			luabridge::LuaRef entity = entities[i];
			VeryReal::Entity* e = scn->AddEntity(entity.tostring()); // Añadiendo entidades
			if (entity.isTable()) {
				string id = entity["id"].tostring(); // DUDA: unsafe_cast
				cout << "Nombre de la entidad: " << id << endl;
				luabridge::LuaRef components = entity["Components"];
				if (components.isTable()) {
					for (int j = 1; j <= components.length(); ++j) { // Recorremos la tabla interior(componentes)
						luabridge::LuaRef component = components[j];
						VeryReal::Creator::Instance()->AddCreator(component.tostring(), new VeryReal::CreatorTransformComponent()); // Ver como generalizar esto
						VeryReal::Component* c = e->AddComponent(component.tostring()); // Añadiendo componentes
						if (component.isTable()) {
							string name = component["name"].tostring();
							cout << "Nombre del componente: " << name << endl;
							cout << VeryReal::SceneManager::Instance()->GetScene("luaTest")->GetEntity(entity.tostring())->HasComponent(component.tostring()) << "\n";
						}
					}
					cout << endl;
				}
			}
		}
	}
}

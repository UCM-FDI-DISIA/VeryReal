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
									parameters.push(lua_state);  
									lua_pushnil(lua_state);     
									while (lua_next(lua_state, -2)) { 									
										std::string paramName = lua_tostring(lua_state, -2);										
										if (lua_istable(lua_state, -3)) {										
											int length = luaL_len(lua_state, -1);
											std::string key;
											std::vector<int> values;
											for (int k = 1; k <= length; ++k) {												
												lua_rawgeti(lua_state, -1, k);
												key = lua_tostring(parameters, -3);
												
												if (lua_isnumber(lua_state, -1)) {												
													int value = lua_tonumber(lua_state, -1);
													values.push_back(value);													
												}
												else {													
													std::cerr << "Error: El valor en la posición " << i << " no es un número" << std::endl;
												}																																				
												lua_pop(lua_state, 1);																							
											}	
											std::cout << "Key: " << key << std::endl;
											for (int i = 0; i < values.size(); i++) {
												
												std::cout << values[i] << ", ";
											}
											if (length == 2) {
												Vector2 v;
												v.SetX(values[0]);
												v.SetY(values[1]);												
												VeryReal::Creator::Instance()->GetCreator(namecomponent)->AddParameter(key, v);
											}
											else if (length == 3) {
												Vector3 v;
												v.SetX(values[0]);
												v.SetY(values[1]);
												v.SetZ(values[2]);
												VeryReal::Creator::Instance()->GetCreator(namecomponent)->AddParameter(key, v);
											}
											else if (length == 4) {
												Vector4 v;
												v.SetG(values[0]);
												v.SetR(values[1]);
												v.SetB(values[2]);
												v.SetA(values[3]);
												VeryReal::Creator::Instance()->GetCreator(namecomponent)->AddParameter(key, v);
											}

											std::cout << std::endl;
											key = "";
											values.clear();
										}
										else {											
											std::cerr << "Error: El valor para el parámetro '" << paramName << "' no es una tabla" << std::endl;
										}									
										lua_pop(lua_state, 1);
									}
									lua_pop(lua_state, 1);  
								}
								else {
									std::cerr << "Error: parameters no es una tabla" << std::endl;
								}

								//else {} //Error

								VeryReal::Component* c = e->AddComponent(namecomponent);	
								std::cout << "Tiene componente? [1=SI, 0 = NO] :" << VeryReal::SceneManager::Instance()->GetScene("PlayScene")->GetEntity(nameentity)->HasComponent(namecomponent) << "\n";
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
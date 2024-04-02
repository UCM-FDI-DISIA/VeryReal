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
	std::string a = "../../bin/LuaFiles/" + p + ".lua"; // TEMPORAL!
	int script_status = luaL_dofile(lua_state, a.c_str());		
	Error(script_status);
}

void ScriptManager::ReadScene(std::string namescene)
{
	VeryReal::Scene* scene = VeryReal::SceneManager::Instance()->AddScene(namescene,false); // Creaci�n de la escena(lleva el nombre del archivo .lua)
	std::cout << "Nombre de la escena: " << namescene << std::endl;

	std::string ent = "Entities";
	luabridge::LuaRef entities = luabridge::getGlobal(lua_state, ent.c_str()); // Referencia a la primera tabla

	if (entities.isTable()) {
		for (int i = 1; i <= entities.length(); ++i) { // Recorremos la tabla de entidades
			luabridge::LuaRef entity = entities[i];
			if (entity.isTable()) {
				std::string entityname = entity["name"].tostring(); 
				std::cout << "Nombre de la entidad: " << entityname << std::endl;
				VeryReal::Entity* e = scene->AddEntity(entityname); // A�adiendo entidades
				luabridge::LuaRef components = entity["components"];
				if (components.isTable()) {
					for (int j = 1; j <= components.length(); ++j) { // Recorremos la tabla interior(componentes)
						luabridge::LuaRef component = components[j];					
						if (component.isTable()) {
							std::string componentname = component["name"].tostring();
							std::cout << "Nombre del componente: " << componentname << std::endl;
						
							if (VeryReal::Creator::Instance()->GetCreator(componentname) != nullptr) {
								luabridge::LuaRef parameters = component["parameters"];
								if (parameters.isTable()) {									
									parameters.push(lua_state); // Insertamos la tabla a la pila 
									lua_pushnil(lua_state);   
									while (lua_next(lua_state, -2)) { 																																							
										ReadParams(parameters, componentname); // Llamada a la lectura de par�metros de un componente
										lua_pop(lua_state, 1); // Sacamos el valor actual de la pila
									}
									lua_pop(lua_state, 1); // Sacamos la tabla de par�metros de la pila
								}
								else {
									std::cerr << "Error: parameters no es una tabla" << std::endl;
								}
								VeryReal::Component* c = e->AddComponent(componentname); // Comentar para hacer pruebas con otros tipos de datos
								std::cout << "Tiene componente?[1=SI, 0=NO]: " << VeryReal::SceneManager::Instance()->GetScene("PlayScene")->GetEntity(entityname)->HasComponent(componentname) << "\n";
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



void ScriptManager::ReadParams(luabridge::LuaRef params, std::string comp)
{
	std::string paramName = lua_tostring(lua_state, -2);
    std::string key;
    if (lua_isnumber(lua_state, -1)) {   // Comprobamos si el valor es un n�mero
            key = lua_tostring(params, -2);
            int value;
            value = (int)lua_tonumber(lua_state, -1);
            std::cout << key + ": " << value << std::endl;
            VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, value);
    }
    else if (lua_isstring(lua_state, -1)) {   // Comprobamos si el valor es un string
            std::string key;
            key = lua_tostring(params, -2);
            std::string value;
            value = lua_tostring(lua_state, -1);
            std::cout << key + ": " << value << std::endl;
            VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, value);
    }
    else if (lua_isboolean(lua_state, -1)) {   // Comprobamos si el valor es un booleano
            key = lua_tostring(params, -2);
            bool value;
            value = lua_toboolean(lua_state, -1);
            std::cout << key + ": " << value << std::endl;
            VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, value);
    }
    else {   // En otro caso estamos ante un vector(tabla en lua)
        int length = (int) luaL_len(lua_state, -1);
        std::string key;
        std::vector<int> values;   // Vector donde iremos almacenando los valores que se meter�n al vector
        for (int k = 1; k <= length; ++k) {
                lua_rawgeti(lua_state, -1, k);   // Obtenemos el elemento en la posici�n k
                key = lua_tostring(params, -3);
                if (lua_isnumber(lua_state, -1)) {
                                int value = (int)lua_tonumber(lua_state, -1);
                                values.push_back(value);
                }
                lua_pop(lua_state, 1);   // Sacamos el valor actual de la pila
        }
        std::cout << "Key: " << key << std::endl;
        std::cout << "( ";
        for (int i = 0; i < values.size(); i++) {
                std::cout << values [i] << " ";
        }
        std::cout << ")";
        if (length == 2) {   // Vector2
                Vector2 v;
                v.SetX((float)values [0]);
                v.SetY((float)values [1]);
                VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, v);
        }
        else if (length == 3) {   // Vector3
                Vector3 v;
                v.SetX((float)values [0]);
                v.SetY((float)values [1]);
                v.SetZ((float)values [2]);
                VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, v);
        }
        else if (length == 4) {   // Vector4
                Vector4 v;
                v.SetG((float)values [0]);
                v.SetR((float)values [1]);
                v.SetB((float)values [2]);
                v.SetA((float)values [3]);
                VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, v);
        }
        std::cout << std::endl;
        key = "";
        values.clear();
    }
}
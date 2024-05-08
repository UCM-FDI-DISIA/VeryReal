/* extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}*/
#include "ScriptManager.h"
#include <lua.hpp>
//#include <LuaBridge.h>
#include <Scene.h>
#include <SceneManager.h>
#include <Entity.h>
#include <Creator.h>
#include <TransformComponent.h>
#include <iostream>
using namespace VeryReal;

ScriptManager::~ScriptManager()
{
	lua_close(lua_state);
}
	
std::pair<bool, std::string> ScriptManager::Error(int status) {
	if (status == 0) {
        return {true, "The .lua file was loaded"};
	}
    
    std::string message = "[LUA ERROR]" + *(lua_tostring(lua_state, -1)); 
	lua_pop(lua_state, 1);
    return {false, message};
}


void ScriptManager::InitManager()
{  
    lua_state = luaL_newstate();
    luaL_openlibs(lua_state);
	
}
std::pair<bool, std::string> ScriptManager::NewScene(std::string p) {
    /*std::string a = "LuaFiles/" + p + ".lua";*/   // Esta ruta accede a la carpeta bin/LuaFiles del juego
    //DE MOMENTO LO DEJO AS� POR COMODIDAD PARA TERMINAR EL LUA DE  LOS JUEGOS, LUEGO SE CAMBIA A LA LINEA DE ARRIBA
    std::string a = "../../../bin/LuaFiles/" + p + ".lua";
    int script_status = luaL_dofile(lua_state, a.c_str());
    return Error(script_status);
}

 std::pair<bool, std::string> ScriptManager::ReadScene(std::string namescene, bool active) {
    VeryReal::Scene* scene =
        VeryReal::SceneManager::Instance()->AddScene(namescene, active);   // Creaci�n de la escena(lleva el nombre del archivo .lua)
    auto loadedScene = NewScene(namescene);
    if (!loadedScene.first) return loadedScene;
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
								    return {false, "There was no parameters table for " + componentname + "in the Entity named" + entityname};
								}
								auto addedComponent =  e->AddComponent(componentname, j); // Comentar para hacer pruebas con otros tipos de datos       
                                if (!addedComponent.first)
                                    return addedComponent;
							}
                            else 
                            {
                                return {false, "The component " + componentname + " was specified but there is no creator releated to it"};
                            }
						}
					}      
					std::cout << std::endl;
				}
			}
		}
    }
    else 
    {
        return {false, "There was no Entities table in the .lua file"};
    }
    return {true, "The scene was read without any problem"};
 }



void ScriptManager::ReadParams(luabridge::LuaRef params, std::string comp)
{
	std::string paramName = lua_tostring(lua_state, -2);
    std::string key;
    if (lua_isinteger(lua_state, -1)) {   // Comprobamos si el valor es un entero
        key = lua_tostring(params, -2);
        int value;
        value = (int)lua_tointeger(lua_state, -1);
        std::cout << key + ": " << value << std::endl;
        VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, value);
    }
    else if (lua_isnumber(lua_state, -1)) {   // Comprobamos si el valor es un float
        key = lua_tostring(params, -2);
        float value;
        value = (float)lua_tonumber(lua_state, -1);
        std::cout << key + ": " << value << std::endl;
        VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, value);
    }
    else if (lua_isstring(lua_state, -1)) { // Comprobamos si el valor es un string
        std::string key;
        key = lua_tostring(params, -2);
        std::string value;
        value = lua_tostring(lua_state, -1);     
        std::cout << key + ": " << value << std::endl;
        VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, value);
    }
    else if (lua_isboolean(lua_state, -1)) { // Comprobamos si el valor es un booleano
        key = lua_tostring(params, -2);
        bool value;
        value = lua_toboolean(lua_state, -1);
        std::cout << key + ": " << value << std::endl;
        VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, value);
    }
    else { // En otro caso estamos ante un vector(tabla en lua)
        int length = (int) luaL_len(lua_state, -1);
        std::string key;
        std::vector<float> values; // Vector donde iremos almacenando los valores que se meter�n al vector
        for (int k = 1; k <= length; ++k) {
            lua_rawgeti(lua_state, -1, k); // Obtenemos el elemento en la posici�n k
            key = lua_tostring(params, -3);
            if (lua_isnumber(lua_state, -1)) {
                float value = (float)lua_tonumber(lua_state, -1);
                values.push_back(value);
            }
            lua_pop(lua_state, 1); // Sacamos el valor actual de la pila
        }  
        std::cout << "Key: " << key << std::endl;
        std::cout << "( ";
        for (int i = 0; i < values.size(); i++) {
            std::cout << values [i] << " ";
        }
        std::cout << ")";
        if (length == 2) { // Vector2
            Vector2 v;
            v.SetX((float)values [0]);
            v.SetY((float)values [1]);
            VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, v);
        }
        else if (length == 3) { // Vector3
            Vector3 v;
            v.SetX((float)values [0]);
            v.SetY((float)values [1]);
            v.SetZ((float)values [2]);
            VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, v);
        }
        else if (length == 4) { // Vector4
            Vector4 v;
            v.SetX((float)values [0]);
            v.SetY((float)values [1]);
            v.SetZ((float)values [2]);
            v.SetW((float)values [3]);
            VeryReal::Creator::Instance()->GetCreator(comp)->AddParameter(key, v);
        }
        std::cout << std::endl;
        key = "";
        values.clear();
    }
}

 std::pair<bool, std::string> ScriptManager::ReadPrefabs() {
    /*std::string a = "LuaFiles/" + p + ".lua";*/   // Esta ruta accede a la carpeta bin/LuaFiles del juego
    //DE MOMENTO LO DEJO AS� POR COMODIDAD PARA TERMINAR EL LUA DE  LOS JUEGOS, LUEGO SE CAMBIA A LA LINEA DE ARRIBA
    std::string a = "../../../bin/LuaFiles/Prefabs.lua";
    int script_status = luaL_dofile(lua_state, a.c_str());
    Error(script_status);

    std::string ent = "Prefabs";
    luabridge::LuaRef prefabs = luabridge::getGlobal(lua_state, ent.c_str());   // Referencia a la primera tabla

    if (prefabs.isTable()) {
        for (int i = 1; i <= prefabs.length(); ++i) {   // Recorremos la tabla de entidades
            luabridge::LuaRef prefab = prefabs[i];
            if (prefab.isTable()) {
                std::string prefab_name = prefab["name"].tostring();
                std::cout << "Nombre del prefab: " << prefab_name << std::endl;
                VeryReal::Entity* e = new Entity();   // A�adiendo entidades
                luabridge::LuaRef components = prefab["components"];
                if (components.isTable()) {
                    for (int j = 1; j <= components.length(); ++j) {   // Recorremos la tabla interior(componentes)
                        luabridge::LuaRef component = components [j];
                        if (component.isTable()) {
                            std::string componentname = component ["name"].tostring();
                            std::cout << "Nombre del componente: " << componentname << std::endl;

                            if (VeryReal::Creator::Instance()->GetCreator(componentname) != nullptr) {
                                luabridge::LuaRef parameters = component ["parameters"];
                                if (parameters.isTable()) {
                                    parameters.push(lua_state);   // Insertamos la tabla a la pila
                                    lua_pushnil(lua_state);
                                    while (lua_next(lua_state, -2)) {
                                        ReadParams(parameters, componentname);   // Llamada a la lectura de par�metros de un componente
                                        lua_pop(lua_state, 1);   // Sacamos el valor actual de la pila
                                    }
                                    lua_pop(lua_state, 1);   // Sacamos la tabla de par�metros de la pila
                                }
                                else {
                                    return {false, "There was no parameters table for " + componentname + "in the Entity named" +prefab_name};
                                }
                                auto addedComponent = e->AddComponent(componentname, j);   // Comentar para hacer pruebas con otros tipos de datos
                                if (!addedComponent.first) return addedComponent;
                            }
                            else 
                            {
                                return {false, "The component " + componentname + " was specified but there is no creator releated to it"};
                            }
                        }
                    }
                }
                VeryReal::Creator::Instance()->AddPrefab(prefab_name, e);
            }
        }
    }
    else {
        return {false, "There was no Prefabs table in the .lua file"};
    }
    return {true, "The prefabs were read without any problem"};
 }

void ScriptManager::ReadFunction(std::string name, int n) {
    std::string s = "../../../bin/LuaFiles/Functions.lua";   // Esta ruta accede a la carpeta bin/LuaFiles del juego
    int script_status = luaL_dofile(lua_state, s.c_str());
    Error(script_status);

    lua_getglobal(lua_state, name.c_str());
    luabridge::Result resultLua = luabridge::push(lua_state, n);
    resultLua = luabridge::push(lua_state, n);
    lua_pcall(lua_state, 2, 1, 0);

    auto resultLua2 = luabridge::Stack<int>::get(lua_state, -1);
    lua_pop(lua_state, 1);
}

void ScriptManager::ExposeFunctionsVoidToLua(std::string name, std::function<void()> FunctionToAdd) {
    luabridge::getGlobalNamespace(lua_state).addFunction(name.c_str(), FunctionToAdd);
}

void ScriptManager::ExposeFunctionsVoidIntToLua(std::string name, std::function<void(int)> FunctionToAdd) {
    luabridge::getGlobalNamespace(lua_state).addFunction(name.c_str(), FunctionToAdd);
}

#pragma once
#ifndef _SCRIPT_MANAGER
#define _SCRIPT_MANAGER

#include "Singleton.h"
#include "Manager.h"
#include <string>
#include "export.h"
struct lua_State;
namespace luabridge {
	class LuaRef;
}

class ScriptManager : public VeryReal::Manager<ScriptManager> {
	friend Singleton<ScriptManager>;

private:
	lua_State* lua_state;
	// Se encarga de leer los parámetros que se le pasarán a los componentes
	void ReadParams(luabridge::LuaRef params, std::string comp);

public:
	ScriptManager();
	~ScriptManager();

	// Abre el archivo .lua
	void Init(std::string p);
	// Compreueba error al abrir archivo
	void Error(int status);
	// Método para probar la creación de entidades y componentes mediante Lua
	void ReadScene(std::string n);
	inline lua_State* GetLuaState() { return lua_state; }
};
//
//// Instancia Singleton
//// @return un puntero de la instancia
//inline ScriptManager& SM() {
//	return *ScriptManager::Instance();
//}
#endif // !_SCRIPT_MANAGER

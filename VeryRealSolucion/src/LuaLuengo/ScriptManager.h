#pragma once
#ifndef _SCRIPT_MANAGER
#define _SCRIPT_MANAGER

#include "Singleton.h"
#include "Manager.h"

struct lua_State;


class ScriptManager : public VeryReal::Manager<ScriptManager> {
	friend Singleton<ScriptManager>;

private:
	lua_State* lua_state;

public:
	ScriptManager();
	~ScriptManager();

	// Abre el archivo .lua
	void Init();
	// Compreueba error al abrir archivo
	void Error(int status);
	// Método para probar la creación de entidades y componentes mediante Lua
	void Test();
	inline lua_State* GetLuaState() { return lua_state; }
};

// Instancia Singleton
// @return un puntero de la instancia
inline ScriptManager& SM() {
	return *ScriptManager::Instance();
}
#endif // !_SCRIPT_MANAGER

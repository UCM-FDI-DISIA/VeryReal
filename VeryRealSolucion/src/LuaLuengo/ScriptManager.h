#pragma once
#ifndef _SCRIPT_MANAGER
#define _SCRIPT_MANAGER

#include "Manager.h"
#include <string>
#include "export.h"

#pragma warning(disable : 4251)

struct lua_State;
namespace luabridge {
	class LuaRef;
}

namespace VeryReal {
	class VERYREAL_API ScriptManager : public VeryReal::Manager<ScriptManager> {
	friend Singleton<ScriptManager>;

	private:
		lua_State* lua_state;
		// Comprueba error al abrir archivo
		void Error(int status);
		// Se encarga de leer los par�metros que se le pasar�n a los componentes
		void ReadParams(luabridge::LuaRef params, std::string comp);

	public:

        ScriptManager() { }
		virtual ~ScriptManager();

		// Abre el archivo .lua
		void Init(std::string p);
		
		// M�todo para probar la creaci�n de entidades y componentes mediante Lua
		void ReadScene(std::string n);
		inline lua_State* GetLuaState() { return lua_state; }
};
//
//// Instancia Singleton
//// @return un puntero de la instancia
//inline ScriptManager& SM() {
//	return *ScriptManager::Instance();
//}
}

#pragma warning(default : 4251)

#endif // !_SCRIPT_MANAGER

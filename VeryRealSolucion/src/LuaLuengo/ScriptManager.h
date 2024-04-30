#pragma once
#ifndef _SCRIPT_MANAGER
#define _SCRIPT_MANAGER

#include "Manager.h"
#include <string>
#include "exportLuaLuengo.h"

#pragma warning(disable : 4251)

struct lua_State;
namespace luabridge {
	class LuaRef;
}

namespace VeryReal {
class  ScriptManager : public VeryReal::Manager<ScriptManager> {
	friend Singleton<ScriptManager>;

	private:
		lua_State* lua_state = nullptr;
		// Comprueba error al abrir archivo
                VERYREAL_LUALUENGO void Error(int status);
		// Se encarga de leer los parámetros que se le pasarán a los componentes
		void ReadParams(luabridge::LuaRef params, std::string comp);
                VERYREAL_LUALUENGO  ScriptManager() { }

	public:
    VERYREAL_LUALUENGO static bool Init() {
      ScriptManager* a = new ScriptManager();
        if (a != nullptr) {
            instance_pointer.reset(a);
            return true;
        }
        return false;
    }
    VERYREAL_LUALUENGO virtual ~ScriptManager();

		// Abre el archivo .lua
    VERYREAL_LUALUENGO void InitManager();
    VERYREAL_LUALUENGO void NewScene(std::string p);
		
		// Método para probar la creación de entidades y componentes mediante Lua
    VERYREAL_LUALUENGO void ReadScene(std::string n);
    VERYREAL_LUALUENGO void ReadPrefabs();
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

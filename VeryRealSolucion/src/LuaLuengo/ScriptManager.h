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
    class VERYREAL_LUALUENGO ScriptManager : public VeryReal::Manager<ScriptManager> {
	    friend Singleton<ScriptManager>;

	    private:
		    lua_State* lua_state = nullptr;
		    // Comprueba error al abrir archivo
                     void Error(int status);
		    // Se encarga de leer los parámetros que se le pasarán a los componentes
		    void ReadParams(luabridge::LuaRef params, std::string comp);
                      ScriptManager() { }

	    public:
        static bool Init() {
          ScriptManager* a = new ScriptManager();
            if (a != nullptr) {
                instance_pointer.reset(a);
                return true;
            }
            return false;
        }
         virtual ~ScriptManager();

		    // Abre el archivo .lua
         void InitManager();
         void NewScene(std::string p);
		
		    // Método para probar la creación de entidades y componentes mediante Lua
         void ReadScene(std::string n);
         void ReadPrefabs();
         inline lua_State* GetLuaState() { return lua_state; }
         void ReadFunction();

         template <class T>
         void ExposeFunctionsToLua(std::string name, T FunctionToAdd) { 
             luabridge::getGlobalNamespace(lua_state).addFunction(name, FunctionToAdd);
         }
    };
}

#pragma warning(default : 4251)

#endif // !_SCRIPT_MANAGER

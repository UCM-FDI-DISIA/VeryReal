#pragma once
#ifndef _SCRIPT_MANAGER
#define _SCRIPT_MANAGER

#include "Manager.h"
#include <string>
#include "exportLuaLuengo.h"
#include <functional>   

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
            std::pair<bool,std::string>Error(int status);
		    // Se encarga de leer los parámetros que se le pasarán a los componentes
		    void ReadParams(luabridge::LuaRef params, std::string comp);
                      ScriptManager() { }

	    public:
        static std::pair<bool,std::string> Init() {
          ScriptManager* a = new ScriptManager();
            if (a != nullptr) {
                instance_pointer.reset(a);
                std::pair<bool, std::string> r = a->InitManager();   //inicializamos el manager
                if (!r.first) {
                    delete a;   //el init manager da error pero se tiene que destruir memoria
                    return {false, "ScriptManager pointer had a problem while it was initializing"};
                }
                return {true, "ScriptManager pointer sucesfully initialized"};
            }
            return {false, "ScriptManager pointer had a problem while it was initializing"};
        }
         virtual ~ScriptManager();

		    // Abre el archivo .lua
         std::pair<bool, std::string> InitManager();
         std::pair<bool,std::string> NewScene(std::string p);
		
		    // Método para probar la creación de entidades y componentes mediante Lua
         std::pair<bool,std::string> ReadScene(std::string n,bool active);
         std::pair<bool,std::string> ReadPrefabs();
         void ReadFunction(std::string name, int n);
         inline lua_State* GetLuaState() { return lua_state; }

         void ExposeFunctionsVoidToLua(std::string name, const std::function<void()> FunctionToAdd);
         void ExposeFunctionsVoidIntToLua(std::string name, const std::function<void(int)> FunctionToAdd);
    };
}

#pragma warning(default : 4251)

#endif // !_SCRIPT_MANAGER

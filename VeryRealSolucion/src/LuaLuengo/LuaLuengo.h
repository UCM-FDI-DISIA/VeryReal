#include <iostream>
#include <string>
#include <vector>
#include "Singleton.h"
#include "Manager.h"
#include <lua.hpp>
#include <LuaBridge.h>
#include <Map.h>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}


using namespace std;
class LuaLuengo : public VeryReal::Manager<LuaLuengo> {
	friend Singleton<LuaLuengo>;
public:

	void Error(lua_State* luaState, int status) {
		if (status == 0) {
			return;
		}

		cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << endl;

		lua_pop(luaState, 1);
	}

	void Test() {
		
		lua_State* L = luaL_newstate();

		luaL_openlibs(L);

		int scriptLoadStatus = luaL_dofile(L, "luaTest.lua");

		Error(L, scriptLoadStatus);

		luabridge::LuaRef entities = luabridge::getGlobal(L, "Entities");

		if (entities.isTable()) {
			for (int i = 1; i <= entities.length(); ++i) {
				luabridge::LuaRef entity = entities[i];
				if (entity.isTable()) {					
					string id = entity["id"].unsafe_cast<string>(); // DUDA: unsafe_cast
					cout << "Nombre de la entidad: " << id << endl;				
					luabridge::LuaRef components = entity["Components"];
					if (components.isTable()) {				
						for (int j = 1; j <= components.length(); ++j) {
							luabridge::LuaRef component = components[j];
							if (component.isTable()) {							
								string name = component["name"].unsafe_cast<string>();															
								cout << "Nombre del componente: " << name << endl;								
							}
						}
						cout << endl;
					}
				}
			}
		}
		lua_close(L);	
	}
};

/// Singleton instance
/// @return A pointer of the instance
inline LuaLuengo& LL() {
	return *LuaLuengo::Instance();
}


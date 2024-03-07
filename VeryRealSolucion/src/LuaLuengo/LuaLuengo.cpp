// LuaLuengo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "LuaLuengo.h"
//int main()
//{
//	//struct Player
//	//{
//	//	std::string title;
//	//	std::string name;
//	//	std::string family;
//	//	int level;
//	//} player;
//
//	//// Create Lua State
//	//lua_State* L = luaL_newstate();
//
//	//// Add standard libraries to Lua Virtual Machine
//	//luaL_openlibs(L);
//
//	//// Register our C++ Function in the global Lua space
//	///*lua_register(L, "HostFunction", lua_HostFunction);*/
//
//
//	//// Load and parse the Lua File
//	//if (LL().CheckLua(L, luaL_dofile(L, "luaTest.lua")))
//	//{
//	//	// Stage 1: Just read simple variables
//	//	std::cout << "[CPP] Stage 1 - Read Simple Variables" << std::endl;
//	//	lua_getglobal(L, "a");
//	//	if (lua_isnumber(L, -1)) std::cout << "[CPP S1] a = " << (int)lua_tointeger(L, -1) << std::endl;
//	//	lua_getglobal(L, "b");
//	//	if (lua_isnumber(L, -1)) std::cout << "[CPP S1] b = " << (int)lua_tointeger(L, -1) << std::endl;
//	//	lua_getglobal(L, "c");
//	//	if (lua_isnumber(L, -1)) std::cout << "[CPP S1] c = " << (int)lua_tointeger(L, -1) << std::endl;
//	//	lua_getglobal(L, "d");
//	//	if (lua_isstring(L, -1)) std::cout << "[CPP S1] d = " << lua_tostring(L, -1) << std::endl << std::endl;
//
//	//	// Stage 2: Read Table Object
//	//	std::cout << "[CPP] Stage 2 - Read Table (Key/Value pairs)" << std::endl;
//	//	lua_getglobal(L, "player");
//	//	if (lua_istable(L, -1))
//	//	{
//	//		lua_pushstring(L, "Name");
//	//		lua_gettable(L, -2);
//	//		player.name = lua_tostring(L, -1);
//	//		lua_pop(L, 1);
//
//	//		lua_pushstring(L, "Family");
//	//		lua_gettable(L, -2);
//	//		player.family = lua_tostring(L, -1);
//	//		lua_pop(L, 1);
//
//	//		lua_pushstring(L, "Title");
//	//		lua_gettable(L, -2);
//	//		player.title = lua_tostring(L, -1);
//	//		lua_pop(L, 1);
//
//	//		lua_pushstring(L, "Level");
//	//		lua_gettable(L, -2);
//	//		player.level = (int)lua_tointeger(L, -1);
//	//		lua_pop(L, 1);
//	//	}
//	//	std::cout << "[CPP S2] " << player.title << " " << player.name << " of " << player.family << " [Lvl: " << player.level << "]" << std::endl << std::endl;
//
//	//	// Stage 3: Call Lua Function
//	//	std::cout << "[CPP] Stage 3 - Call Lua Function" << std::endl;
//	//	lua_getglobal(L, "CalledFromCPP1");
//	//	if (lua_isfunction(L, -1))
//	//	{
//	//		lua_pushnumber(L, 5.0f);
//	//		lua_pushnumber(L, 6.0f);
//	//		lua_pushstring(L, "Bwa ha ha!");
//	//		std::cout << "[CPP S3] Calling 'CalledFromCPP1' in lua script" << std::endl;
//	//		if (LL().CheckLua(L, lua_pcall(L, 3, 1, 0)))
//	//		{
//	//			std::cout << "[CPP S3] 'CalledFromCPP1' returned " << (float)lua_tonumber(L, -1) << std::endl << std::endl;
//	//		}
//	//	}
//
//	//	// Stage 4: Call Lua Function, which calls C++ Function
//	//	std::cout << "[CPP] Stage 4 - Call Lua Function, whcih in turn calls C++ Function" << std::endl;
//	//	lua_getglobal(L, "CalledFromCPP2");
//	//	if (lua_isfunction(L, -1))
//	//	{
//	//		lua_pushnumber(L, 5.0f);
//	//		lua_pushnumber(L, 6.0f);
//	//		std::cout << "[CPP S4] Calling 'CalledFromCPP2' in lua script" << std::endl;
//	//		if (LL().CheckLua(L, lua_pcall(L, 2, 1, 0)))
//	//		{
//	//			std::cout << "[CPP S4] 'CalledFromCPP2' returned " << (float)lua_tonumber(L, -1) << std::endl << std::endl;
//	//		}
//	//	}
//	//}
//
//
//
//
//
//	//system("pause");
//	//lua_close(L);
//	
//}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln


@echo off

rem Directorios
set BAT_DIR=%~dp0
set LUA_SRC=%BAT_DIR%..\Lua
set LUA_BUILD=%BAT_DIR%..\Lua\Builds\
set LUA_SLN=%BAT_DIR%..\Lua\Builds\Lua.sln
set DLL_FOLDERS=%BAT_DIR%..\..\bin

cmake ^
-S %LUA_SRC% -B %LUA_BUILD%

cd %LUA_BUILD%

rem Compilacion de la solucion en Debug y en Release
msbuild %LUA_SLN% /t:build /p:configuration=Debug /maxcpucount
msbuild %LUA_SLN% /t:build /p:configuration=Release /maxcpucount

echo Terminada la build de Lua
pause
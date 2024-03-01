@echo off

rem Directorios
set BAT_DIR=%~dp0
set BULLET_SRC=%BAT_DIR%..\Bullet\Src
set BULLET_BUILD=%BAT_DIR%..\Bullet\Builds
set DLL_FOLDERS=%BAT_DIR%..\..\bin

rem Crear el directorio de compilación si no existe
if not exist "%BULLET_BUILD%" mkdir "%BULLET_BUILD%"

cd %BULLET_BUILD%

echo Configurando la compilacion de Bullet
cmake ^
  -G "Visual Studio 17 2022" ^
  -A x64 ^
		-D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
		-D BUILD_BULLET_ROBOTICS_EXTRA:BOOL=0 ^
		-D BUILD_BULLET_ROBOTICS_GUI_EXTRA:BOOL=0 ^
		-D BUILD_CLSOCKET:BOOL=0 ^
		-D BUILD_ENET:BOOL=0 ^
		-D BUILD_UNIT_TESTS:BOOL=0 ^
		-D ENABLE_VHACD:BOOL=0 ^
		-D BUILD_BULLET2_DEMOS:BOOL=0 ^
		-D BUILD_CPU_DEMOS:BOOL=0 ^
		-D BUILD_OPENGL3_DEMOS:BOOL=0 ^
		-D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=1 ^
	-S %BULLET_SRC% -B %BULLET_BUILD%

echo Compilando Bullet
cmake --build . --config Release
cmake --build . --config Debug

echo Copiando DLLs a la carpeta correspondiente
xcopy /y /s "%BULLET_BUILD%\lib\Release\*.dll" "%DLL_FOLDERS%\Bullet\release\"
xcopy /y /s "%BULLET_BUILD%\lib\Debug\*.dll" "%DLL_FOLDERS%\Bullet\debug\"
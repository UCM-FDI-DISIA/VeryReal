@echo off

rem Directorios
set BAT_DIR=%~dp0
set BULLET_SRC=%BAT_DIR%..\Bullet\Src
set BULLET_BUILD_STATIC=%BAT_DIR%..\Bullet\Builds\Static
set BULLET_BUILD_SHARED=%BAT_DIR%..\Bullet\Builds\Shared
set DLL_FOLDERS=%BAT_DIR%..\..\bin
set LIB_FOLDERS=%BAT_DIR%..\..\lib

rem Crear los directorios de compilación si no existen
if not exist "%BULLET_BUILD_STATIC%" mkdir "%BULLET_BUILD_STATIC%"
if not exist "%BULLET_BUILD_SHARED%" mkdir "%BULLET_BUILD_SHARED%"

rem Configuración para la compilación de bibliotecas estáticas
echo Configurando la compilacion de Bullet (Versiones Estáticas)
cd "%BULLET_BUILD_STATIC%"
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
  -D BUILD_SHARED_LIBS=OFF ^
  -D BUILD_OPENGL3_DEMOS:BOOL=0 ^
  -D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=1 ^
  -S "%BULLET_SRC%" ^
  -B "%BULLET_BUILD_STATIC%"

echo Compilando Bullet (Versiones Estáticas)
cmake --build . --config Release
cmake --build . --config Debug

rem Configuración para la compilación de bibliotecas compartidas
echo Configurando la compilacion de Bullet (Versiones Compartidas)
cd "%BULLET_BUILD_SHARED%"
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
  -D BUILD_SHARED_LIBS=ON ^
  -D BUILD_OPENGL3_DEMOS:BOOL=0 ^
  -D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=1 ^
  -S "%BULLET_SRC%" ^
  -B "%BULLET_BUILD_SHARED%"

echo Compilando Bullet (Versiones Compartidas)
cmake --build . --config Release
cmake --build . --config Debug

echo Copiando DLLs a la carpeta correspondiente
xcopy /y /s "%BULLET_BUILD_SHARED%\lib\Release\*.dll" "%DLL_FOLDERS%"
xcopy /y /s "%BULLET_BUILD_SHARED%\lib\Debug\*.dll" "%DLL_FOLDERS%"

echo Compilacion y copia de archivos completadas.
pause
